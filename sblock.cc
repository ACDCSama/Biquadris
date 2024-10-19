#include "sblock.h"
using namespace std; 
 
SBlock::SBlock(int level) : Block{level, 'S'} {
    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 3});
    theCells.emplace_back(Coord{1, 2});
    theCells.emplace_back(Coord{2, 2});
}



