#include "biquadris.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {  
  Biquadris game; 
  while (true) {
    if(cin.eof()) break;
    game.play(2, argc, argv);
  }
}




