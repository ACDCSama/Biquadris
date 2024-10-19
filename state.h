#ifndef STATE_H
#define STATE_H

enum class StateType { NewPiece, Relay, Reply };
enum class Colour { NoColour, Black, White };
enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
  StateType type;
  Colour colour;
  Direction direction;
};

#endif




