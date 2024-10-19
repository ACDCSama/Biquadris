#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include "biquadris.h"
using namespace std;


void Biquadris::play(int numPlayers, int argc, char *argv[]){
  numPlayers = numPlayers;
  readArgs(argc, argv);
  char script;
  ifstream sfile;
  sfile.open(this->scriptfilen[0]);
  while (true) {
    if (sfile.eof()) break;
    if (sfile >> script) blockSeq[0].emplace_back(script);
  }
  sfile.close();

  ifstream sfile2;
  sfile2.open(this->scriptfilen[1]);
  while (true) {
    if (sfile2.eof()) break;
    if (sfile2 >> script) blockSeq[1].emplace_back(script);
  }
  sfile2.close();
  init();   
}

void Biquadris::init(){
  for (size_t i = 0; i < numPlayers; i++){
    Board* b = new Board(start_level);
    b->setSeq(this->blockSeq[i]);
    b->init(BCol, BRow);
    boards.emplace_back(b); 
  }  
  printGame();
  readCmd(); 
  restart();
}


void Biquadris::restart(){
  for (size_t i = 0; i < boards.size(); i++){
    delete boards[i];
    boards[i] = nullptr;
  }
  boards.clear(); 

  curPlayer = 0; 
  highscore = 0; 
  isHeavy = false; 
}

void Biquadris::setSeed(int seed) { this->seed = seed; }

void Biquadris::setStartLevel(int start_level) { this->start_level = start_level; }

void Biquadris::setScript1(string fname) { this->scriptfilen[0] = fname; }

void Biquadris::setScript2(string fname) { this->scriptfilen[1] = fname; }

void Biquadris::readArgs(int argc, char *argv[]){
  for (int i = 1; i < argc; i++){
    string cmdin;
    cmdin = {argv[i]};

    if (cmdin == "-seed") {
      istringstream ss(argv[i++]);
      int seedin;
      ss >> seedin;
      if (seed > 0){
        setSeed(seedin);
        srand(seed);
      }
    } else if (cmdin == "-scriptfile1") {
      istringstream ss(argv[i++]); 
      string fname; 
      ss >> fname; 
      setScript1(fname); 
    } else if (cmdin == "-scriptfile2") {
      istringstream ss(argv[i++]); 
      string fname; 
      ss >> fname; 
      setScript2(fname);    
    } else if (cmdin == "-startlevel") {
      int lvlin;
      istringstream ss(argv[i++]);
      ss >> lvlin; 
      if (lvlin >= 0 && lvlin <= 4) setStartLevel(lvlin);
    }
  }
}

void Biquadris::readCmd(){
  curPlayer = 0; 
  string user_cmd;

  while (true) {
    if (boards[curPlayer]->getDrops() > 0) {
      exCmd(boards[curPlayer]->getDrops(), "drop");
      printGame();
    } else {
      cin >> user_cmd;
      if(cin.eof()) break;
      int times = ci.parseTimes(user_cmd);
      string cmd = ci.parseCommands(user_cmd, times);

      if (cmd == "sequence") {
        string file;
        cin >> file;
        ifstream myfile;
        myfile.open(file);
        string file_cmd;
        while (true) {
          if (myfile.eof()) break;
          if (myfile >> file_cmd) {
            times = ci.parseTimes(file_cmd);
            string new_cmd = ci.parseCommands(file_cmd, times);
            exCmd(times, new_cmd);
            printGame(); 
          }
        }
        myfile.close();
      }  else if (cmd == "restart") {
          return;
      } else if (!allGamesOver() || (allGamesOver() && cmd == "restart")) {
          exCmd(times, cmd);
          printGame(); 
      }
    }
  }
}

