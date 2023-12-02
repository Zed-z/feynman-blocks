#pragma once
#ifndef FEYNMAN_BLOCK_H
#define FEYNMAN_BLOCK_H


#define MAX_FBLOCK_AMOUNT 16
#define MAX_FBLOCK_TYPE_AMOUNT 10
#define FBLOCK_MAX_INPUT 4
#define FBLOCK_MAX_OUTPUT 4

#include "feynman_particle.h"

extern char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT];
extern int fblock_type_iter;

struct FBlock {
	int id;			// Unique block id
	int type;		// Block type identifier
	int used_count;	// How many times it's been used
	int cost;		// Block usage cost; can be interpreted as time or energy
	int *input;		// Required input particles (type)
	int *input_id;	// Particles selected for input
	int *output;	// Output particles (type)
	int *output_id;	// Particles selected for output
};

void print_fblock(struct FBlock fblock, char* fpart_types[]);

struct FBlock new_FBlock(int type, int cost, int input[FBLOCK_MAX_INPUT], int output[FBLOCK_MAX_OUTPUT]);


#endif
