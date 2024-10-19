#include "tblock.h"
using namespace std; 
 
TBlock::TBlock(int level) : Block{level, 'T'} {
    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 2});
    theCells.emplace_back(Coord{1, 2});
    theCells.emplace_back(Coord{2, 2});
    
}



