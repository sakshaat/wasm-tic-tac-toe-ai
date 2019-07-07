#include "GameRunner.h"

GameRunner::GameRunner() {
  state = GameState();
  turn = PLAYER_1;

  // TODO Optimization
  // cout << "Building tree" << endl;
  // maintain the current state to reduce work
  // this->head = Node(state, turn);
  // cout << "Tree built." << endl;
}

void GameRunner::switch_turn() {
  this->turn = this->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

player GameRunner::winner() { return this->state.winner(); }

bool GameRunner::has_game_ended() {
  return NO_ONE != this->state.winner() || this->state.board_full();
}

void GameRunner::print_state() { this->state.print_state(); }

void GameRunner::make_move(int x, int y) {
  cout << "The move is " << x << " " << y << endl;
  try {
    state.move(x, y, this->turn);
  } catch (invalid_argument *e) {
    cout << e->what() << endl;
  } catch (out_of_range *e) {
    cout << e->what() << endl;
  }
  this->switch_turn();
}

pair<int, int> get_user_input() {
  string input;
  getline(cin, input);
  return make_pair(input[0] - '0', input[1] - '0');
}

pair<int, int> GameRunner::calculate_ai_move() {
  return Node(this->state, this->turn).get_next_best_move();
}

void GameRunner::make_ai_move() {
  if (this->has_game_ended()) {
    return;
  }

  pair<int, int> move = calculate_ai_move();
  this->make_move(move.first, move.second);
}

uint8_t *GameRunner::board_as_arr() { return this->state.board_as_arr(); }