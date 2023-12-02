#include <iostream>
#include <vector>

#include "include/feynman_block.h"
#include "include/feynman_particle.h"

using namespace std;

std::vector <FeynmanBlock*> FeynmanBlockList;
std::vector <FeynmanParticle*> FeynmanParticleList;

vector <int> block_input;
vector <int> block_output;

int main() {

	block_input.clear(); block_input.push_back(0); block_input.push_back(0);
	block_output.clear(); block_output.push_back(1); block_output.push_back(1);
	FeynmanBlockList.push_back(new FeynmanBlock(0, "electron funny business", 1, block_input, block_output));


	for (int i = 0; i < 3; i++) {
		FeynmanParticleList.push_back(new FeynmanParticle(0, "e-", -1));
	}
	for (int i = 0; i < 3; i++) {
		FeynmanParticleList.push_back(new FeynmanParticle(1, "e+", -1));
	}


	for (auto i = FeynmanBlockList.begin(); i != FeynmanBlockList.end(); i++) {
		cout << **i << endl;
	}
	for (auto i = FeynmanParticleList.begin(); i != FeynmanParticleList.end(); i++) {
		cout << **i << endl;
	}

}