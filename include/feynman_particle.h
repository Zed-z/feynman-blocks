#pragma once
#ifndef FEYNMAN_PARTICLE_H
#define FEYNMAN_PARTICLE_H


#include <string>

class FeynmanParticle {
	private:
		static unsigned int id_queue;

	public:
		unsigned int id;		// Unique particle id
		unsigned int type;	// Particle type specified by blocks
		std::string name;		// Particle name for ease of use

		unsigned int source;	// Particle source; -1 if it's an initial particle, block id if made by a block

		FeynmanParticle(int type, std::string name, unsigned int source);
		FeynmanParticle(const FeynmanParticle& fb);
		~FeynmanParticle();
};

extern std::vector <FeynmanParticle*> FeynmanParticleList;


#endif
