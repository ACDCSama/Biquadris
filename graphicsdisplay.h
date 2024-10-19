#ifndef GD_H
#define GD_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
#include "window.h"

class Cell;

class GraphicsDisplay: public Observer<Info> {
  protected:
    bool blind = false;
    bool uninit_blind = false;

    const size_t xw_width = 500;
    const size_t xw_height = 500;

    const size_t cell_width = 20;
    const size_t cell_height = 20; 

    const size_t num_rows = 18;
    const size_t num_cols = 11;

    std::vector<std::vector<char>> theDisplay;
      
    Xwindow xw; 
  
  public:
    const int cols = 11;
    const int rows = 18;

    GraphicsDisplay(size_t board_cols, size_t board_rows); 
    void notify(Subject<Info> &notifiedBy) override;
    Info getInfo() const override;
    int getColor(char type);

};
#endif



