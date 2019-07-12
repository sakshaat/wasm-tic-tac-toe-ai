#include <array>
#include <iostream>
#include <vector>

using namespace std;

enum player { NO_ONE, PLAYER_1, PLAYER_2 };

class GameState {
 private:
  array<array<player, 3>, 3> state;
  int empty_spots;

 public:
  GameState();
  GameState(const GameState& other);
  void print_state();

  bool empty_tile(int x, int y);
  player winner();
  void move(int x, int y, player t);
  bool board_full();
  vector<pair<int, int>> get_empty_tiles();
  void board_as_arr(uint8_t* board);
};
