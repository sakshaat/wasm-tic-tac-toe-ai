
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
  return NO_ONE != this->state.winner() || this->state.board_full();
}

char GameRunner::get_turn() { return turn == PLAYER_1 ? 'X' : 'O'; }

void GameRunner::print_state() { this->state.print_state(); }

void GameRunner::make_move(int x, int y) {
  if (x > 2 || y > 2) {
    throw new out_of_range("x and y have to be between 0 - 2");
  }

  if (!this->state.empty_tile(x, y)) {
    throw new invalid_argument(
        "Cannot make a move where a move has already been made.");
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

  string input;

  // for debugging use only
  while (!runner.game_ended()) {
    printf("%c's Turn:\n", runner.get_turn());
    getline(cin, input);

    // converting to int
    int x = input[0] - '0';
    int y = input[1] - '0';

    try {
      runner.make_move(x, y);
    } catch (invalid_argument *e) {
      cout << e->what() << endl;
    } catch (out_of_range *e) {
      cout << e->what() << endl;
    }

    runner.print_state();
  }

  switch (runner.is_winner()) {
    case PLAYER_1:
      cout << 'X' << " Wins!" << endl;
      break;
    case PLAYER_2:
      cout << 'O' << " Wins!" << endl;
      break;
    case NO_ONE:
      cout << "TIE GAME" << endl;
  }
}
