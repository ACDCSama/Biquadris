#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "block.h"
#include <memory>

struct Info {
  int level;
  size_t row, col;
  char type;
  bool isSet;
  bool detachObs;
  bool isBlind;
  std::shared_ptr<Block> block;
};

#endif



