#include <vector>
#include <algorithm>

#include "../include/feynman_block.h"

std::vector <FeynmanBlock*> FeynmanBlockList;
unsigned int FeynmanBlock::id_queue = 0;

FeynmanBlock::FeynmanBlock(int type, std::string name, unsigned int cost) {

	this->id = this->id_queue;
	this->id_queue++;

	this->type = type;
	this->name = name;
	this->cost = cost;

	FeynmanBlockList.push_back(this);

}

FeynmanBlock::FeynmanBlock(int type, std::string name, unsigned int cost, std::vector <unsigned int> input, std::vector <unsigned int> output) {

	this->id = this->id_queue;
	this->id_queue++;

	this->type = type;
	this->name = name;
	this->cost = cost;

	for (auto i = input.begin(); i != input.end(); i++) {
		this->input.push_back(*i);
	}
	for (auto o = output.begin(); o != output.end(); o++) {
		this->output.push_back(*o);
	}

	FeynmanBlockList.push_back(this);

}

FeynmanBlock::FeynmanBlock(const FeynmanBlock& fb) {
	FeynmanBlockList.push_back(this);
}

FeynmanBlock::~FeynmanBlock() {
	FeynmanBlockList.erase(std::remove(FeynmanBlockList.begin(), FeynmanBlockList.end(), this), FeynmanBlockList.end());
}