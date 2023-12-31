#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#include "include/config.h"
#include "include/functions.h"
#include "include/timer.h"
#include "include/json.h"

#include "include/feynman_block.h"
#include "include/feynman_particle.h"

#include "include/brute_force.h"
#include "include/greedy.h"
#include "include/metaheuristic.h"


struct FPart fpart_list[MAX_FPART_AMOUNT];
int fpart_list_length = 0;

struct FBlock fblock_list[MAX_FBLOCK_AMOUNT];
int fblock_list_length = 0;

#define MAX_PROCESSES 100
struct FBlock *process_list[MAX_PROCESSES];
int process_id = 0;

int test_mode = -1;
int *target_output;
int target_output_length;

int main(int argc, char *argv[]) {

	// Read pipe if available
	#define READ_MAX 65535
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

		if (json_load(chars_read, fblock_list, &fblock_list_length, fpart_list, &fpart_list_length, fblock_types, &test_mode, &target_output, &target_output_length) == 1) return 1;

	// Arguments
	} else if (argc > 1) {

		if (argv[1][0] == '{') {// Raw json

			if (json_load(argv[1], fblock_list, &fblock_list_length, fpart_list, &fpart_list_length, fblock_types, &test_mode, &target_output, &target_output_length) == 1) return 1;

		} else {// Json file

			FILE *f = fopen(argv[1], "r");
			fgets(chars_read, READ_MAX, f);
			fclose(f);
			if (json_load(chars_read, fblock_list, &fblock_list_length, fpart_list, &fpart_list_length, fblock_types, &test_mode, &target_output, &target_output_length) == 1) return 1;

		}

	// No data
	} else {
		printf("No input data!\n");
		exit(1);
	}

	if (LOG) print_fblock_all(fblock_list, fblock_list_length, fparticle_types);
	if (LOG) print_fpart_all(fpart_list, fpart_list_length);


	timer_reset();
	switch (test_mode) {
		case 0: {//Random tests

			// Create block queue and shuffle it
			int *block_queue = (int*)malloc(sizeof(int) * fblock_list_length);
			for (int i = 0; i < fblock_list_length; i++) block_queue[i] = i;

			// Shuffle
			for (int i = 0; i < fblock_list_length - 1; i++) {
				int j = i + rand() / (RAND_MAX / (fblock_list_length - i) + 1);
				int tmp = block_queue[i];
				block_queue[i] = block_queue[j];
				block_queue[j] = tmp;
			}

			// Use blocks in order
			for (int i = 0; i < fblock_list_length; i++) {
				int queued = block_queue[i];

				if (LOG) {
					printf("Using block: ");
					print_fblock(fblock_list[queued], fparticle_types);
				}

				if (use_fblock(fpart_list, &fpart_list_length, &(fblock_list[queued]), 0, 0, 0) == 0) {
					if (LOG) printf("Success!\n");
					if (LOG) print_fpart_all(fpart_list, fpart_list_length);
				} else {
					if (LOG) printf("Fail!\n");
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

			break;
		}
		case 1: {// Brute Force
			brute_force(fblock_list, fblock_list_length, fpart_list, fpart_list_length, target_output, target_output_length);

			break;
		}
		case 2: {// Greedy
			greedy(fblock_list, fblock_list_length, fpart_list, fpart_list_length, target_output, target_output_length, 0);

			break;
		}
		case 3: {// Greedy randomized
			greedy(fblock_list, fblock_list_length, fpart_list, fpart_list_length, target_output, target_output_length, 1);

			break;
		}
		case 4: {// Metaheuristic
			metaheuristic(fblock_list, fblock_list_length, fpart_list, fpart_list_length, target_output, target_output_length);

			break;
		}
		default: {// Do nothing
			if (LOG) printf("No valid mode!\n");

			printf("{\"success\": -1, \"time\": %f, \"fblocks\": [", timer_get());
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

			exit(1);
			break;
		}
	}
}
