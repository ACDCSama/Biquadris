#include "iblock.h"
using namespace std; 
 
IBlock::IBlock(int level) : Block{level, 'I'} {

    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 3});
    theCells.emplace_back(Coord{2, 3});
    theCells.emplace_back(Coord{3, 3});
}




