#include "graphicsdisplay.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(size_t board_cols, size_t board_rows) {
  xw.fillRectangle(0, 0, xw_width/2*0.95, xw_width, Xwindow::White); 

  xw.drawString(xw_width/2*0.05, 30, "Level: 0"); 
  xw.drawString(xw_width/2*0.05, 45, "Score: 0"); 
  xw.drawString(xw_width/2*1.2, 45, "Next Piece: "); 
  xw.drawString(xw_width/2*0.05, 60, "-----------"); 

  for (size_t i = 0; i < num_rows; i++){
    vector <char> dp_row; 
    for (size_t j = 0; j < num_cols; j++){
      dp_row.emplace_back(' ');
    }
    theDisplay.emplace_back(dp_row);
  }
} 

Info GraphicsDisplay::getInfo() const { return Info{-1, 0, 0, ' ', false, false, false, nullptr}; } 


int GraphicsDisplay::getColor(char type){ 
  if (type == 'S') return Xwindow::Green; 
  if (type == 'O') return Xwindow::Yellow; 
  if (type == 'T') return Xwindow::Purple; 
  if (type == 'J') return Xwindow::Blue; 
  if (type == 'L') return Xwindow::Orange; 
  if (type == 'I') return Xwindow::Cyan; 
  if (type == 'Z') return Xwindow::Red; 
  if (type == '*') return Xwindow::Gray; 
  return Xwindow::White;
}

void GraphicsDisplay::notify(Subject<Info> &notifiedBy){
  int row;
  int col;
  char type;

  if (notifiedBy.getInfo().type == 'B') {
    xw.fillRectangle(xw_width/2*0.05, 15, 100, 50, Xwindow::White);
    xw.drawString(xw_width/2*0.05, 30, "Level: " + to_string(notifiedBy.getInfo().level));   
    xw.drawString(xw_width/2*0.05, 45, "Score: " + to_string(notifiedBy.getInfo().row)); 
    xw.fillRectangle(xw_width/2*1.2, 30, 100, 500, Xwindow::White); 

    vector<Coord> abs = notifiedBy.getInfo().block->get_theCells();
    for (size_t i = 0; i < abs.size(); i++) {
      int col = abs.at(i).x;
      int row = abs.at(i).y;
      xw.drawString(xw_width/2*1.2, 45, "Next Piece: "); 
      xw.fillRectangle(col * cell_width + 301, row * cell_height + 101, cell_width - 1, cell_height - 1, getColor(notifiedBy.getInfo().block->getType()));
    }


  } else {
    row = notifiedBy.getInfo().row;
    col = notifiedBy.getInfo().col; 
    type = notifiedBy.getInfo().type;
    theDisplay.at(row).at(col) = type;
    xw.fillRectangle(col * cell_width + 1, row * cell_height + 101, cell_width - 1, cell_height - 1, getColor(type)); 
  }
  if (notifiedBy.getInfo().type == 'B' && notifiedBy.getInfo().isBlind == true && 
      notifiedBy.getInfo().detachObs == false && notifiedBy.getInfo().isSet == false) { 
    blind = true;
  } 
  
  if (blind) {
    for (int i = 2; i < 11; i++) {
      for (int j = 2; j < 8; j++) { 
        xw.fillRectangle(j * cell_width, i * cell_height + 100, cell_width, cell_height, Xwindow::Black);  
      }
    }
  }
}




