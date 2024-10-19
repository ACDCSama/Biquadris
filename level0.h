#ifndef LEVELZERO_H
#define LEVELZERO_H
#include "level.h"

class Level0 : public Level {
	int count = 0; 		
	std::vector<char> sequence; 
	public: 
		~Level0();
		Level0(std::vector<char> sequence); 
		virtual std::shared_ptr<Block> genBlock() override; 
	
}; 

#endif 



