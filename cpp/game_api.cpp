// #include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include "game_runner.h"

using namespace emscripten;

static GameRunner current_game;

val get_gameboard() {
  uint8_t* board = (uint8_t*)malloc(9 * sizeof(sizeof(uint8_t)));
  current_game.board_as_arr(board);
  val ret = val(typed_memory_view(9 * sizeof(uint8_t), board));
  free(board);
  return ret;
}

void start_new_game() { current_game = GameRunner(); }

int game_result() {
  if (!current_game.has_game_ended()) {
    throw new invalid_argument("The game has not yet ended.");
  }
  return current_game.winner();
}

void print_state() { current_game.print_state(); }

bool has_game_ended() { return current_game.has_game_ended(); }

void make_ai_move() { current_game.make_ai_move(); }

void make_player_move(int idx) {
  int x = idx / 3;
  int y = idx % 3;
  current_game.make_move(x, y);
}

int get_winner() { return current_game.winner(); }

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("start_new_game", &start_new_game);
  emscripten::function("get_gameboard", &get_gameboard);
  emscripten::function("game_result", &game_result);
  emscripten::function("has_game_ended", &has_game_ended);
  emscripten::function("print_state", &print_state);
  emscripten::function("make_ai_move", &make_ai_move);
  emscripten::function("make_player_move", &make_player_move);
  emscripten::function("get_winner", &get_winner);
  emscripten::enum_<player>("player")
      .value("NO_ONE", NO_ONE)
      .value("PLAYER_1", PLAYER_1)
      .value("PLAYER_2", PLAYER_2);
}

int main() { current_game = GameRunner(); }
