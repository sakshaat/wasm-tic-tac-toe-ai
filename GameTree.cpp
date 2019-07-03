#include "GameTree.h"

Node::Node(GameState state, players turn) {
  this->state = state;
  this->player = turn;
  this->is_max = turn == PLAYER_1;

  if (state.winner() == PLAYER_1) {
    this->score = 10;
  } else if (state.winner() == PLAYER_2) {
    this->score = -10;
  } else if (state.board_full()) {
    this->score = 0;
  } else {
    this->children = generate_children();

    if (is_max) {
      this->best_child =
          max_element(this->children.begin(), this->children.end()).base();
    } else {
      this->best_child =
          min_element(this->children.begin(), this->children.end()).base();
    }
    this->score = (this->best_child)->score;
  }
}

pair<int, int> Node::get_move() { return this->move; }

pair<int, int> Node::get_next_best_move() { return this->best_child->move; }

void Node::set_move(pair<int, int> move) { this->move = move; }

vector<Node> Node::get_children() { return this->children; }

Node Node::get_best_child() { return *this->best_child; }

void Node::print_state() { this->state.print_state(); }

int Node::get_score() { return this->score; };

vector<Node> Node::generate_children() {
  vector<pair<int, int>> moves = this->state.get_empty_tiles();
  if (moves.size() == 0) {
    return {};
  }

  vector<Node> result;
  for (size_t i = 0; i < moves.size(); i++) {
    // copy current state
    GameState child = this->state;

    child.move(moves[i].first, moves[i].second, player);
    Node node = Node(child, this->player == PLAYER_1 ? PLAYER_2 : PLAYER_1);

    // need this to be able to retrieve it later
    node.set_move(make_pair(moves[i].first, moves[i].second));
    result.push_back(node);
  }
  return result;
}
