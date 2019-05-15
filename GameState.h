#include <array>
#include <iostream>

using namespace std;

enum players { PLAYER_1, PLAYER_2, NO_ONE };

class GameState {
 private:
  array<array<players, 3>, 3> state;
  int empty_spots;

 public:
  GameState();
  void print_state();
  bool empty_tile(int x, int y);
  players winner();
  void move(int x, int y, players t);
  bool board_full();
};
