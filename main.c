#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "include/config.h"
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

	// Mode select
	enum Mode { RANDOM, BRUTE };
	enum Mode mode;

	if (argc < 2) {
		mode = RANDOM;
	} else {
		if (strcmp(argv[1], "random") == 0) mode = RANDOM;
		if (strcmp(argv[1], "brute") == 0) mode = BRUTE;
	}

	// Read pipe if available
	#define READ_MAX 1024
	int chars_read_count = 0;
	char chars_read[READ_MAX];

	if (!isatty(fileno(stdin))) {
		char c;
        while ((c = getchar()) != EOF) {
			if (c == '\0' || c == EOF || c == '\n') continue;
			chars_read[chars_read_count++] = c;
		}
		chars_read[chars_read_count++] = '\0';
	}

	// Stdin for pipes
	if (chars_read_count > 0) {

		if (json_load(chars_read, fblock_list, &fblock_list_length, fpart_list, &fpart_list_length, fblock_types) == 1) return 1;

	// Arguments
	} else if (argc > 2) {
		if (json_load(argv[2], fblock_list, &fblock_list_length, fpart_list, &fpart_list_length, fblock_types) == 1) return 1;

	// No data
	} else {
		printf("No input data!]n");
		exit(1);
	}

	if (LOG) print_fblock_all(fblock_list, fblock_list_length, fparticle_types);
	if (LOG) print_fpart_all(fpart_list, fpart_list_length);


	if (mode == RANDOM) {
		//Random tests
		for (int i = 0; i < MAX_PROCESSES; i++) {
			int randint = rand() % fblock_list_length;

			if (use_fblock(fpart_list, &fpart_list_length, &energy, &(fblock_list[randint]), 0, 0) == 0) {
				if (LOG) print_fpart_all(fpart_list, fpart_list_length);
				process_list[process_id++] = &(fblock_list[randint]);
			}

			if (energy == 0) {
				if (LOG) printf("Out of energy!\n");
				break;
			}
		}
		if (LOG) printf("\n\n");
		if (LOG) print_fblock_all(fblock_list, fblock_list_length, fparticle_types);
		if (LOG) print_fpart_all(fpart_list, fpart_list_length);

		if (LOG) printf("\n\nProcesses:\n");
		for (int i = 0; i < process_id; i++) if (LOG) print_fblock(*(process_list[i]), fparticle_types);


		printf("{\"fblocks\": [");
		for (int i = 0; i < fblock_list_length; i++) {
			print_fblock_json(fblock_list[i]);
			if (i < fblock_list_length - 1) printf(", ");
		}
		printf("], \"fparts\": [");
		for (int i = 0; i < fpart_list_length; i++) {
			print_fpart_json(fpart_list[i]);
			if (i < fpart_list_length - 1) printf(", ");
		}
		printf("]}");
	}

	else if (mode == BRUTE) {
		// Brute Force
		int desired_output[] = {2, 2, 6};
		brute_force(fblock_list, fblock_list_length, fpart_list, fpart_list_length, energy, desired_output, fparticle_types_length);
	}

	else {
		printf("No valid mode!\n");
		exit(1);
	}

}
