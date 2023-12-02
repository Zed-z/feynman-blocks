#pragma once
#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "feynman_block.h"
#include "feynman_particle.h"

void swap(int *a, int *b);

void brute_force(struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length, int energy, int desired_output[MAX_FPART_AMOUNT], int desired_output_length);

#endif
