#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/config.h"
#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"
#include "../include/brute_force.h"
#include "../include/timer.h"

// 1 is a match, 0 is no match
int usepermutation(
	int *steps, int stepsize,
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {
	struct FPart particle_array_copy[MAX_FPART_AMOUNT];
	for (int i = 0; i < fpart_list_length; i++) {
		particle_array_copy[i] = fpart_list[i];
	}
	int fpart_list_length_copy = fpart_list_length;

	if (LOG) {
		printf("--------------------PERMUTATION: ");
		for (int i = 0; i < stepsize; i++) printf("%d ", steps[i]);
		printf("\n");
	}

	for (int i = 0; i < stepsize; i++) {
		//Reset IO
		//for (int j = 0; j < FBLOCK_MAX_INPUT; j++) {
		//	fblock_list[steps[i]].input_id[j] = -1;
		//	fblock_list[steps[i]].output_id[j] = -1;
		//}
		use_fblock(particle_array_copy, &fpart_list_length_copy, &(fblock_list[steps[i]]), 0, 1, 0);
	}

	if (LOG) print_fpart_all(particle_array_copy, fpart_list_length_copy);
	if (LOG) print_fblock_all(fblock_list, fblock_list_length, fparticle_types);

	if (check_solution_bool(particle_array_copy, fpart_list_length_copy, desired_output, desired_output_length) == 0) {
		return 0;
	}

	// Success at this point, log results -----------
	if (LOG) printf("------SUCCES!------\n");

	if (LOG) print_fpart_all(particle_array_copy, fpart_list_length_copy);

	//Print
	printf("{\"success\": 1, \"time\": %f, \"fblocks\": [", timer_get());
	for (int i = 0; i < fblock_list_length; i++) {
		print_fblock_json(fblock_list[i]);
		if (i < fblock_list_length - 1) printf(", ");
	}
	printf("], \"fparts\": [");
	for (int i = 0; i < fpart_list_length_copy; i++) {
		print_fpart_json(particle_array_copy[i]);
		if (i < fpart_list_length_copy - 1) printf(", ");
	}
	printf("]}");

	//free(particle_array_copy);
	return 1;
}


void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//permutation function
int permutation(
	int *arr, int arrlen, int start, int end,
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	if(start == end) {
		/*if (LOG) {
			printf("PERMUTATION: ");
			for (int i = 0; i < 6; i++)
			printf("%d ", arr[i]);
			printf("\n");
		}*/

		for (int i = 0; i < fblock_list_length; i++) {
			//Reset block IO
			for (int j = 0; j < FBLOCK_MAX_INPUT; j++) {
				fblock_list[i].input_id[j] = -1;
			}
			for (int j = 0; j < FBLOCK_MAX_OUTPUT; j++) {
				fblock_list[i].output_id[j] = -1;
			}
		}

		return usepermutation(arr, arrlen, fblock_list, fblock_list_length, fpart_list, fpart_list_length, desired_output, desired_output_length);
	}

	for(int i = start; i <= end; i++) {
		swap((arr + i), (arr + start));
		if (permutation(arr, arrlen, start + 1, end, fblock_list, fblock_list_length, fpart_list, fpart_list_length, desired_output, desired_output_length) == 1) {
			return 1;
		}
		swap((arr + i), (arr + start));
	}

	return 0;
}

void brute_force(
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	// Create array of values 0..i for permutation purposes
	int *a = (int*)malloc(fblock_list_length * sizeof(int));
	for (int i = 0; i < fblock_list_length; i++) a[i] = i;

	int ret = permutation(a, fblock_list_length, 0, fblock_list_length - 1, fblock_list, fblock_list_length, fpart_list, fpart_list_length, desired_output, desired_output_length);

	// -------- If you got here, no permutations were found.

	//Print
	if (ret == 0) printf("{\"success\": 0, \"time\": %f}", timer_get());

	free(a);
}


