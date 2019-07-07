let symbol = {
  0: "",
  1: "X",
  2: "O"
};

let cellClickHandler = e => {
  Module.make_player_move(parseInt(e.target.getAttribute("data-value")));
  updateBoard();
  Module.make_ai_move();
  updateBoard();
};

let makeUnclickable = elem => {
  elem.classList.remove("empty-cell");
  elem.removeEventListener("click", cellClickHandler);
};

let gameEnded = () => {
  // make everything unclickable
  document.querySelectorAll(".empty-cell").forEach(makeUnclickable);

  // change winner header
  let winner = Module.get_winner();
  let title;
  if (winner === 0) {
    title = "Tie Game!";
  } else if (winner == 1) {
    title == "X Wins!";
  } else {
    title = "O Wins!";
  }
  document.querySelector("#winner-header").innerHTML = title;
};

let updateBoard = () => {
  let board = Module.get_gameboard();
  for (let i = 0; i < 9; i++) {
    let elem = document.querySelector(`#cell-${i}`);
    elem.innerHTML = symbol[board[i]];
    if (board[i] !== Module.player.NO_ONE.value) {
      makeUnclickable(elem);
    }
  }

  if (Module.has_game_ended()) {
    gameEnded();
  }
};

let startNewGame = () => {
  document.querySelector("#winner-header").innerHTML = "";
  Module.start_new_game();

  // reset
  document.querySelectorAll(".cell").forEach(elem => {
    elem.classList.add("empty-cell");
    elem.addEventListener("click", cellClickHandler);
  });

  updateBoard();
};

Module.onRuntimeInitialized = () => {
  // new game btn listener
  document
    .querySelector("#new-game-btn")
    .addEventListener("click", startNewGame);

  // update the board
  startNewGame();
};
