#include <stdio.h>

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"

int use_fblock(struct FPart *fpart_list, int *fpart_list_length, int *energy, struct FBlock *fblock, int log, int infinite_uses) {
	// 
	// Returns 0 if success, 2 if input not fullfilled, 3 if already used

	if (log > 0) {
		printf("Process: ");
		print_fblock(*fblock, fparticle_types);
	}

	//Skip if already used
	if (!infinite_uses && fblock->used_count > 0) {
		if (log > 0) printf("  Process fail: already used\n");
		return 3;
	}

	int input_indexes[FBLOCK_MAX_INPUT];
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) input_indexes[i] = -1;
	int input_checks_total = 0;

	for (int ini = 0; ini < FBLOCK_MAX_INPUT; ini++) {
		// Skip if this input condition is fullfilled
		if (input_indexes[ini] != -1) continue;

		// Skip if no input particle at current slot (-1)
		int cur_in = fblock->input[ini];
		if (cur_in == -1) continue;

		// Print message
		if (log > 1) printf("Need %d (%s):\n", cur_in, fparticle_types[cur_in]);

		int found_part = 0;
		for (int i = 0; i < (*fpart_list_length); i++) {
			struct FPart cur_part = fpart_list[i];

			if (log > 1) printf("    Have: ");
			if (log > 1) print_fpart(cur_part);

			// Skip if deleted
			if (cur_part.deleted == 1) {
				continue;
			}

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
			if (log > 0) printf("  Process fail: missing particles\n");
			return 2;
		}
	}


	// Save input ids
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) {
		if (fblock->input[i] == -1) break;

		fblock->input_id[i] = fpart_list[input_indexes[i]].id;
	}


	// Delete input particles
	for (int i = 0; i < input_checks_total; i++) {

		int to_delete = input_indexes[i];
		fpart_list[to_delete].deleted = 1;
	}


	// Add output particles
	for (int i = 0; i < FBLOCK_MAX_OUTPUT; i++) {
		if (fblock->output[i] == -1) break;

		struct FPart fp = new_FPart(fblock->output[i], fblock->id);
		fpart_list[(*fpart_list_length)++] = fp;
		fblock->output_id[i] = fp.id;
	}


	// Increase usage counter
	fblock->used_count += 1;

	if (log > 0) printf("  Process success!\n");
	return 0;

}

void print_fpart_all(struct FPart *fpart_list, int fpart_list_length) {
	printf("Total Particles: %d\n", fpart_list_length);
	for (int i = 0; i < fpart_list_length; i++) print_fpart(fpart_list[i]);
}
void print_fblock_all(struct FBlock *fblock_list, int fblock_list_length, char **fparticle_types) {
	printf("Total Blocks: %d\n", fblock_list_length);
	for (int i = 0; i < fblock_list_length; i++) print_fblock(fblock_list[i], fparticle_types);
}
