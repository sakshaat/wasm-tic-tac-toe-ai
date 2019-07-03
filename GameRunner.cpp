#include <emscripten/emscripten.h>
#include "GameTree.h"

class GameRunner {
 private:
  GameState state;
  players turn;
  array<actor, 2> actors;
  Node head;

 public:
  void make_move(int x, int y);
  void print_state();
  void switch_turn();
  bool game_ended();
  char get_current_turn();
  void run();
  pair<int, int> calculate_ai_move();
  pair<int, int> get_next_move();
  players winner();
  GameRunner(actor player1, actor player2);
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
  state.move(x, y, this->turn);
  this->switch_turn();
}

pair<int, int> get_user_input() {
  string input;
  getline(cin, input);
  return make_pair(input[0] - '0', input[1] - '0');
}

pair<int, int> GameRunner::calculate_ai_move() {
  // make current node
  // Node node = Node(this->state, this->turn);
  // node.print_state();

  // debug
  // vector<Node> children = node.get_children();
  // for (size_t i = 0; i < children.size(); i++) {
  //   pair<int, int> move = children[i].get_move();
  //   cout << "move is (" << move.first << ", " << move.second << ")" << endl;
  //   cout << "score is " << children[i].get_score() << endl;
  // }

  // get best child
  return Node(this->state, this->turn).get_best_child().get_move();

  // debug
  // cout << "selected pair is (" << next_move.first << ", " << next_move.second
  //      << ")" << endl;
}

pair<int, int> GameRunner::get_next_move() {
  int i = this->turn == PLAYER_1 ? 0 : 1;
  switch (this->actors[i]) {
    case PLAYER:
      return get_user_input();
    case AI:
      return calculate_ai_move();
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
  GameRunner runner = GameRunner(AI, AI);
  // testing
  // runner.make_move(2, 0);
  // runner.make_move(0, 0);
  // runner.make_move(1, 2);
  // runner.make_move(0, 1);
  // runner.make_move(1, 1);
  // runner.make_move(0, 2);
  // runner.make_move(2, 2);
  // runner.make_move(2, 1);
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
