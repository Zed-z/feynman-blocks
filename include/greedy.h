#pragma once
#ifndef GREEDY_H
#define GREEDY_H

#include "feynman_block.h"
#include "feynman_particle.h"

void greedy(struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int fpart_list_length, int desired_output[MAX_FPART_AMOUNT], int desired_output_length, int randomized);

#endif
