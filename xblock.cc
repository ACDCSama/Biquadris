#include "xblock.h"
using namespace std; 
 
XBlock::XBlock(int level) : Block{level, '*'} {
    theCells.emplace_back(Coord{5, 0});
}



