#include "level2.h"

Level2::Level2(int seed):Level{2}, seed{seed}{}

std::shared_ptr<Block> Level2::genBlock(){
    int random = (rand() % 7) + 1;  
    std::shared_ptr<Block> new_block;
    if (random == 1) return std::make_shared<SBlock>(level);
    if (random == 2) return std::make_shared<ZBlock>(level);
    if (random == 3) return std::make_shared<OBlock>(level);
    if (random == 4) return std::make_shared<LBlock>(level);
    if (random == 5) return std::make_shared<JBlock>(level);
    if (random == 6) return std::make_shared<TBlock>(level);
    if (random == 7) return std::make_shared<IBlock>(level);
    return nullptr;
}




