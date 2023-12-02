#pragma once
#ifndef FEYNMAN_BLOCK_H
#define FEYNMAN_BLOCK_H


#include <string>
#include <vector>

class FeynmanBlock {
	private:
		static unsigned int id_queue;

	public:
		unsigned int id;					// Unique block id
		unsigned int type;					// Block type identifier
		std::string name;					// Block type name
		unsigned int cost;					// Block usage cost; can be interpreted as time or energy

		std::vector <unsigned int> input;	// Required input particles (type)
		std::vector <unsigned int> output;	// Output particles (type)

		FeynmanBlock(int type, std::string name, unsigned int cost);
		FeynmanBlock(int type, std::string name, unsigned int cost, std::vector <unsigned int> input, std::vector <unsigned int> output);
		FeynmanBlock(const FeynmanBlock& fb);
		~FeynmanBlock();

};

extern std::vector <FeynmanBlock*> FeynmanBlockList;

#endif
