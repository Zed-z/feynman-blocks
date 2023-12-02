#pragma once
#ifndef FEYNMAN_PARTICLE_H
#define FEYNMAN_PARTICLE_H


#include <string>
#include <iostream>

class FeynmanParticle {
	private:
		static int id_queue;

	public:
		int id;		// Unique particle id
		int type;	// Particle type specified by blocks
		std::string name;		// Particle name for ease of use

		int source;	// Particle source; -1 if it's an initial particle, block id if made by a block

		friend std::ostream& operator << (std::ostream &os, const FeynmanParticle &particle);

		FeynmanParticle(int type, std::string name, int source);

};


#endif
