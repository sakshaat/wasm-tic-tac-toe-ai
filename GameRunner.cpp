#include <emscripten/emscripten.h>
#include "GameTree.h"

class GameRunner {
 private:
  GameState state;
  players turn;
  array<actor, 2> actors;
  Node head;
  pair<int, int> calculate_ai_move();
  void switch_turn();

 public:
  bool has_game_ended();
  char get_current_turn();
  void make_move(int x, int y);
  void print_state();
  void run();
  players winner();
  GameRunner(actor player1, actor player2);
  GameRunner(){};
  void make_next_move();
  void make_player_move(int x, int y);
  void make_ai_move();
  void make_next_move(int x, int y);
  bool is_player_move();
};

GameRunner::GameRunner(actor player1, actor player2) {
  state = GameState();
  turn = PLAYER_1;

  // TODO Optimization
  // cout << "Building tree" << endl;
  // maintain the current state to reduce work
  // this->head = Node(state, turn);
  // cout << "Tree built." << endl;

  actors = {player1, player2};
}

bool GameRunner::is_player_move() { return actors[this->turn] == PLAYER; }

void GameRunner::switch_turn() {
  this->turn = this->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

players GameRunner::winner() { return this->state.winner(); }

bool GameRunner::has_game_ended() {
  return NO_ONE != this->state.winner() || this->state.board_full();
}

char GameRunner::get_current_turn() { return turn; }

void GameRunner::print_state() { this->state.print_state(); }

void GameRunner::make_move(int x, int y) {
  state.move(x, y, this->turn);
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

void GameRunner::run() {
  // keep looping until one of the players wins
  while (!this->game_ended()) {
    printf("%c's Turn:\n", this->get_current_turn() == PLAYER_1 ? 'X' : 'O');
    this->make_next_move();
    this->print_state();
  }
}

void GameRunner::make_ai_move() {
  if (this->game_ended()) {
    return;
  }

  pair<int, int> move = calculate_ai_move();
  this->make_next_move(move.first, move.second);
}

void GameRunner::make_player_move(int x, int y) {
  if (this->actors[this->turn] != PLAYER) {
    throw new invalid_argument("It is not the players move.");
  }
  this->make_next_move(x, y);
}

void GameRunner::make_next_move() {
  pair<int, int> move;
  if (this->actors[this->turn] == PLAYER) {
    move = get_user_input();
  } else {
    move = calculate_ai_move();
  }

  this->make_next_move(move.first, move.second);
}

void GameRunner::make_next_move(int x, int y) {
  printf("The move is %d %d\n", x, y);

  try {
    this->make_move(x, y);
  } catch (invalid_argument *e) {
    cout << e->what() << endl;
  } catch (out_of_range *e) {
    cout << e->what() << endl;
  }
}

static GameRunner current_game;

extern "C" {
void EMSCRIPTEN_KEEPALIVE make_ai_move() { current_game.make_ai_move(); }

void EMSCRIPTEN_KEEPALIVE make_player_move(int x, int y) {
  current_game.make_player_move(x, y);
}

void EMSCRIPTEN_KEEPALIVE print_state() { current_game.print_state(); }

bool EMSCRIPTEN_KEEPALIVE is_player_move() {
  return current_game.is_player_move();
}
bool EMSCRIPTEN_KEEPALIVE has_game_ended() {
  return current_game.has_game_ended();
}
}

int main() {
  current_game = GameRunner(PLAYER, AI);
  // testing
  // runner.make_move(2, 0);
  // runner.make_move(0, 0);
  // runner.make_move(1, 2);
  // runner.make_move(0, 1);
  // runner.make_move(1, 1);
  // runner.make_move(0, 2);
  // runner.make_move(2, 2);
  // runner.make_move(2, 1);
  current_game.print_state();

  // run 2 player game
  // current_game.run();

  // switch (current_game.winner()) {
  //   case PLAYER_1:
  //     cout << 'X' << " Wins!" << endl;
  //     break;
  //   case PLAYER_2:
  //     cout << 'O' << " Wins!" << endl;
  //     break;
  //   case NO_ONE:
  //     cout << "TIE GAME" << endl;
  // }
}
