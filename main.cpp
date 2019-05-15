
#include "GameState.h"

class GameRunner {
 private:
  GameState state;
  players turn;

 public:
  void make_move(int x, int y);
  void print_state();
  void switch_turn();
  players is_winner();
  bool game_ended();
  char get_turn();
  GameRunner();
};

GameRunner::GameRunner() {
  state = GameState();
  turn = PLAYER_1;
}

void GameRunner::switch_turn() {
  if (turn == PLAYER_1) {
    turn = PLAYER_2;
  } else {
    turn = PLAYER_1;
  }
}

players GameRunner::is_winner() { return this->state.winner(); }

bool GameRunner::game_ended() {
  return turn == this->state.winner() || this->state.board_full();
}

char GameRunner::get_turn() { return turn == PLAYER_1 ? 'X' : 'O'; }

void GameRunner::print_state() { this->state.print_state(); }

void GameRunner::make_move(int x, int y) {
  if (!this->state.empty_tile(x, y)) {
    throw "Can't make a move on a non-empty tile";
  }

  state.move(x, y, this->turn);
  this->switch_turn();
}

int main() {
  GameRunner runner = GameRunner();
  runner.make_move(0, 0);
  runner.make_move(2, 0);
  runner.make_move(1, 1);
  runner.make_move(1, 2);
  runner.print_state();
  cout << runner.game_ended() << '\n';

  string input;

  // for debugging use only
  while (!runner.game_ended()) {
    cout << 'X' << " Wins!\n";
    printf("%c's Turn:\n", runner.get_turn());
    getline(cin, input);

    // converting to int
    int x = input[0] - '0';
    int y = input[1] - '0';

    runner.make_move(x, y);
    runner.print_state();
  }

  string fmt = "%c Wins!";

  switch (runner.is_winner()) {
    case PLAYER_1:
      cout << 'X' << " Wins!\n";
      break;
    case PLAYER_2:
      cout << 'O' << " Wins!\n";
      break;
    default:
      cout << "TIE GAME\n";
  }
}
