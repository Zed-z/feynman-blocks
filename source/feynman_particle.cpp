#include <vector>
#include <algorithm>

#include "../include/feynman_particle.h"

std::vector <FeynmanParticle*> FeynmanParticleList;
unsigned int FeynmanParticle::id_queue = 0;

FeynmanParticle::FeynmanParticle(int type, std::string name, unsigned int source) {

	this->id = this->id_queue;
	this->id_queue++;

	this->type = type;
	this->name = name;
	this->source = source;

	FeynmanParticleList.push_back(this);

}

FeynmanParticle::FeynmanParticle(const FeynmanParticle& fb) {
	FeynmanParticleList.push_back(this);
}

FeynmanParticle::~FeynmanParticle() {
	FeynmanParticleList.erase(std::remove(FeynmanParticleList.begin(), FeynmanParticleList.end(), this), FeynmanParticleList.end());
}