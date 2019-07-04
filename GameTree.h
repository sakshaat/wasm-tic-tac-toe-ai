#include "GameState.h"

using namespace std;

// a future optimization strategy could involve first constructing the entire
// tree and then using it to save game state rather than computing the tree each
// time

class Node {
 private:
  GameState state;
  player turn;
  vector<Node> children;
  vector<Node> generate_children();
  pair<int, int> move;
  int score;
  bool is_max;
  pair<int, int> next_best_move;

 public:
  Node(GameState state, player turn);
  Node(){};
  void print_state();
  pair<int, int> get_next_best_move();
  void set_move(pair<int, int> move);
  pair<int, int> get_move();
  bool operator<(const Node& other) const { return this->score < other.score; }
};
