
#include "jblock.h"
using namespace std; 
 
JBlock::JBlock(int level) : Block{level, 'J'} {

    theCells.emplace_back(Coord{1, 3});
    theCells.emplace_back(Coord{0, 3});
    theCells.emplace_back(Coord{2, 3});
    theCells.emplace_back(Coord{0, 2});

}




