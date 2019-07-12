#include "game_state.h"

GameState::GameState() {
  array<array<player, 3>, 3> empty_board;
  for (int i = 0; i < 3; i++) {
    empty_board[i].fill(NO_ONE);
  }
  state = empty_board;
  empty_spots = 9;
}

GameState::GameState(const GameState& other) {
  this->state = other.state;
  this->empty_spots = other.empty_spots;
}

void GameState::move(int x, int y, player t) {
  if (x > 2 || y > 2) {
    throw new out_of_range("x and y have to be between 0 - 2");
  }

  if (!this->empty_tile(y, x)) {
    throw new invalid_argument(
        "Cannot make a move where a move has already been made.");
  }

  this->state[y][x] = t;
  empty_spots--;
}

bool GameState::board_full() { return this->empty_spots == 0; }

player GameState::winner() {
  // horizontal
  for (int i = 0; i < 3; i++) {
    array<player, 3> curr = state[i];
    bool result = all_of(curr.begin(), curr.end(), [curr](player x) {
      return x != NO_ONE && x == curr[0];
    });
    if (result) {
      return curr[0];
    }
  }

  // vertical
  for (int j = 0; j < 3; j++) {
    bool result = state[0][j] != NO_ONE && state[0][j] == state[1][j] &&
                  state[0][j] == state[2][j];
    if (result) {
      return state[0][j];
    }
  }

  // diagonal
  bool result = state[0][0] != NO_ONE && state[0][0] == state[1][1] &&
                state[1][1] == state[2][2];

  if (result) {
    return state[1][1];
  }

  result = state[2][0] != NO_ONE && state[2][0] == state[1][1] &&
           state[1][1] == state[0][2];

  if (result) {
    return state[1][1];
  }

  return NO_ONE;
}

bool GameState::empty_tile(int x, int y) { return this->state[x][y] == NO_ONE; }

void GameState::print_state() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      switch (state[j][i]) {
        case PLAYER_1:
          cout << " X ";
          break;
        case PLAYER_2:
          cout << " O ";
          break;
        case NO_ONE:
          cout << " - ";
          break;
      }
    }
    cout << '\n';
  }
}

void GameState::board_as_arr(uint8_t* board) {
  uint8_t idx = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[idx] = this->state[j][i];
      idx++;
    }
  }
};

vector<pair<int, int>> GameState::get_empty_tiles() {
  if (this->board_full()) {
    return vector<pair<int, int>>();
  }

  vector<pair<int, int>> result;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (this->state[j][i] == NO_ONE) {
        result.push_back(make_pair(i, j));
      }
    }
  }

  return result;
}