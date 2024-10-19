#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
class Cell;

class TextDisplay: public Observer<Info> {
  std::vector<std::vector<char>> theDisplay;

  public:
    TextDisplay(size_t board_cols, size_t board_rows);
    Info getInfo() const override;
    void notify(Subject<Info> &notifiedBy) override;
    void printRow(size_t r);
    void printBlind(size_t r);

};
#endif



