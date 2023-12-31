#pragma once
#ifndef FEYNMAN_PARTICLE_H
#define FEYNMAN_PARTICLE_H


#define MAX_FPART_AMOUNT 256
#define MAX_FPART_TYPE_AMOUNT 128

extern char* fparticle_types[MAX_FPART_TYPE_AMOUNT];
extern int fparticle_types_length;

struct FPart {
	int id;		// Unique ID
	int type;	// Type of particle
	int source;	// Source: ID of origin block, -1 if initial
	int deleted;// Whether it's deleted or not (kept for visualization purposes)
};

void print_fpart(struct FPart fpart);
void print_fpart_json(struct FPart fpart);

struct FPart new_FPart(int type, int source);


#endif
