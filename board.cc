#include "board.h"
using namespace std; 

Info Board::getInfo() const{
  if (isBlind && initBlind) return Info{getLevel(), getScore(), 0, 'B', false, false, true, nextBlock}; 
  if (isBlind && !initBlind) return Info{getLevel(), getScore(), 0, 'B', true, false, false, nextBlock}; 
  return Info{getLevel(), getScore(), 0, 'B', false, false, false, nextBlock}; 
}

Board::Board(int start_level):level{start_level} {}

Board::~Board() {
  delete td;
  delete ob;
}

void Board::init(size_t BCol, size_t BRow){
  l = nullptr;
  td = new TextDisplay{BCol, BRow};
  ob = new GraphicsDisplay{BCol, BRow}; 

  for (size_t i = 0; i < BRow; i++){
    vector <Cell> grid_row; 
    for (size_t j = 0; j < BCol; j++){
      grid_row.emplace_back(Cell{i, j});
    }
    theBoard.emplace_back(grid_row); 
  }
  setLevelPtr(); 
  curBlock = l->genBlock();
  nextBlock = l->genBlock();
  activeBlocks.emplace_back(curBlock);
  activeBlocks.emplace_back(nextBlock);
  print(curBlock);
}

bool Board::inRange(int c, int r, int max_width, int max_height) const {
  return (c >= 0 && c < max_width && r >= 0 && r < max_height); 
}

bool Board::isEmptyCell(int r, int c) const { return (theBoard[r][c].getInfo().type == ' '); }

bool Board::Movable(vector<Coord> c) const {
  for (size_t i = 0; i < c.size(); i++)
    if (!inRange(c[i].x, c[i].y, theBoard[0].size(), theBoard.size()) || !isEmptyCell(c[i].y, c[i].x)) return false;
  return true;
}

bool Board::isRowFull(int r){
  for (size_t c = 0; c < theBoard[r].size(); c++) 
    if (isEmptyCell(r, c)) return false;
  return true; 
}

void Board::changeDrops(int changeTo) { dropsLeft = changeTo; }

int Board::getDrops() const { return dropsLeft; }


int Board::getRowsCleared() const { return rowsCleared; }

void Board::setRowsCleared() { rowsCleared = 0; }

void Board::printRow(size_t i){
  if (isBlind && i >= (3-1) && i <= (12-1)) td->printBlind(i);
  else td->printRow(i);
}

void Board::moveRight(size_t times) {
  unprint(curBlock); 
  vector<Coord> copy = curBlock->get_theCells(); 
  for (size_t i = 0; i < times; i++){
    curBlock->moveRight();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      break; 
    }
  }

  copy = curBlock->get_theCells(); 

  if (isHeavy()) {
    if (getLevel() == 3 || getLevel() == 4) curBlock->moveDown();
      curBlock->moveDown();
      curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      print(curBlock);
      dropBlock();
      return;
    }
  } 
  if (getLevel() == 3 || getLevel() == 4) {
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) curBlock->set_theCells(copy); 
  }
  print(curBlock);
}

void Board::moveLeft(size_t times) {
  unprint(curBlock); 
  vector<Coord> copy = curBlock->get_theCells(); 
  for (size_t i = 0; i < times; i++){
    curBlock->moveLeft();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      break; 
    }
  }
  copy = curBlock->get_theCells(); 
  if (isHeavy()) {
    if (getLevel() == 3 || getLevel() == 4) curBlock->moveDown();
      curBlock->moveDown();
      curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      print(curBlock);
      dropBlock();
      return;
    }
  } 
  if (getLevel() == 3 || getLevel() == 4) {
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) curBlock->set_theCells(copy); 
  }
  print(curBlock);
}

void Board::moveDown(size_t times) {
  unprint(curBlock); 
  vector<Coord> copy = curBlock->get_theCells(); 
  for (size_t i = 0; i < times; i++){
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      break; 
    }
  }
  copy = curBlock->get_theCells(); 
  if (isHeavy()) {
    if (getLevel() == 3 || getLevel() == 4) curBlock->moveDown();
      curBlock->moveDown();
      curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      print(curBlock);
      dropBlock();
      return;
    }
  } 
  if (getLevel() == 3 || getLevel() == 4) {
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) curBlock->set_theCells(copy); 
  }
  print(curBlock);

}

void Board::rotateCw(size_t times){
  times %= 4; 
  unprint(curBlock); 
  vector<Coord> copy = curBlock->get_theCells(); 
  for (size_t i = 0; i < times; i++){
    curBlock->rotateCW();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      break; 
    }
  }
  copy = curBlock->get_theCells(); 
  if (isHeavy()) {
    if (getLevel() == 3 || getLevel() == 4) curBlock->moveDown();
      curBlock->moveDown();
      curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(copy); 
      print(curBlock);
      dropBlock();
      return;
    }
  } 
  if (getLevel() == 3 || getLevel() == 4) {
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) curBlock->set_theCells(copy); 
  }
  print(curBlock);
}

