#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/config.h"
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
	int fpart_list_length_copy = fpart_list_length;
	int energy_copy = energy;

	if (LOG) {
		printf("PERMUTATION: ");
		for (int i = 0; i < stepsize; i++) printf("%d ", steps[i]);printf("\n");
	}

	for (int i = 0; i < stepsize; i++) {
		use_fblock(particle_array_copy, &fpart_list_length_copy, &energy_copy, &(fblock_list[steps[i]]), 0, 1);
	}

	if (LOG) print_fpart_all(particle_array_copy, fpart_list_length_copy);


	int *particle_counts = (int*)malloc(sizeof(int) * desired_output_length);
	for (int i = 0; i < desired_output_length; i++) particle_counts[i] = 0;

	for (int i = 0; i < fpart_list_length_copy; i++) {
		particle_counts[particle_array_copy[i].type]++;
	}

	for (int i = 0; i < desired_output_length; i++) {
		if (LOG) printf("%d %d\n", particle_counts[i], desired_output[i]);
		if (particle_counts[i] != desired_output[i]) {
			free(particle_counts);
			return 0;
		}
	}

	// Success at this point, log results -----------

	if (LOG) print_fpart_all(particle_array_copy, fpart_list_length_copy);

	printf("{\"fblocks\": [");
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

	free(particle_counts);
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
	int energy, int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	if(start == end) {
		/*if (LOG) {
			printf("PERMUTATION: ");
			for (int i = 0; i < 6; i++)
			printf("%d ", arr[i]);
			printf("\n");
		}*/
		return usepermutation(arr, arrlen, fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, desired_output_length);
	}

	for(int i = start; i <= end; i++) {
		swap((arr + i), (arr + start));
		if (permutation(arr, arrlen, start + 1, end, fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, desired_output_length) == 1) {
			if (LOG) printf("SUKCES!");
			exit(1);
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

	free(a);
}


