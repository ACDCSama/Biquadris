#include "cell.h"
#include <iostream>
#include <string> 
using namespace std;

Cell::Cell(size_t r, size_t c) : r{r}, c{c}, type{' '} {}

void Cell::notify(Subject<Info> &whoFrom){ 
    vector<Observer<Info> *> &observers = getObservers();
    if (whoFrom.getInfo().detachObs) {
      for (int i = 0; i < observers.size(); i++) {
        int row = observers[i]->getInfo().row;
        int col = observers[i]->getInfo().col;
        if (whoFrom.getInfo().row == row && whoFrom.getInfo().col == col) {
          detach(observers[i]);
          Coord cleared{col, row};
          block->removeCoords(cleared);
        }
      }
    } else {
      if (!whoFrom.getInfo().isSet) {
        Info info = whoFrom.getInfo();
        info.isSet = true;
        setCell(info);
        notifyObservers();
      }
    }
}


Info Cell::getInfo() const {
  return Info{level, r, c, type, isSet, detachObs, isBoard, block}; 
} 

void Cell::setCell(Info info) {
  this->type = info.type;
  this->level = info.level;
  this->isSet = info.isSet;
  this->detachObs = info.detachObs;
  this->block = info.block;
}




