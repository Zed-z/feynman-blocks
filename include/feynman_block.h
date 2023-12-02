#pragma once
#ifndef FEYNMAN_BLOCK_H
#define FEYNMAN_BLOCK_H


#define MAX_FBLOCK_AMOUNT 16
#define MAX_FBLOCK_TYPE_AMOUNT 10
#define FBLOCK_MAX_INPUT 4
#define FBLOCK_MAX_OUTPUT 4

extern char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT];

struct FBlock {
	int id;			// Unique block id
	int type;		// Block type identifier
	int cost;		// Block usage cost; can be interpreted as time or energy
	int *input;		// Required input particles (type)
	int *output;	// Output particles (type)
};

void print_fblock(struct FBlock fblock);

struct FBlock new_FBlock(int type, int cost, int input[FBLOCK_MAX_INPUT], int output[FBLOCK_MAX_OUTPUT]);


#endif
