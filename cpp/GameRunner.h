#include "GameTree.h"

class GameRunner {
 private:
  GameState state;
  player turn;
  pair<int, int> calculate_ai_move();
  void switch_turn();

 public:
  bool has_game_ended();
  void make_move(int x, int y);
  void print_state();
  player winner();
  GameRunner();
  void make_ai_move();
  void board_as_arr(uint8_t* board);
};