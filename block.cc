#include "block.h"

using namespace std; 
class Coord; 

Block::Block(int level, char type): level{level}, type{type} {}

int getMaxY(vector<Coord> v){
  int max = v.front().y; 
  for (size_t i = 1; i < v.size(); i++) if (v[i].y > max) max = v[i].y;
  return max; 
}

int getMaxX(vector<Coord> v){
  int max = v.front().x; 
  for (size_t i = 1; i < v.size(); i++) if (v[i].x > max) max = v[i].x; 
  return max; 
}

int getMinX(vector<Coord> v){
  int min = v.front().x; 
  for (size_t i = 1; i < v.size(); i++) if (v[i].x < min) min = v[i].x;
  return min; 
}

int getMinY(vector<Coord> v){
  int min = v.front().y; 
  for (size_t i = 1; i < v.size(); i++)if (v[i].y < min) min = v[i].y;
  return min; 
}


void Block::moveRight() {
  x_left += 1;
  for (size_t i = 0; i < theCells.size(); i++) theCells[i].x += 1;
}

void Block::moveLeft() {
  x_left -= 1;
  for (size_t i = 0; i < theCells.size(); i++) theCells[i].x -= 1;
}

void Block::moveDown() {
    y_bottom += 1;
    for (size_t i = 0; i < theCells.size(); i++) theCells[i].y += 1;
}

void Block::rotateCW(){
    vector<Coord> copy = theCells; 
    Coord around {getMinX(theCells), getMaxY(theCells)}; 
    for (size_t i = 0; i < 4; i++){
        theCells[i].x -= getMaxX(copy) - getMinX(copy); 
        theCells[i] = Coord{-(theCells[i].y-around.y) + around.x, (theCells[i].x-around.x) + around.y};
    }
}
 
Coord Block::getCoords() { return Coord{x_left, y_bottom}; }

void Block::setCoords(int x, int y) {
    x_left = x; 
    y_bottom = y;
}

vector<Coord> Block::get_theCells() { return theCells; }


char Block::getType() { return type; }

void Block::set_theCells(vector<Coord> pos) { theCells = pos; }

void Block::removeCoords(Coord& location) {
  for (int i = 0; i < theCells.size(); i++) 
    if (theCells[i].x == location.x && theCells[i].y == location.y) theCells.erase(theCells.begin() + i);
}

int Block::getLevel() const{ return level; }

void Block::printRow(int r, int board_width){
  for (int i = 0; i < board_width; i++){
    bool found = false; 
    for (int j = 0; j < 4; j++){
      if (theCells[j].y == r && theCells[j].x == i){
          cout << type; 
          found = true; 
          break; 
      }
    }
    if (!found) cout << " "; 
  }
}




