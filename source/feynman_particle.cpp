#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "../include/feynman_particle.h"


int FeynmanParticle::id_queue = 0;

FeynmanParticle::FeynmanParticle(int type, std::string name, int source) {

	this->id = this->id_queue;
	this->id_queue++;

	this->type = type;
	this->name = name;
	this->source = source;

}

std::ostream& operator << (std::ostream& os, const FeynmanParticle& particle) {
	os << "[Particle: " << particle.id << ", type: " << particle.type << ", name: " << particle.name << ", source: " << particle.source << "]";
	return os;
}