void Biquadris::exCmd(int times, string cmd){
  Board* currboard = boards[curPlayer];
  if (cmd == "rename") {
    string old_name;
    string new_name;
    cin >> old_name >> new_name;
    ci.rename(old_name, new_name);
  } else if (cmd == "left") {
    currboard->moveLeft(times);  
  } else if (cmd == "right") {
      currboard->moveRight(times);   
  } else if (cmd == "down") {
      currboard->moveDown(times);
  } else if (cmd == "clockwise") {
    currboard->rotateCw(times);
  } else if (cmd == "counterclockwise") {
      currboard->rotateCcw(times); 
  } else if (cmd == "drop") {
    if (times > 1) {
      currboard->changeDrops(times - 1);
    }
    currboard->dropBlock();
    currboard->unsetBlind();

    if (!boards[(curPlayer + 1) % (numPlayers)]->gameOver()) curPlayer = (curPlayer + 1) % (numPlayers);

    if(currboard->getRowsCleared() >= 2){ 
      cout << "Enter a special action." << endl; 
      string special_action_cmd;  
      cin >> special_action_cmd; 
      special_action_cmd = ci.parseCommands(special_action_cmd, times);
      if (special_action_cmd == "blind") {
        currboard = boards[curPlayer];
        currboard->setBlind();
      } else if (special_action_cmd == "heavy") {
        currboard = boards[curPlayer];
        currboard->setHeavy();
      } else if (special_action_cmd == "force") {
          string force_to;
          cin >> force_to;
          exCmd(1, force_to);
      }
    }

    if (!boards[(curPlayer + 1) % (numPlayers)]->gameOver()) curPlayer = (curPlayer + 1) % (numPlayers);

    boards[curPlayer]->setRowsCleared();

  } else if (cmd == "levelup") {
    if (currboard->getLevel() + times <= 4) {
      currboard->levelup(times);
      currboard->setRandom();
      currboard->setLevelPtr(); 
    }
  } else if (cmd == "leveldown") {
    if (currboard->getLevel()- times >= 0) {
      currboard->leveldown(times); 
      currboard->setRandom();
      currboard->setLevelPtr(); 
    }
  }  else if (times == 1) {
    if (cmd == "norandom" && (boards[curPlayer])->getLevel() >= 3) {
      string fname; 
      cin >> fname; 
      boards[curPlayer]->resetSeq(fname); 
      currboard->unsetRandom();
      currboard->setLevelPtr(); 
    } else if (cmd == "random" && boards[curPlayer]->getLevel() >= 3) {
      currboard->setRandom();
      currboard->setLevelPtr(); 
    } else if (cmd == "I"){
      currboard->setCurBlock(currboard->getLevel(), 'I'); 
    } else if (cmd == "J"){
      currboard->setCurBlock(currboard->getLevel(), 'J');
    } else if (cmd == "L"){
      currboard->setCurBlock(currboard->getLevel(), 'L');
    } else if (cmd == "O"){
      currboard->setCurBlock(currboard->getLevel(), 'O'); 
    } else if (cmd == "T"){
      currboard->setCurBlock(currboard->getLevel(), 'T');
    } else if (cmd == "S"){
      currboard->setCurBlock(currboard->getLevel(), 'S');
    } else if (cmd == "Z"){
      currboard->setCurBlock(currboard->getLevel(), 'Z');
    } else if (cmd == "restart") {
      restart(); 
    } else if (cmd == "help"){
      ci.printCommands();
    }
  } else {
    cin.ignore(); 
    cin.clear(); 
    cout << "Invalid. Type 'help' for list of valid commands." << endl; 
  }
  if (boards[curPlayer]->getDropped()) {
    boards[curPlayer]->toggleDropped();
    if (!boards[(curPlayer + 1) % (numPlayers)]->gameOver()) {
      curPlayer = (curPlayer + 1) % (numPlayers);
    }
  }
}

bool Biquadris::allGamesOver(){
  for (size_t i = 0; i < boards.size(); i++) if (!(boards[i]->gameOver())) return false; 
  return true; 
}
void Biquadris::printGame(){ 
   for (size_t i = 0; i < boards.size(); i++) if (boards[i]->gameOver()) boards[i]->changeDrops(0);

  if (allGamesOver()){
    cout << "All Games Over" << endl; 
    return; 
  }

  cout << endl;

  cout << left << setw(BCol - to_string(boards.at(0)->getLevel()).length()) << "Level: " << right << boards.at(0)->getLevel()   
       << setw(space_between_boards - 1) << " " 
       << left << setw(BCol - to_string(boards.at(1)->getLevel()).length()) << "Level: " << right << boards.at(1)->getLevel() 
       << endl; 

  cout << left << setw(BCol - to_string(boards.at(0)->getScore()).length()) << "Score: " << right << boards.at(0)->getScore()   
       << setw(space_between_boards - 1) << " "
       << left << setw(BCol - to_string(boards.at(1)->getScore()).length()) << "Score: " << right << boards.at(1)->getScore() 
       << endl; 

  cout << left << string(BCol, '-') 
        << right << setw(space_between_boards + BCol - 1) << string(BCol, '-') << endl;

  for (size_t i = 0; i < BRow; i++){
    boards.at(0)->printRow(i);
    cout << setw(space_between_boards); 
    boards.at(1)->printRow(i); 
    cout << endl; 
  }
  
  cout << left << string(BCol, '-') << right << setw(space_between_boards + BCol - 1) << string(BCol, '-') << endl;

  cout << "Next:" << setw(space_between_boards + BCol - 1) << "Next:" << endl; 

  for (size_t i = 2; i < 4; i++){
    boards.at(0)->getNextBlock()->printRow(i, BCol);
    cout << setw(space_between_boards); 
    boards.at(1)->getNextBlock()->printRow(i, BCol); 
    cout << endl; 
  }
  cout << endl; 

}

Biquadris::~Biquadris() { for (size_t i = 0; i < boards.size(); i++) delete boards[i]; }
