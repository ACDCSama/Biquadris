#include "level4.h"

Level4::Level4(int seed, std::vector<char> sequence, bool isRandom)
    :Level{4}, seed{seed}, sequence{sequence}, isRandom{isRandom} {}

std::shared_ptr<Block> Level4::genBlock(){
    
    if (!isRandom) {
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
    } else {
        int random = (rand() % 9) + 1;  
        std::shared_ptr<Block> new_block;
        if (random == 1 || random == 2) return std::make_shared<SBlock>(level);
        if (random == 3 || random == 4) return std::make_shared<ZBlock>(level);
        if (random == 5) return std::make_shared<OBlock>(level);
        if (random == 6) return std::make_shared<LBlock>(level);
        if (random == 7) return std::make_shared<JBlock>(level);
        if (random == 8) return std::make_shared<TBlock>(level);
        if (random == 9) return std::make_shared<IBlock>(level);
        return nullptr;
    }
}