void Board::rotateCcw(size_t times) { rotateCw(4 - times % 4); }

void Board::dropBlock() {
  unprint(curBlock); 
  for (int r = 0; r < theBoard.size(); r++) {
    vector<Coord> currCopy = curBlock->get_theCells(); 
    curBlock->moveDown();
    if (!Movable(curBlock->get_theCells())) {
      curBlock->set_theCells(currCopy); 
      break;
    } 
  }
  print(curBlock);
  checkFullRows();
  unsetBlind();
  notifyObservers();

  if (falling_count % 5 == 0 && falling_count != 0 && getLevel() == 4) {
    std::shared_ptr<XBlock> xblock = std::make_shared<XBlock>(4);
    activeBlocks.emplace_back(xblock);
    for (size_t i = 0; i < theBoard.size(); i++) {
      vector<Coord> xcopy = xblock->get_theCells(); 
      unprint(xblock); 
      xblock->moveDown();
      
      if (!Movable(xblock->get_theCells())) {
        xblock->set_theCells(xcopy); 
        break;
      }
      print(xblock);
    }
    falling_count = 0;
  }
  
  genNewBlock(); 
  toggleDropped();
}


void Board::clearRow(int r) {

  int width = theBoard[0].size();

  for (int j = 0; j < width; j++) {
    if (theBoard[r][j].getObSize() == 1) score += (theBoard[r][j].getInfo().level + 1) * (theBoard[r][j].getInfo().level + 1);
    Coord self_remove{j, r};
    theBoard[r][j].getInfo().block->removeCoords(self_remove);
    theBoard[r][j].setCell(Info{-1, 0, 0, ' ', false, true, false, nullptr});
    theBoard[r][j].notifyObservers();
    theBoard[r][j].detachAll();
    theBoard[r][j].setCell(Info{-1, 0, 0, ' ', false, false, false, nullptr});
  }
  
}

void Board::multiRows(int r, vector<int>& validator) {

  int width = theBoard[0].size();
  
  for (int i = 0; i < width; i++) {
    if (theBoard[r][i].getInfo().type != ' ') {
      std::shared_ptr<Block> to_be_moved = theBoard[r][i].getInfo().block;
      for (size_t j = 0; j < activeBlocks.size(); j++) {
        if (to_be_moved == activeBlocks[j] && validator[j] == 0) {
          unprint(to_be_moved);
          vector<Coord> copy = to_be_moved->get_theCells(); 
          to_be_moved->moveDown();
          if (!Movable(to_be_moved->get_theCells())) to_be_moved->set_theCells(copy); 
          else validator[j] = 1;
          print(to_be_moved);
        }
      }
    }
  }

  for (int i = width - 1; i >= 0; i--) {
    if (theBoard[r][i].getInfo().type != ' ') {
      std::shared_ptr<Block> to_be_moved = theBoard[r][i].getInfo().block;
      for (size_t j = 0; j < activeBlocks.size(); j++) {
        if (to_be_moved == activeBlocks[j] && validator[j] == 0) {
          unprint(to_be_moved);
          vector<Coord> copy = to_be_moved->get_theCells(); 
          to_be_moved->moveDown();
          if (!Movable(to_be_moved->get_theCells())) {
            for (size_t k = 0; k < copy.size(); k++) if (copy.at(k).y < r + 1) copy.at(k).y += 1;
            to_be_moved->set_theCells(copy); 
          }
          validator[j] = 1;
          print(to_be_moved);
        }
      }
    }
  }

}

void Board::checkFullRows(){
  int rows_cleared = 0;
  bool one_row_cleared = false;
  for (size_t r = 0; r < theBoard.size(); r++){
    if (isRowFull(r)){
      rowsCleared++;
      clearRow(r); 
      for (size_t i = 0; i < activeBlocks.size(); i++) 
        if(activeBlocks[i]->get_theCells().size() == 0) activeBlocks.erase(activeBlocks.begin() + i);

      vector<int> validator;

      for (size_t i = 0; i < activeBlocks.size(); i++) validator.emplace_back(0);
      for (int i = r; i > 0; i--) multiRows(i - 1, validator);
      rows_cleared++;
      one_row_cleared = true;
    }
  }

  if (one_row_cleared) score += (rows_cleared + getLevel()) * (rows_cleared + getLevel());

  if (rows_cleared == 0 && getLevel() == 4) falling_count += 1;
  if (rows_cleared > 0 && getLevel() == 4) falling_count = 0;
}

