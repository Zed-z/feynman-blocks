#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "../include/feynman_block.h"

int FeynmanBlock::id_queue = 0;

FeynmanBlock::FeynmanBlock(int type, std::string name, int cost, std::vector <int> input, std::vector <int> output) {

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

}

std::ostream& operator << (std::ostream& os, const FeynmanBlock& block) {

	std::string inp = "";
	for (auto i = block.input.begin(); i != block.input.end(); i++) {
		inp += std::to_string(*i) + " ";
	}

	std::string out = "";
	for (auto i = block.output.begin(); i != block.output.end(); i++) {
		out += std::to_string(*i) + " ";
	}

	os << "[Block: " << block.id << ", name: " << block.name << ", cost: " << block.cost << ", input: <" << inp << ">, output: <" << out<< ">]";
	return os;
}

void FeynmanBlock::simulate() {
	std::cout << "HELLO";
}
