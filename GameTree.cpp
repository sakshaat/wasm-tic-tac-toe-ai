#include "GameTree.h"
#include <unordered_map>

Node::Node(GameState state, players turn) {
  this->state = state;
  this->player = turn;
  this->is_max = turn == PLAYER_1;

  if (state.winner() == PLAYER_1) {
    this->score = 1;
  } else if (state.winner() == PLAYER_2) {
    this->score = -1;
  } else if (state.board_full()) {
    this->score = 0;
  } else {
    // generate its children
    generate_children();
    vector<Node> children_lst = get_children();
    if (is_max) {
      this->best_child =
          &(*max_element(children_lst.begin(), children_lst.end()));

    } else {
      this->best_child =
          &(*min_element(children_lst.begin(), children_lst.end()));
    }
    this->score = (this->best_child)->score;
  }
}

pair<int, int> Node::get_move() { return this->move; }

void Node::set_move(pair<int, int> move) { this->move = move; }

vector<Node> Node::get_children() { return this->children; }

Node Node::get_best_child() { return *this->best_child; }

void Node::print_state() { this->state.print_state(); }

int Node::get_score() { return this->score; };

void Node::generate_children() {
  vector<pair<int, int>> moves = this->state.get_empty_tiles();
  if (moves.size() == 0) {
    return;
  }

  Node* best_so_far = NULL;

  for (size_t i = 0; i < moves.size(); i++) {
    // copy current state
    GameState child = this->state;

    child.move(moves[i].first, moves[i].second, player);
    Node node = Node(child, this->player == PLAYER_1 ? PLAYER_2 : PLAYER_1);

    // need this to be able to retrieve it later
    node.set_move(make_pair(moves[i].first, moves[i].second));
    this->children[moves[i]] = node;

    // also want to keep track of the best node here
    if (best_so_far == NULL) {
      *best_so_far = node;
    } else {
      if (this->is_max) {
        if (node.get_score() > (*best_so_far).get_score()) {
          *best_so_far = node;
        }
      } else {
        if (node.get_score() < (*best_so_far).get_score()) {
          *best_so_far = node;
        }
      }
    }
  }
  this->best_child = best_so_far;
}
