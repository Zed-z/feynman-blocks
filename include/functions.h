#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "feynman_block.h"
#include "feynman_particle.h"

int use_fblock(struct FPart *fpart_list, int *fpart_list_length, struct FBlock *fblock, int log, int infinite_uses, int dry_run);

void print_fpart_all(struct FPart *fpart_list, int fpart_list_length);
void print_fblock_all(struct FBlock *fblock_list, int fblock_list_length, char **fparticle_types);

#endif