void Board::genNewBlock(){

  curBlock = nextBlock;
  if (!Movable(curBlock->get_theCells())){
    this->lost = true; 
    cout << "Game over" << endl;
    return; 
  }
  
  nextBlock = l->genBlock();
  activeBlocks.emplace_back(nextBlock);

  print(curBlock);

}

void Board::setBlind(){
  isBlind = true; 
  initBlind = true;
  notifyObservers();
  initBlind = false;
}
void Board::unsetBlind(){
  initBlind = true;
  notifyObservers();
  isBlind = false;
  initBlind = false;
}


void Board::setRandom() { isRandom = true; }
void Board::unsetRandom() { isRandom = false; }

void Board::setCurBlock(int level, char type) {
  unprint(curBlock);

  for (size_t i = 0; i < activeBlocks.size(); i++) if(activeBlocks[i] == curBlock) activeBlocks.erase(activeBlocks.begin() + i);

  if (type == 'S') curBlock = std::make_shared<SBlock>(level);
  else if (type == 'Z') curBlock = std::make_shared<ZBlock>(level);
  else if (type == 'O') curBlock = std::make_shared<OBlock>(level);
  else if (type == 'L') curBlock = std::make_shared<LBlock>(level);
  else if (type == 'J') curBlock = std::make_shared<JBlock>(level);
  else if (type == 'T') curBlock = std::make_shared<TBlock>(level);
  else if (type == 'I') curBlock = std::make_shared<IBlock>(level);
  else return; 
  activeBlocks.emplace_back(curBlock);
  print(curBlock);
}

void Board::setLevelPtr() {
  l = nullptr;
  if (level == 0) l = make_shared<Level0>(blockSequence); 
  if (level == 1) l = make_shared<Level1>(seed); 
  if (level == 2) l = make_shared<Level2>(seed); 
  if (level == 3) l = make_shared<Level3>(seed, blockSequence, isRandom); 
  if (level == 4) l = make_shared<Level4>(seed, blockSequence, isRandom); 
}

void Board::levelup(size_t times) {
  if (getLevel() + times <= 4) {
    level += times;
    if (getObSize() > 0) notifyObservers();
  }
}

void Board::leveldown(size_t times) {
  int amount = times;
  if (getLevel() - amount >= 0) {
    level -= amount;
    if (getObSize() > 0) notifyObservers();
  }
}

int Board::getLevel() const { return level; }

int Board::getScore() const { return score; }

std::shared_ptr<Block> Board::getNextBlock() const { return nextBlock; }

bool Board::gameOver() const{ return lost; }

bool Board::isHeavy() const { return heavy; }

void Board::toggleHeavy() {
  if (heavy) heavy = false;
  else heavy = true;
}

void Board::setHeavy() { heavy = true; }

bool Board::getDropped() const { return isDropped; }

bool Board::toggleDropped() {
  if (isDropped == false) isDropped = true;
  else isDropped = false;
}


void Board::setSeq(std::vector<char> seq) { blockSequence = seq; }

void Board::resetSeq(string fname) {
  char scriptBlock;

  ifstream sf;
  sf.open(fname);

  blockSequence.clear();

  while (true) {
    if (sf.eof()) break;
    if (sf >> scriptBlock) blockSequence.emplace_back(scriptBlock);
  }
  sf.close();
}

void Board::print(std::shared_ptr<Block> b){
  if (b == nullptr) return;
  vector<Coord> abs_location = b->get_theCells();
  for(size_t i = 0; i < abs_location.size(); i++) {
    int sub_row = abs_location[i].y;
    int sub_col = abs_location[i].x;
    for(size_t j = 0; j < abs_location.size(); j++) {
      int ob_row = abs_location[j].y;
      int ob_col = abs_location[j].x;
      if (sub_row == ob_row && sub_col == ob_col) {
        continue;
      } else {
        theBoard[sub_row][sub_col].attach(&theBoard[ob_row][ob_col]);
      }
    }
    theBoard[sub_row][sub_col].attach(td);
    attach(ob);
    theBoard[sub_row][sub_col].attach(ob);
  }

  int row = abs_location[0].y;
  int col = abs_location[0].x;
  theBoard[row][col].setCell(Info{b->getLevel(), row, col, b->getType(), false, false, false, b});
  theBoard[row][col].notifyObservers();
}

void Board::unprint(std::shared_ptr<Block> b) {
  if (b == nullptr) return;
  vector<Coord> abs_location = b->get_theCells();
  char c = ' ';
  theBoard[abs_location[0].y][abs_location[0].x].setCell(Info{0, 0, 0, c, false, false, false, nullptr});
  theBoard[abs_location[0].y][abs_location[0].x].notifyObservers();

  for(size_t i = 0; i < abs_location.size(); i++) {
    int sub_row = abs_location[i].y;
    int sub_col = abs_location[i].x;
    theBoard[sub_row][sub_col].detachAll();
  }
}





