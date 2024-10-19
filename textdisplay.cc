#include "textdisplay.h"
#include "subject.h"
using namespace std;

TextDisplay::TextDisplay(size_t board_cols, size_t board_rows) {
  for (size_t i = 0; i < board_rows; i++){
    vector <char> dp_row; 
    for (size_t j = 0; j < board_cols; j++){
      dp_row.emplace_back(' ');
    }
    theDisplay.emplace_back(dp_row);
  }
}

Info TextDisplay::getInfo() const { return Info{0, 0, 0, ' ', false, false, false}; }

void TextDisplay::notify(Subject<Info> &notifiedBy){
  int row = notifiedBy.getInfo().row;
  int col = notifiedBy.getInfo().col; 
  char c = notifiedBy.getInfo().type;
  theDisplay.at(row).at(col) = c;
}

void TextDisplay::printRow(size_t row) {
  for (size_t i = 0; i < theDisplay.at(row).size(); i++) cout << theDisplay.at(row).at(i);
}


void TextDisplay::printBlind(size_t row){
  for (size_t i = 0; i < theDisplay.at(row).size(); i++){
    if (i >= (3-1) && i <= (9-1)){
      cout << "?"; 
    } else {
      cout << theDisplay.at(row).at(i); 
    }
  }
}




