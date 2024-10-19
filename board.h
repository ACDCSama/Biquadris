#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <memory>
#include "cell.h"
#include "info.h"
#include "block.h" 
#include "level.h"
#include "level0.h" 
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "textdisplay.h"
#include "observer.h"
#include "subject.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"
#include "jblock.h"
#include "zblock.h"
#include "coord.h"
#include "graphicsdisplay.h"

class TextDisplay;
class GraphicsDisplay; 
template <typename Info> class Observer;

class Board : public Subject<Info> { 
  protected: 
    std::vector<std::vector<Cell>> theBoard;
    TextDisplay *td = nullptr;
    Observer<Info> *ob = nullptr;
    std::shared_ptr<Block> curBlock;
    std::shared_ptr<Block> nextBlock;
    std::vector<std::shared_ptr<Block>> activeBlocks;
    std::vector<char> blockSequence;

    int seed = time(NULL);
    std::shared_ptr<Level> l; 
    int level;
    int dropsLeft = 0;
    int falling_count = 0;
    int score = 0; 
    bool isDropped = false;         
    bool lost = false; 
    bool heavy = false;
    int rowsCleared = 0; 
    bool isBlind = false; 
    bool initBlind = false;
    bool isRandom = true; 

    bool inRange(int c, int r, int max_width, int max_height) const;
    bool isEmptyCell(int r, int c) const;
    bool Movable(std::vector<Coord> c) const;
    bool isRowFull(int r); 
    void checkFullRows();
    void multiRows(int r, std::vector<int>& validator);
    void clearRow(int r);

  public:

    Info getInfo() const override;
    Board(int start_level = 0); 
    virtual ~Board();
    void init(size_t BCol, size_t BRow);
    virtual void genNewBlock();
    virtual void moveRight(size_t times = 1);
    virtual void moveLeft(size_t times = 1);
    virtual void moveDown(size_t times = 1);
    virtual void rotateCw(size_t times = 1); 
    virtual void rotateCcw(size_t times = 1); 
    virtual void levelup(size_t times = 1); 
    virtual void leveldown(size_t times = 1); 
    virtual void dropBlock();
    void setHeavy();
    bool getDropped() const;
    bool toggleDropped();
    void setBlind();
    void unsetBlind(); 
    void print(std::shared_ptr<Block> b);
    virtual void unprint(std::shared_ptr<Block> b);
    bool gameOver() const; 
    void printRow(size_t r);
    void setCurBlock(int level, char type);
    void setLevelPtr(); 
    void setSeq(std::vector<char> seq);
    void setRandom();
    void unsetRandom(); 
    void resetSeq(std::string fname);
    void changeDrops(int changeTo);
    int getDrops() const;
    int getRowsCleared() const;
    void setRowsCleared();
    int getLevel() const;
    int getScore() const;
    std::shared_ptr<Block> getNextBlock() const;
    bool isHeavy() const;
    void toggleHeavy();


};

#endif




