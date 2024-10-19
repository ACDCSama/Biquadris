#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "coord.h"

class TextDisplay;
class GraphicsDisplay; 
class Coord; 

class Block {
 protected: 

    int x_left = 1;       
    int y_bottom = 3; 
    int level; 
    char type;

    std::vector<Coord> theCells;     
 
 public:
    Block(int level, char type); 

    void moveRight();
    void moveLeft();
    void moveDown();
    void rotateCW();

    Coord getCoords(); 
    void setCoords(int x, int y);
    char getType();
    int getLevel() const;
    std::vector<Coord> get_theCells();   
    void set_theCells(std::vector<Coord> pos); 
    void removeCoords(Coord& location); 
    void printRow(int r, int board_width); 
};

#endif





