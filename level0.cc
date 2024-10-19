#include "level0.h"
#include <memory>

Level0::Level0(std::vector<char> sequence): Level{0}, sequence{sequence} {}

std::shared_ptr<Block> Level0::genBlock() {
    char type = sequence[count];
    count += 1;
    if (count == sequence.size()) return nullptr;
    if (type == 'S') return std::make_shared<SBlock>(0); 
    if (type == 'Z') return std::make_shared<ZBlock>(0);
    if (type == 'O') return std::make_shared<OBlock>(0);
    if (type == 'T') return std::make_shared<TBlock>(0);
    if (type == 'J') return std::make_shared<JBlock>(0);
    if (type == 'I') return std::make_shared<IBlock>(0);
    if (type == 'L') return std::make_shared<LBlock>(0);
    return nullptr;
}
Level0::~Level0() {};





