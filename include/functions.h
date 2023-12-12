#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "feynman_block.h"
#include "feynman_particle.h"


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


int use_fblock(struct FPart *fpart_list, int *fpart_list_length, struct FBlock *fblock, int log, int infinite_uses, int dry_run);

void print_fpart_all(struct FPart *fpart_list, int fpart_list_length);
void print_fblock_all(struct FBlock *fblock_list, int fblock_list_length, char **fparticle_types);

int check_solution_bool(
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
);
float check_solution_float(
	struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length,
	int desired_output[MAX_FPART_AMOUNT], int desired_output_length
);

#endif
