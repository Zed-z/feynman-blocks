#include <stdio.h>
#include <stdlib.h>

#include "../include/feynman_block.h"

char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT] = {0};

void print_fblock(struct FBlock fblock) {
	printf("<FBlock %d> %s (cost: %d)\n", fblock.id, fblock_types[fblock.type], fblock.cost);
}

struct FBlock new_FBlock(int type, int cost, int input[FBLOCK_MAX_INPUT], int output[FBLOCK_MAX_OUTPUT]) {
	static int fblock_id_iter = 0;

	int *in = (int*)malloc(FBLOCK_MAX_INPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_INPUT; i++) in[i] = input[i];

	int *out = (int*)malloc(FBLOCK_MAX_OUTPUT * sizeof(int));
	for (int i = 0; i < FBLOCK_MAX_OUTPUT; i++) out[i] = output[i];

	return (struct FBlock){fblock_id_iter++, type, cost, in, out};
}
