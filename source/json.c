#include "../include/json.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"


int find_index(const char* target, char* arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(target, arr[i]) == 0) {
            return i; // Return the index if the value is found
        }
    }
    return -1; // Return -1 if the value is not found
}


int json_load(char *json_string, struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int *fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int *fpart_list_length, const char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT], int *test_mode, int **target_output, int *target_output_length) {

    // Setup
    json_error_t error;
    json_t *root = json_loads(json_string, 0, &error);
    if (!root) { fprintf(stderr, "JSON parsing error: %s\n", error.text); return 1; }


    // Parse particles
    json_t *particle_array = json_object_get(root, "particles");
    size_t particle_array_length = json_array_size(particle_array);

    for (size_t i = 0; i < particle_array_length; i++) {
		json_t *part = json_array_get(particle_array, i);

		// Name and count
		const char *name_json = json_string_value(json_array_get(part, 0));
		const char *name = strdup(name_json);
        int count = json_integer_value(json_array_get(part, 1));

		fparticle_types[fparticle_types_length] = (char*)name;
		for (int i = 0; i < count; i++) {
			fpart_list[(*fpart_list_length)++] = new_FPart(fparticle_types_length, -1);
		}
		fparticle_types_length++;

    }


	// Parse blocks
    json_t *block_array = json_object_get(root, "blocks");
    size_t block_array_length = json_array_size(block_array);

    for (size_t i = 0; i < block_array_length; i++) {
        json_t *block = json_array_get(block_array, i);

		// Name and count
		const char *name_json = json_string_value(json_array_get(block, 0));
		const char *name = strdup(name_json);
        int count = json_integer_value(json_array_get(block, 1));

		// Inputs and outputs
		json_t *input_json = json_array_get(block, 2);
			size_t input_size = json_array_size(input_json);
			int input[FBLOCK_MAX_INPUT];
			for (int in = 0; in < FBLOCK_MAX_INPUT; in++) input[in] = -1;

			for (size_t j = 0; j < input_size; j++) {
				const char *input_particle = json_string_value(json_array_get(input_json, j));
				input[j] = find_index(input_particle, fparticle_types, fparticle_types_length);
			}

        json_t *output_json = json_array_get(block, 3);
			size_t output_size = json_array_size(output_json);
			int output[FBLOCK_MAX_INPUT];
			for (int out = 0; out < FBLOCK_MAX_OUTPUT; out++) output[out] = -1;

			for (size_t j = 0; j < output_size; j++) {
				const char *output_particle = json_string_value(json_array_get(output_json, j));
				output[j] = find_index(output_particle, fparticle_types, fparticle_types_length);
			}

		fblock_types[fblock_type_iter] = (char*)name;
		for (int i = 0; i < count; i++) {
			fblock_list[(*fblock_list_length)++] = new_FBlock(fblock_type_iter, input, output);
		}
		fblock_type_iter++;
    }


	// Mode
	*test_mode = -1; // Random
	json_t *json_mode = json_object_get(root, "test_mode");
	if (json_mode != NULL) {
		*test_mode = json_integer_value(json_mode);
	}

	if (*test_mode != -1) {
		// Brute data
		json_t *test_data = json_object_get(root, "test_data");
		size_t test_data_length = json_array_size(test_data);

		(*target_output) = (int*)malloc(sizeof(int)*test_data_length);
		for (int i = 0; i < test_data_length; i++) (*target_output)[i] = 0;

		for (size_t i = 0; i < test_data_length; i++) {
			json_t *data = json_array_get(test_data, i);
			int val = json_integer_value(data);
			(*target_output)[(*target_output_length)++] = val;
		}
	}


    // Cleanup
    json_decref(root);
	return 0;
}