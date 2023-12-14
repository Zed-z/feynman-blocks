#pragma once
#ifndef FEYNMAN_BLOCK_H
#define FEYNMAN_BLOCK_H


#define MAX_FBLOCK_AMOUNT 128
#define MAX_FBLOCK_TYPE_AMOUNT 128
#define FBLOCK_MAX_INPUT 4
#define FBLOCK_MAX_OUTPUT 4

#include "feynman_particle.h"

extern const char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT];
extern int fblock_type_iter;

struct FBlock {
	int id;			// Unique block id
	int type;		// Block type identifier
	int used_count;	// How many times it's been used
	int *input;		// Required input particles (type)
	int *input_id;	// Particles selected for input
	int *output;	// Output particles (type)
	int *output_id;	// Particles selected for output
};

void print_fblock(struct FBlock fblock, char* fpart_types[]);
void print_fblock_json(struct FBlock fblock);

struct FBlock new_FBlock(int type, int input[FBLOCK_MAX_INPUT], int output[FBLOCK_MAX_OUTPUT]);


#endif
