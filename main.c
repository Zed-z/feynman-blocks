#include <stdio.h>
#include <stdlib.h>

#include "include/feynman_block.h"
#include "include/feynman_particle.h"
#include "include/functions.h"

struct FPart fpart_list[MAX_FPART_AMOUNT];
int fpart_list_length = 0;
struct FBlock fblock_list[MAX_FBLOCK_AMOUNT];
int fblock_list_length = 0;

void print_fpart_all();
int use_fblock(struct FBlock fblock);
int use_fblock(struct FBlock fblock, int log);

int energy = 100;

int main() {

	// Feynman particle type names
	#define P_E 0
	#define P_Q 1
	#define P_P 2
	fparticle_types[P_E] = (char*)"e";
	fparticle_types[P_Q] = (char*)"q";
	fparticle_types[P_P] = (char*)"p";


	{// Block 1: turn 2 electrons into a proton
		fblock_types[fblock_list_length] = (char*)"ee->pp";
		int in[] = {P_E, P_E, -15, -1}; int out[] = {P_P, P_P, -1, -1};
		fblock_list[fblock_list_length] = new_FBlock(fblock_list_length, 10, in, out);
		fblock_list_length++;
	}
	{
		fblock_types[fblock_list_length] = (char*)"qq->💥";
		int in[] = {P_Q, P_Q, -1, -1}; int out[] = {-1, -1, -1, -1};
		fblock_list[fblock_list_length] = new_FBlock(fblock_list_length, 20, in, out);
		fblock_list_length++;
	}
	{
		fblock_types[fblock_list_length] = (char*)"p->qe";
		int in[] = {P_P, -1, -1, -1}; int out[] = {P_Q, P_E, -1, -1};
		fblock_list[fblock_list_length] = new_FBlock(fblock_list_length, 30, in, out);
		fblock_list_length++;
	}
	{
		fblock_types[fblock_list_length] = (char*)"eq->p";
		int in[] = {P_E, P_Q, -1, -1}; int out[] = {P_P, -1, -1, -1};
		fblock_list[fblock_list_length] = new_FBlock(fblock_list_length, 30, in, out);
		fblock_list_length++;
	}

	//*

	for (int i = 0; i < 10; i++) {
		int randint = rand() % 3;
		fpart_list[fpart_list_length++] = new_FPart(randint, -1);
	}

	//for (int i = 0; i < fblock_list_length; i++) print_fblock(fblock_list[i]);
	print_fpart_all();

	for (int i = 0; i < 100; i++) {
		int randint = rand() % fblock_list_length;

		use_fblock(fblock_list[randint], 1);
		//print_fpart_all();

		if (energy == 0) {
			printf("Out of energy!\n");
			print_fpart_all();
			break;
		}
	}
	//*/

	/*
	fpart_list[fpart_list_length++] = new_FPart(0, -1);
	fpart_list[fpart_list_length++] = new_FPart(0, -1);

	use_fblock(fblock_list[0], 2);
	print_fpart_all();
	//*/

}

void print_fpart_all() {
	printf("Total: %d\n", fpart_list_length);
	for (int i = 0; i < fpart_list_length; i++) print_fpart(fpart_list[i]);
}

int use_fblock(struct FBlock fblock) {
	return use_fblock(fblock, 0);
}
int use_fblock(struct FBlock fblock, int log) {
	// 
	// Returns 0 if success, 1 if not enough energy, 2 if input not fullfilled

	if (log > 0) {
		printf("Process: ");
		print_fblock(fblock);
	}

	// Skip if not enough energy
	if (fblock.cost > energy) {
		if (log > 0) printf("Process failed: not enough energy\n");
		return 1;
	}

	int input_indexes[FBLOCK_MAX_INPUT];
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) input_indexes[i] = -1;
	int input_checks_total = 0;

	for (int ini = 0; ini < FBLOCK_MAX_INPUT; ini++) {
		// Skip if this input condition is fullfilled
		if (input_indexes[ini] != -1) continue;

		// Skip if no input particle at current slot (-1)
		int cur_in = fblock.input[ini];
		if (cur_in == -1) continue;

		// Print message
		if (log > 1) printf("Need %d (%s):\n", cur_in, fparticle_types[cur_in]);

		int found_part = 0;
		for (int i = 0; i < fpart_list_length; i++) {
			struct FPart cur_part = fpart_list[i];

			if (log > 1) printf("    Have: ");
			if (log > 1) print_fpart(cur_part);


			// Skip if index already in index list
			int is_already_in_index_list = 0;
			for (int indcheck = 0; indcheck < FBLOCK_MAX_INPUT; indcheck++) {
				if (input_indexes[indcheck] == i) {
					if (log > 1) printf("        TAKEN!!!\n");
					is_already_in_index_list = 1;
					break;
				}
			}
			if (is_already_in_index_list) continue;


			if (cur_in == cur_part.type) {
				if (log > 1) printf("        OK :)\n");

				input_indexes[ini] = i;
				input_checks_total++;

				found_part = 1;
				break;
			} else {
				if (log > 1) printf("        NO :(\n");
			}
		}

		// Quit early if no input found for at least one slot
		if (found_part == 0) {
			if (log > 0) printf("Process failed: missing particles\n");
			return 2;
		}
	}

	printf("Input check success!\n");

	// Delete input particles
	////printf("Before delete\n"); for (int i = 0; i < fpart_list_length; i++) print_fpart(fpart_list[i]);
	int parts_deleted = 0;
	for (int i = 0; i < input_checks_total; i++) {

		int to_delete = input_indexes[i] - parts_deleted;
		if (to_delete < 0 || to_delete >= fpart_list_length) continue;

		for (int di = to_delete; di < fpart_list_length; di++) {
			fpart_list[di] = fpart_list[di + 1];
		}

		fpart_list_length--;
		parts_deleted++;
	}
	////printf("After delete\n"); for (int i = 0; i < fpart_list_length; i++) print_fpart(fpart_list[i]);

	// Add output particles
	for (int i = 0; i < FBLOCK_MAX_OUTPUT; i++) {
		if (fblock.output[i] == -1) break;

		fpart_list[fpart_list_length++] = new_FPart(fblock.output[i], fblock.id);
	}

	// Use up energy
	energy -= fblock.cost;

	// Optional: prevent block from being used again
	fblock.cost = INT_MAX;

	return 0;

}