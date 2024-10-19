
#include "zblock.h"
using namespace std; 
 
ZBlock::ZBlock(int level) : Block{level, 'Z'} {
    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 2});
    theCells.emplace_back(Coord{1, 2});
    theCells.emplace_back(Coord{2, 3});
}



