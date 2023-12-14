#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/config.h"
#include "../include/timer.h"

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"

#include "../include/metaheuristic.h"


void crossover(int *parent_a, int *parent_b, int *child_a, int *child_b, int length) {
	int crossover_point = length / 2;

	int ind_a = 0;
	int ind_b = 0;

	for (int i = 0; i < crossover_point; i++) {
		child_a[ind_a++] = parent_a[i];
		child_b[ind_b++] = parent_b[i];
	}

	for (int i = 0; i < length; i++) {

		int is_in_a = 0;
		int is_in_b = 0;

		for (int j = 0; j < crossover_point; j++) {
			if (child_a[j] == parent_b[i]) is_in_a = 1;
			if (child_b[j] == parent_a[i]) is_in_b = 1;
			if (is_in_a && is_in_b) break;
		}

		if (!is_in_a) child_a[ind_a++] = parent_b[i];
		if (!is_in_b) child_b[ind_b++] = parent_a[i];
	}
}

void mutation(int *child, int length, double chance) {
	for (int i = 0; i < length - 1; i++) {
		double roll = (double)rand() / (double)RAND_MAX;
		if (roll > chance) continue;

		int j = rand() % length;
		int tmp = child[i];
		child[i] = child[j];
		child[j] = tmp;
	}
}

float test_out_mutation(
	int *steps, int length,
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {
	struct FPart fpart_list_copy[MAX_FPART_AMOUNT];
	for (int i = 0; i < fpart_list_length; i++) {
		fpart_list_copy[i] = fpart_list[i];
	}
	int fpart_list_length_copy = fpart_list_length;

	for (int i = 0; i < length; i++) {
		int queued = steps[i];

		if (LOG) {
			printf("Using block: ");
			print_fblock(fblock_list[queued], fparticle_types);
		}

		use_fblock(fpart_list_copy, &fpart_list_length_copy, &(fblock_list[queued]), 0, 1, 0);
	}

	/*printf("Steps: ");
	for (int i = 0; i < length; i++) printf("%d ", steps[i]);
	printf("\n");

	printf("Particles: ");
	for (int i = 0; i < fpart_list_length_copy; i++) printf("%d ", fpart_list_copy[i].type);
	printf("\n");*/

	return check_solution_float(fpart_list_copy, fpart_list_length, desired_output, desired_output_length);
}

void print_genetic_board(int *genetic_board, float *genetic_quality, int height, int width) {
	printf("board ----------------------------\n");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d\t ", genetic_board[i*width+j]);
		}
		printf("| %f\n", genetic_quality[i]);
	}
}

void metaheuristic(
	struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length,
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
) {

	#define GENETICS_AMOUNT 10
	#define GENETICS_LENGTH fblock_list_length
	#define EVOLUTIONS 10
	#define MUTATION_CHANCE 0.5
	#define PRINT_PROGRESS 0

	// Define structures for storing information
	int *genetic_board = (int*)malloc(sizeof(int)*GENETICS_LENGTH*GENETICS_AMOUNT);
	float *genetic_quality = (float*)malloc(sizeof(float)*GENETICS_AMOUNT);

	for (int i = 0; i < GENETICS_AMOUNT; i++) {

		#define CURRENT_GENETIC_ROW (i * GENETICS_LENGTH)

		// Create block queue
		for (int j = 0; j < GENETICS_LENGTH; j++) genetic_board[CURRENT_GENETIC_ROW+j] = j;

		// Shuffle
		for (int k = 0; k < GENETICS_LENGTH - 1; k++) {
			int j = k + rand() / (RAND_MAX / (GENETICS_LENGTH - k) + 1);
			int tmp = genetic_board[CURRENT_GENETIC_ROW+k];
			genetic_board[CURRENT_GENETIC_ROW+k] = genetic_board[CURRENT_GENETIC_ROW+j];
			genetic_board[CURRENT_GENETIC_ROW+j] = tmp;
		}

		// Set quality
		genetic_quality[i] = test_out_mutation(genetic_board+CURRENT_GENETIC_ROW, GENETICS_LENGTH, fblock_list, fblock_list_length, fpart_list, fpart_list_length, desired_output, desired_output_length);
	}

	if (PRINT_PROGRESS) print_genetic_board(genetic_board, genetic_quality, GENETICS_AMOUNT, GENETICS_LENGTH);

	for (int evo = 0; evo < EVOLUTIONS; evo++) {

		// Sort to get parents
		int max_ind = 0;
		float max_val = -1;
		int max_ind_2 = 0;
		float max_val_2 = -1;

		for (int j = 0; j < GENETICS_AMOUNT; j++) {
			if (genetic_quality[j] > max_val) {
				max_ind_2 = max_ind;
				max_val_2 = max_val;
				max_ind = j;
				max_val = genetic_quality[j];
			} else if (genetic_quality[j] > max_val_2 && genetic_quality[j] <= max_val) {
				max_ind_2 = j;
				max_val_2 = genetic_quality[j];
			}
		}

		// Parents
		int parent_a_ind = max_ind;
		int parent_b_ind = max_ind_2;

		if (PRINT_PROGRESS) printf("PARENTS CHOSEN AT INDEXES %d, %d\n", parent_a_ind, parent_b_ind);

		// Crossover and mutate non-parent indexes
		for (int j = 0; j < GENETICS_AMOUNT; j++) {
			if (j == parent_a_ind || j == parent_b_ind) continue;

			int next_non_parent = -1;
			for (int k = 0; k < GENETICS_AMOUNT; k++) {
				if (k != parent_a_ind && k != parent_b_ind) {
					next_non_parent = k;
					break;
				}
			}
			if (next_non_parent == -1) continue;

			crossover(genetic_board+(parent_a_ind*GENETICS_LENGTH), genetic_board+(parent_b_ind*GENETICS_LENGTH),
				genetic_board+(j*GENETICS_LENGTH), genetic_board+(next_non_parent*GENETICS_LENGTH), GENETICS_LENGTH);

			mutation(genetic_board+(j*GENETICS_LENGTH), GENETICS_LENGTH, MUTATION_CHANCE);
			mutation(genetic_board+(next_non_parent*GENETICS_LENGTH), GENETICS_LENGTH, MUTATION_CHANCE);
		}

		for (int i = 0; i < GENETICS_AMOUNT; i++) {
			genetic_quality[i] = test_out_mutation(genetic_board+CURRENT_GENETIC_ROW, GENETICS_LENGTH, fblock_list, fblock_list_length, fpart_list, fpart_list_length, desired_output, desired_output_length) + (i == parent_a_ind || i == parent_b_ind ? -0.1 : 0);//Discourage repeated use of parents
		}

		if (PRINT_PROGRESS) print_genetic_board(genetic_board, genetic_quality, GENETICS_AMOUNT, GENETICS_LENGTH);
	}

	// Get best solution
	int max_ind = 0;
	float max_val = genetic_quality[0];

	for (int j = 1; j < GENETICS_AMOUNT; j++) {
		if (genetic_quality[j] > max_val) {
			max_ind = j;
			max_val = genetic_quality[j];
		}
	}

	// Apply best solution
	for (int i = 0; i < GENETICS_LENGTH; i++) {
		int queued = genetic_board[max_ind*GENETICS_AMOUNT+i];

		if (LOG) {
			printf("Using block: ");
			print_fblock(fblock_list[queued], fparticle_types);
		}

		use_fblock(fpart_list, &fpart_list_length, &(fblock_list[queued]), 0, 1, 0);
	}

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
