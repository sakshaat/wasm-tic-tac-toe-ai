
#include "GameState.h"

class GameRunner {
 private:
  GameState state;
  players turn;
  array<actor, 2> actors;

 public:
  void make_move(int x, int y);
  void print_state();
  void switch_turn();
  players winner();
  bool game_ended();
  char get_current_turn();
  void run();
  pair<int, int> get_next_move();
  GameRunner(actor player1, actor player2);
};

GameRunner::GameRunner(actor player1, actor player2) {
  state = GameState();
  turn = PLAYER_1;
  actors = {player1, player2};
}

void GameRunner::switch_turn() {
  this->turn = this->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

players GameRunner::winner() { return this->state.winner(); }

bool GameRunner::game_ended() {
  return NO_ONE != this->state.winner() || this->state.board_full();
}

char GameRunner::get_current_turn() { return turn; }

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

pair<int, int> get_user_input() {
  string input;
  getline(cin, input);

  // converting to int
  int x = input[0] - '0';
  int y = input[1] - '0';

  return make_pair(x, y);
}

pair<int, int> GameRunner::get_next_move() {
  int i = this->turn == PLAYER_1 ? 0 : 1;
  cout << "TURN IS " << i << "ACTOR IS" << actors[i];
  switch (this->actors[i]) {
    case PLAYER:
      return get_user_input();
    case AI:
      // TO DO
      throw new invalid_argument("Not Implemented");
    default:
      throw new invalid_argument("Unknown Error");
  }
}

void GameRunner::run() {
  // keep looping until one of the players wins
  while (!this->game_ended()) {
    printf("%c's Turn:\n", this->get_current_turn() == PLAYER_1 ? 'X' : 'O');

    pair<int, int> move = get_next_move();
    printf("move is %d %d\n", move.first, move.second);

    try {
      this->make_move(move.first, move.second);
    } catch (invalid_argument *e) {
      cout << e->what() << endl;
    } catch (out_of_range *e) {
      cout << e->what() << endl;
    }

    // just to see for now
    this->print_state();
  }
}

int main() {
  GameRunner runner = GameRunner(AI, PLAYER);
  // testing
  runner.make_move(0, 0);
  runner.make_move(2, 0);
  runner.make_move(1, 1);
  runner.make_move(1, 2);
  runner.print_state();

  // run 2 player game
  runner.run();

  switch (runner.winner()) {
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
