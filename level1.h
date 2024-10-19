#ifndef LEVELONE_H
#define LEVELONE_H
#include "level.h"
#include <cstdlib>

class Level1 : public Level {
		// prob of S = prob of Z = 1/12; prob of O = prob of L = prob of J = prob of T = prob of I = 1/6; 
		int seed = time(NULL);

	public: 
		Level1(int seed);
		virtual std::shared_ptr<Block> genBlock() override; 
}; 

#endif 




