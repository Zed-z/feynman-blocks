#include <stdio.h>

#include "../include/feynman_particle.h"

char* fparticle_types[MAX_FPART_TYPE_AMOUNT] = {0};

void print_fpart(struct FPart fpart) {
	printf("<FPart %d> %s (source: %d)\n", fpart.id, fparticle_types[fpart.type], fpart.source);
}

struct FPart new_FPart(int type, int source) {
	static int fpart_id_iter = 0;
	return (struct FPart){fpart_id_iter++, type, source};
}
