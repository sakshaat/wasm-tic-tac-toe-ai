#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

enum player { PLAYER_1, PLAYER_2, NO_ONE };

class GameState {
 private:
  array<array<player, 3>, 3> state;
  int empty_spots;

 public:
  GameState();
  GameState(const GameState &other);
  void print_state();

  bool empty_tile(int x, int y);
  player winner();
  void move(int x, int y, player t);
  bool board_full();
  vector<pair<int, int>> get_empty_tiles();
};
