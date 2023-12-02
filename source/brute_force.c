#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"
#include "../include/brute_force.h"

// 1 is a match, 0 is no match
int usepermutation(
	int *steps, int stepsize,
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int energy, int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {
	struct FPart particle_array_copy[MAX_FPART_AMOUNT];
	for (int i = 0; i < fpart_list_length; i++) {
		particle_array_copy[i] = fpart_list[i];
	}
	//memcpy(particle_array_copy, &fpart_list, sizeof(struct FPart) * fpart_list_length);
	int fpart_list_length_copy = fpart_list_length;
	int energy_copy = energy;

	printf("PERMUTATION: "); for (int i = 0; i < stepsize; i++) printf("%d ", steps[i]); printf("\n");

	for (int i = 0; i < stepsize; i++) {
		use_fblock(particle_array_copy, &fpart_list_length_copy, &energy_copy, &(fblock_list[steps[i]]), 0, 1);
	}

	//print_fpart_all(particle_array_copy, fpart_list_length_copy);

	if (fpart_list_length_copy != desired_output_length) return 0;
	for (int i = 0; i < fpart_list_length_copy; i++) {
		if (particle_array_copy[i].type != desired_output[i]) return 0;
	}
	print_fpart_all(particle_array_copy, fpart_list_length_copy);
	return 1;

	//free(particle_array_copy);
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
	int energy, int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	if(start == end) {
		//printf("PERMUTATION: "); for (int i = 0; i < 6; i++) printf("%d ", arr[i]); printf("\n");
		return usepermutation(arr, arrlen, fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, desired_output_length);
	}

	for(int i = start; i <= end; i++) {
		swap((arr + i), (arr + start));
		if (permutation(arr, arrlen, start + 1, end, fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, desired_output_length) == 1) {
			printf("SUKCES!");
			return 1;
		}
		swap((arr + i), (arr + start));
	}

	return 0;
}

void brute_force(
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int energy, int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	// Create array of values 0..i for permutation purposes
	int *a = (int*)malloc(fblock_list_length * sizeof(int));
	for (int i = 0; i < fblock_list_length; i++) a[i] = i;

	permutation(a, fblock_list_length, 0, fblock_list_length - 1, fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, desired_output_length);
}


