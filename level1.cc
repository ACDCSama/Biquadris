#include "level1.h"

using namespace std; 
Level1::Level1(int seed):Level{1}, seed{seed}{}

std::shared_ptr<Block> Level1::genBlock(){
    int random = (rand() % 12) + 1;  
    std::shared_ptr<Block> new_block;
    if (random == 1) return std::make_shared<SBlock>(level);
    if (random == 2) return std::make_shared<ZBlock>(level);
    if (random == 3 || random == 4) return std::make_shared<OBlock>(level);
    if (random == 5 || random == 6) return std::make_shared<LBlock>(level);
    if (random == 7 || random == 8) return std::make_shared<JBlock>(level);
    if (random == 9 || random == 10) return std::make_shared<TBlock>(level);
    if (random == 11 || random == 12) return std::make_shared<IBlock>(level);
    return nullptr;
}




