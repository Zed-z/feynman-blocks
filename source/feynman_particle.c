#include <stdio.h>

#include "../include/feynman_particle.h"

char* fparticle_types[MAX_FPART_TYPE_AMOUNT] = {0};
int fparticle_types_length = 0;

// O(1)
void print_fpart(struct FPart fpart) {
	printf("<%sFPart %d> %s (source: %d)\n", (fpart.deleted == 1 ? "DELETED " : ""), fpart.id, fparticle_types[fpart.type], fpart.source);
}

// O(1)
void print_fpart_json(struct FPart fpart) {
	printf("{\"id\": %d, \"name\": \"%s\", \"source\": %d, \"deleted\": %d}", fpart.id, fparticle_types[fpart.type], fpart.source, fpart.deleted);
}

// O(1)
struct FPart new_FPart(int type, int source) {
	static int fpart_id_iter = 0;
	return (struct FPart){fpart_id_iter++, type, source};
}
