#include <iostream>

#include "include/feynman_block.h"
#include "source/feynman_block.cpp"
#include "include/feynman_particle.h"
#include "source/feynman_particle.cpp"

using namespace std;

int main() {

	vector <unsigned int> block_input;
	vector <unsigned int> block_output;

	block_input.clear(); block_input.push_back(0); block_input.push_back(0);
	block_output.clear(); block_output.push_back(1); block_output.push_back(1);
	FeynmanBlock block(0, "electron funny business", 1, block_input, block_output);

	FeynmanParticle particle0(0, "e-", -1);
	FeynmanParticle particle1(1, "e+", -1);


	for (auto i = FeynmanBlockList.begin(); i != FeynmanBlockList.end(); i++) {
		cout << "Block: " << *i << endl;
	}
	for (auto i = FeynmanParticleList.begin(); i != FeynmanParticleList.end(); i++) {
		cout << "Particle: " << *i << endl;
	}

}