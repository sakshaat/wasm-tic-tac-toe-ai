#include "GameState.h"

GameState::GameState() {
  array<array<players, 3>, 3> empty_board;
  for (int i = 0; i < 3; i++) {
    empty_board[i].fill(NO_ONE);
  }
  state = empty_board;
  empty_spots = 0;
}

void GameState::move(int x, int y, players t) {
  this->state[x][y] = t;
  empty_spots++;
}

bool GameState::board_full() { return this->empty_spots == 9; }

players GameState::winner() {
  // horizontal
  for (int i = 0; i < 3; i++) {
    array<players, 3> curr = state[i];
    bool result = all_of(curr.begin(), curr.end(), [curr](players x) {
      return x != NO_ONE && x == curr[0];
    });
    if (result) {
      return curr[0];
    }
  }

  // vertical
  for (int i = 0; i < 3; i++) {
    bool result = state[0][i] != NO_ONE && state[0][i] == state[1][i] &&
                  state[0][i] == state[2][i];
    if (result) {
      return state[0][i];
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