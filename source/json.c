#include "../include/json.h"

#include <stdio.h>
#include <jansson.h>

#include "../include/feynman_block.h"
#include "../include/feynman_particle.h"
#include "../include/functions.h"

int json_load(char *json_string, struct FBlock fblock_list[MAX_FBLOCK_AMOUNT], int *fblock_list_length, struct FPart fpart_list[MAX_FPART_AMOUNT], int *fpart_list_length) {

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

		int type = json_integer_value(json_array_get(block, 0));
        int cost = json_integer_value(json_array_get(block, 1));

		json_t *input = json_array_get(block, 2);
        json_t *output = json_array_get(block, 3);

		fblock_list[(*fblock_list_length)++] = new_FBlock(type, cost, (int*)input, (int*)output);
    }


    // Cleanup
    json_decref(root);
	return 0;
}