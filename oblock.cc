
#include "oblock.h"
using namespace std; 
 
OBlock::OBlock(int level) : Block{level, 'O'} {
    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 3});
    theCells.emplace_back(Coord{0, 2});
    theCells.emplace_back(Coord{1, 2});
}



