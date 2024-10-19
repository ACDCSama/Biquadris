#ifndef BIQUADRIS_H
#define BIQUADRIS_H
#include <vector>
#include <map>
#include "board.h"
#include "commandinterpreter.h"

class Biquadris {
  const size_t BRow = 18;
  const size_t BCol = 11;
  const int space_between_boards = 10;                                
  const int longest_row_width = 2 * BCol + space_between_boards;  
  const std::map<std::string, std::string> cmds =
    { {"rename", "rename"}, {"left", "left"}, {"right", "right"}, {"down", "down"},
      {"clockwise", "clockwise"}, {"counterclockwise", "counterclockwise"}, {"drop", "drop"},
      {"levelup", "levelup"}, {"leveldown", "leveldown"}, {"norandom", "norandom"}, {"random", "random"},
      {"sequence", "sequence"}, {"I", "I"}, {"J", "J"}, {"L", "L"}, {"O", "O"}, {"S", "S"},
      {"Z", "Z"}, {"T", "T"}, {"restart", "restart"}, {"blind", "blind"}, {"force", "force"}, {"heavy", "heavy"},
      {"help", "help"} }; 

protected:
  std::vector<Board *> boards;
  std::vector<int> drops;
  CommandInterpreter ci {cmds}; 
  size_t highscore = 0;
  size_t curPlayer = 0;
  size_t numPlayers = 2;  
  int start_level = 0;
  bool isHeavy = false;
  int seed = time(NULL);
  std::vector<std::string> scriptfilen = {"sequence1.txt", "sequence2.txt"};
  std::vector<std::vector<char>> blockSeq = { {}, {} };

  void setSeed(int seed);
  void setStartLevel(int startLevel);
  void restart();
  void printGame();  
  void readArgs(int argc, char *argv[]);
  void readCmd();
  void exCmd(int times, std::string cmd);
  void setScript1(std::string fname);
  void setScript2(std::string fname);
  void init(); 
  bool allGamesOver(); 

public:
  ~Biquadris();
  void play(int numPlayers, int argc, char *argv[]);

};

#endif





