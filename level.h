#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "sblock.h"
#include "zblock.h"
#include "jblock.h"
#include "tblock.h"
#include "lblock.h"
#include "oblock.h"
#include "iblock.h"
#include "xblock.h"
#include <memory>


// Interface for Level 
class Level {
	protected:
		int level; 

	public: 
		virtual ~Level();
		Level(int level = 0); 
		virtual std::shared_ptr<Block> genBlock() = 0; 
		int getLevel() const;
};

#endif 





