#include "lblock.h"
using namespace std; 

LBlock::LBlock(int level) : Block{level, 'L'} {
    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 3});
    theCells.emplace_back(Coord{2, 3});
    theCells.emplace_back(Coord{2, 2});

}




