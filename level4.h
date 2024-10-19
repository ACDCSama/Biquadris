#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include "level.h"
#include "level3.h"

class Level4 : public Level {
	// prob of S = prob of Z = 2/9; prob of O = prob of L = prob of J = prob of T = prob of I = 1/9;  
	int seed = time(NULL);

	int count = 0; 
	std::vector <char> sequence; 
	bool isRandom;

	public:
		Level4(int seed, std::vector<char> sequence, bool isRandom); 
		virtual std::shared_ptr<Block> genBlock() override; 
}; 

#endif 




