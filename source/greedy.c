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

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

float check_solution(
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {
	// Setup array for checking types
	int *particle_counts = (int*)malloc(sizeof(int) * desired_output_length);
	for (int i = 0; i < desired_output_length; i++) particle_counts[i] = 0;

	// Count particle type amounts
	for (int i = 0; i < fpart_list_length; i++) {
		if (fpart_list[i].deleted == 1) continue;
		particle_counts[fpart_list[i].type]++;
	}

	// Check if counts match, return 0 early otherwise
	int parts_matching = 0;
	int parts_output = 0;
	int parts_desired_output = 0;

	for (int i = 0; i < desired_output_length; i++) {
		if (LOG) printf("%d %d\n", particle_counts[i], desired_output[i]);
		parts_matching += min(particle_counts[i], desired_output[i]);
		parts_output += particle_counts[i];
		parts_desired_output += desired_output[i];
	}

	// If here, all checks passed, return 1
	free(particle_counts);
	return ((float)parts_matching / (float)max(parts_output, parts_desired_output));
}


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
	do {

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

			int *choice_indexes = (int*)malloc(sizeof(int) * fblock_list_length);
			for (int i = 0; i < fblock_list_length; i++) choice_indexes[i] = i;

			for (int i = 0; i < fblock_list_length; i++) {
				for (int j = 0; j < fblock_list_length; j++) {
					if (choice_quality[i] > choice_quality[j]) {
						int tmp = choice_quality[i];
						choice_quality[i] = choice_quality[j];
						choice_quality[j] = tmp;

						int tmpind = choice_indexes[i];
						choice_indexes[i] = choice_indexes[j];
						choice_indexes[j] = tmpind;
					}
				}
			} 

			int index_to_use = choice_indexes[0];
			if (randomized) {
				index_to_use = choice_indexes[min(rand() % 3, valid_choices-1)];
			}

			free(choice_indexes);

			if (LOG) {
				printf("Using block: ");
				print_fblock(fblock_list[index_to_use], fparticle_types);
			}

			use_fblock(fpart_list, &fpart_list_length, &(fblock_list[index_to_use]), 0, 1, 0);
		}

	} while (valid_choices > 0);


	// Print JSON
	printf("{\"success\": %f, \"time\": %f, \"fblocks\": [", check_solution(fpart_list, fpart_list_length, desired_output, desired_output_length), timer_get());
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
