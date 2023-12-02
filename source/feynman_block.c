#include <stdio.h>
#include <stdlib.h>

#include "../include/feynman_block.h"

char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT] = {0};

void print_fblock(struct FBlock fblock, char* fpart_types[]) {
	printf("<FBlock %d> %s (cost: %d) ", fblock.id, fblock_types[fblock.type], fblock.cost);

	printf("\t[");

	printf("In: < ");
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) if (fblock.input[i] != -1) {
		printf("%d(%s) ", fblock.input[i], fpart_types[fblock.input[i]]);
	}
	printf(">");

	if (fblock.used_count > 0) {
		printf("\tIn ID: < ");
		for (int i = 0; i < FBLOCK_MAX_INPUT; i++) if (fblock.input_id[i] != -1) {
			printf("%d ", fblock.input_id[i]);
		}
		printf(">");
	}

	printf("\tOut: < ");
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) if (fblock.output[i] != -1) {
		printf("%d(%s) ", fblock.output[i], fpart_types[fblock.output[i]]);
	}
	printf(">");

	if (fblock.used_count > 0) {
		printf("\tOut ID: < ");
		for (int i = 0; i < FBLOCK_MAX_INPUT; i++) if (fblock.output_id[i] != -1) {
			printf("%d ", fblock.output_id[i]);
		}
		printf(">");
	}

	printf("]\n");

}

struct FBlock new_FBlock(int type, int cost, int input[FBLOCK_MAX_INPUT], int output[FBLOCK_MAX_OUTPUT]) {
	static int fblock_id_iter = 0;

	int *in = (int*)malloc(FBLOCK_MAX_INPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) in[i] = input[i];

	int *in_i = (int*)malloc(FBLOCK_MAX_INPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) in_i[i] = -1;

	int *out = (int*)malloc(FBLOCK_MAX_OUTPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_OUTPUT; i++) out[i] = output[i];

	int *out_i = (int*)malloc(FBLOCK_MAX_OUTPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_OUTPUT; i++) out_i[i] = -1;

	return (struct FBlock){fblock_id_iter++, type, 0, cost, in, in_i, out, out_i};
}
