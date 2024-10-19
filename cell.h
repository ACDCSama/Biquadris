#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "block.h"
#include "coord.h"


class Cell : public Subject<Info>, public Observer<Info> {
  int level;
  const size_t r, c;
  char type = ' ';
  bool isSet;
  bool detachObs;
  bool isBoard = false;
  std::shared_ptr<Block> block;
  
 public:
  Cell(size_t r, size_t c);
  void setCell(Info info);    
  void notify(Subject<Info> &whoFrom) override;
  Info getInfo() const override;
};
#endif




