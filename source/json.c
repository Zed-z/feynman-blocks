#include "../include/json.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"

int json_load(char *json_string, struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int *fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int *fpart_list_length, const char* fblock_types[MAX_FBLOCK_TYPE_AMOUNT]) {

    // Setup
    json_error_t error;
    json_t *root = json_loads(json_string, 0, &error);
    if (!root) { fprintf(stderr, "JSON parsing error: %s\n", error.text); return 1; }


    // Parse particles
    json_t *particle_array = json_object_get(root, "particles");
    size_t particle_array_length = json_array_size(particle_array);

    for (size_t i = 0; i < particle_array_length; i++) {
        int part = json_integer_value(json_array_get(particle_array, i));

		fpart_list[(*fpart_list_length)++] = new_FPart(part, -1);
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

		// Type id and cost
        int cost = json_integer_value(json_array_get(block, 2));

		// Inputs and outputs
		json_t *input_json = json_array_get(block, 3);
			size_t input_size = json_array_size(input_json);
			int *input = malloc(input_size * sizeof(int));
			for (size_t j = 0; j < input_size; j++) {
				input[j] = json_integer_value(json_array_get(input_json, j));
			}
        json_t *output_json = json_array_get(block, 4);
			size_t output_size = json_array_size(output_json);
			int *output = malloc(output_size * sizeof(int));
			for (size_t j = 0; j < output_size; j++) {
				output[j] = json_integer_value(json_array_get(output_json, j));
			}

		fblock_types[fblock_type_iter] = (char*)name;
		for (int i = 0; i < count; i++) {
			fblock_list[(*fblock_list_length)++] = new_FBlock(fblock_type_iter, cost, input, output);
		}
		fblock_type_iter++;

		// Cleanup
		free(input);
        free(output);
    }


    // Cleanup
    json_decref(root);
	return 0;
}