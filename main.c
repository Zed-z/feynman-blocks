#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/feynman_block.h"
#include "include/feynman_particle.h"
#include "include/functions.h"
#include "include/brute_force.h"
#include "include/json.h"

struct FPart fpart_list[MAX_FPART_AMOUNT];
int fpart_list_length = 0;

struct FBlock fblock_list[MAX_FBLOCK_AMOUNT];
int fblock_list_length = 0;

void swap(int *a, int *b);
void permutation(int *arr, int arrlen, int start, int end);

int energy = 500;
#define MAX_PROCESSES 100
struct FBlock *process_list[MAX_PROCESSES];
int process_id = 0;

int main(int argc, char *argv[]) {

	// Feynman particle type names
	#define P_E 0
	#define P_Q 1
	#define P_P 2
	#define MAX_FPART_TYPES 3
	fparticle_types[P_E] = (char*)"e";
	fparticle_types[P_Q] = (char*)"q";
	fparticle_types[P_P] = (char*)"p";


	// Block 1: turn 2 electrons into a proton
	/*fblock_types[fblock_type_iter] = (char*)"ee->pp";
	for (int i = 0; i < 2; i++) {
		int in[] = {P_E, P_E, -1, -1}; int out[] = {P_P, P_P, -1, -1};
		fblock_list[fblock_list_length++] = new_FBlock(fblock_type_iter, 10, in, out);
	}
	fblock_type_iter++;

	fblock_types[fblock_type_iter] = (char*)"qq->💥";
	for (int i = 0; i < 1; i++) {
		int in[] = {P_Q, P_Q, -1, -1}; int out[] = {-1, -1, -1, -1};
		fblock_list[fblock_list_length++] = new_FBlock(fblock_type_iter, 20, in, out);
	}
	fblock_type_iter++;

	fblock_types[fblock_type_iter] = (char*)"p->qe";
	for (int i = 0; i < 2; i++) {
		int in[] = {P_P, -1, -1, -1}; int out[] = {P_Q, P_E, -1, -1};
		fblock_list[fblock_list_length++] = new_FBlock(fblock_type_iter, 30, in, out);
	}
	fblock_type_iter++;

	fblock_types[fblock_type_iter] = (char*)"eq->p";
	for (int i = 0; i < 2; i++) {
		int in[] = {P_E, P_Q, -1, -1}; int out[] = {P_P, -1, -1, -1};
		fblock_list[fblock_list_length++] = new_FBlock(fblock_type_iter, 15, in, out);
	}
	fblock_type_iter++;*/

	// Particles
	if (argc > 1) {
		printf("h %s\n\n",argv[1]);
		if (json_load(argv[1], fblock_list, &fblock_list_length, fpart_list, &fpart_list_length) == 1) return 1;
	} else {
		if (json_load("{\"particles\":[0, 1, 1, 2, 0, 1]}", fblock_list, &fblock_list_length, fpart_list, &fpart_list_length) == 1) return 1;
	}
	
	/*for (int i = 0; i < 10; i++) {
		int randint = rand() % MAX_FPART_TYPES;
		fpart_list[fpart_list_length++] = new_FPart(randint, -1);
		fpart_list_output[fpart_list_length_output++] = fpart_list[fpart_list_length-1];
	}*/

	print_fblock_all(fblock_list, fblock_list_length, fparticle_types);
	print_fpart_all(fpart_list, fpart_list_length);
	return 0;

	//Random tests
	/*
	for (int i = 0; i < MAX_PROCESSES; i++) {
		int randint = rand() % fblock_list_length;

		if (use_fblock(fpart_list, &fpart_list_length, &energy, &(fblock_list[randint]), 1, 0) == 0) {
			print_fpart_all(fpart_list, fpart_list_length);
			process_list[process_id++] = &(fblock_list[randint]);
		}

		if (energy == 0) {
			printf("Out of energy!\n");
			break;
		}
	}
	printf("\n\n");
	print_fblock_all(fblock_list, fblock_list_length, fparticle_types);
	print_fpart_all(fpart_list, fpart_list_length);

	printf("\n\nProcesses:\n");
	for (int i = 0; i < process_id; i++) print_fblock(*(process_list[i]), fparticle_types);
	//*/

	// Brute Force
	int desired_output[MAX_FPART_TYPES] = {0, 2, 6};
	brute_force(fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, MAX_FPART_TYPES);
}
