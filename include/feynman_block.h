#pragma once
#ifndef FEYNMAN_BLOCK_H
#define FEYNMAN_BLOCK_H


#include <string>
#include <vector>

class FeynmanBlock {
	private:
		static int id_queue;

	public:
		int id;					// Unique block id
		int type;					// Block type identifier
		std::string name;					// Block type name
		int cost;					// Block usage cost; can be interpreted as time or energy

		std::vector <int> input;	// Required input particles (type)
		std::vector <int> output;	// Output particles (type)

		friend std::ostream& operator << (std::ostream &os, const FeynmanBlock &block);

		FeynmanBlock(int type, std::string name, int cost, std::vector <int> input, std::vector <int> output);

		void simulate();

};

#endif
