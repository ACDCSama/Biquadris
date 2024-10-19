#ifndef LEVELTWO_H
#define LEVELTWO_H
#include "level.h"
#include <cstdlib>

class Level2 : public Level {
	// prob of S = prob of Z = prob of O = prob of L = prob of J = prob of T = prob of I = 1/7; 
	int seed = time(NULL);

	public: 
		Level2(int seed);
		virtual std::shared_ptr<Block> genBlock() override; 
}; 

#endif 





