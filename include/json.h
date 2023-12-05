#pragma once
#ifndef JSON_H
#define JSON_H

#include <jansson.h>

#include "feynman_block.h"
#include "feynman_particle.h"
#include "functions.h"

int json_load(char *json_string, struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int *fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int *fpart_list_length, const char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT], int *test_mode, int **brute_target_output, int *brute_target_output_length);

#endif
