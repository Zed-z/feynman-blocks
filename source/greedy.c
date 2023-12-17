#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/config.h"
#include "../include/timer.h"

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"

#include "../include/greedy.h"


// O(n)
void find_top_3_indexes(int arr[], int size, int *max1, int *max2, int *max3) {
    *max1 = *max2 = *max3 = -1;

    for (int i = 0; i < size; ++i) {
        if (*max1 == -1 || arr[i] > arr[*max1] || (arr[i] == arr[*max1] && i < *max1)) {
            *max3 = *max2;
            *max2 = *max1;
            *max1 = i;
        } else if (*max2 == -1 || arr[i] > arr[*max2] || (arr[i] == arr[*max2] && i < *max2)) {
            *max3 = *max2;
            *max2 = i;
        } else if (*max3 == -1 || arr[i] > arr[*max3] || (arr[i] == arr[*max3] && i < *max3)) {
            *max3 = i;
        }
    }
}


// O(b^2) or O(b*p)
void greedy(
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length,
	int randomized // Whether to pick the best or one of the best solutions
) {

	// Init random
	time_t t;
	srand((unsigned) time(&t));

	// Create choice quality array, -1 means ignore no matter what
	int *choice_quality = (int*)malloc(sizeof(int) * fblock_list_length);
	for (int i = 0; i < fblock_list_length; i++) choice_quality[i] = -1;

	// Calculate quality
	int valid_choices;
	do { // Worst case scenario, this runs b times

		valid_choices = 0;

		for (int i = 0; i < fblock_list_length; i++) {

			if (LOG) print_fblock(fblock_list[i], fparticle_types);

			// Never use a block twice
			if (fblock_list[i].used_count > 0) {
				choice_quality[i] = -1;
				if (LOG) printf("Already used!\n");
				continue;
			}

			// Don't use if inputs don't match
			if (use_fblock(fpart_list, &fpart_list_length, &(fblock_list[i]), 0, 1, 1) == 2) {
				choice_quality[i] = -1;
				if (LOG) printf("Inputs don't match!\n");
				continue;
			}

			// After this point, the block is valid
			choice_quality[i] = 0;

			// Add score if output in desired output
			for (int j = 0; j < FBLOCK_MAX_OUTPUT; j++) {
				if (fblock_list[i].output[j] == -1) continue;

				for (int k = 0; k < desired_output_length; k++) {
					if (fblock_list[i].output[j] == desired_output[k]) {
						choice_quality[i] += 1;
					}
				}
			}

			// Subtract score if input needed
			for (int j = 0; j < FBLOCK_MAX_INPUT; j++) {
				if (fblock_list[i].input[j] == -1) continue;

				for (int k = 0; k < desired_output_length; k++) {
					if (fblock_list[i].input[j] == desired_output[k]) {
						choice_quality[i] -= 1;
					}
				}
			}
		}


		// Print quality
		if (LOG) {
			printf("Quality: ");
			for (int i = 0; i < fblock_list_length; i++) {
				printf("%d ", choice_quality[i]);
			}
			printf("\n");
		}


		// Valid choice exists
		for (int i = 1; i < fblock_list_length; i++) {
			if (choice_quality[i] >= 0) valid_choices += 1;
		}


		// Use highest quality block
		if (valid_choices > 0) {

			int max1; int max2; int max3;
			find_top_3_indexes(choice_quality, fblock_list_length, &max1, &max2, &max3);

			int index_to_use;
			if (randomized) {
				switch (min(rand() % 3, valid_choices-1)) {
					case 0: index_to_use = max1; break;
					case 1: index_to_use = max2; break;
					case 2: index_to_use = max3; break;
				}
			} else {
				index_to_use = max1;
			}

			if (LOG) {
				printf("Using block: ");
				print_fblock(fblock_list[index_to_use], fparticle_types);
			}

			use_fblock(fpart_list, &fpart_list_length, &(fblock_list[index_to_use]), 0, 1, 0);
		}

	} while (valid_choices > 0);


	// Print JSON
	printf("{\"success\": %f, \"time\": %f, \"fblocks\": [", check_solution_float(fpart_list, fpart_list_length, desired_output, desired_output_length), timer_get());
	for (int i = 0; i < fblock_list_length; i++) {
		print_fblock_json(fblock_list[i]);
		if (i < fblock_list_length - 1) printf(", ");
	}
	printf("], \"fparts\": [");
	for (int i = 0; i < fpart_list_length; i++) {
		print_fpart_json(fpart_list[i]);
		if (i < fpart_list_length - 1) printf(", ");
	}
	printf("]}");

}
