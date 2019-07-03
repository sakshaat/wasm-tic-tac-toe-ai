#include "GameState.h"

using namespace std;

// a future optimization strategy could involve first constructing the entire
// tree and then using it to save game state rather than computing the tree each
// time

class Node {
 private:
  GameState state;
  players player;
  vector<Node> children;
  vector<Node> generate_children();
  Node* best_child;
  pair<int, int> move;
  int score;

 public:
  bool is_max;
  int get_score();
  Node(GameState state, players turn);
  Node(){};
  void print_state();
  Node get_best_child();
  pair<int, int> get_move();
  void set_move(pair<int, int> move);

  vector<Node> get_children();
  bool operator<(const Node& other) const { return this->score < other.score; }
};

class GameTree {
 private:
  Node root;
  void construct_tree();

 public:
  void next_move();
  GameTree(GameState state);
};
