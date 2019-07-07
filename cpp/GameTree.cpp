#include "GameTree.h"

Node::Node(GameState state, player turn) {
  this->state = state;
  this->turn = turn;
  this->is_max = turn == PLAYER_1;

  if (state.winner() == PLAYER_1) {
    this->score = 1;
  } else if (state.winner() == PLAYER_2) {
    this->score = -1;
  } else if (state.board_full()) {
    this->score = 0;
  } else {
    this->children = generate_children();

    Node *best_child;
    if (is_max) {
      best_child =
          max_element(this->children.begin(), this->children.end()).base();
    } else {
      best_child =
          min_element(this->children.begin(), this->children.end()).base();
    }
    this->score = best_child->score;
    this->next_best_move = best_child->move;
  }
}

pair<int, int> Node::get_move() { return this->move; }

pair<int, int> Node::get_next_best_move() { return this->next_best_move; }

void Node::set_move(pair<int, int> move) { this->move = move; }

void Node::print_state() { this->state.print_state(); }

vector<Node> Node::generate_children() {
  vector<pair<int, int>> moves = this->state.get_empty_tiles();
  if (moves.size() == 0) {
    return {};
  }

  vector<Node> result;
  for (size_t i = 0; i < moves.size(); i++) {
    // copy current state
    GameState child = this->state;

    child.move(moves[i].first, moves[i].second, this->turn);
    Node node = Node(child, this->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1);

    // need this to be able to retrieve it later
    node.set_move(make_pair(moves[i].first, moves[i].second));
    result.push_back(node);
  }
  return result;
}
