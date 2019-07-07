CPP_PATH=./cpp/

all: main

main: GameRunner.cpp GameState.cpp GameTree.cpp
	$(MAKE) -C $(CPP_PATH) main

clean:
	$(MAKE) -C $(CPP_PATH) clean

run: main
	$(MAKE) -C $(CPP_PATH) run

wasm:
	$(MAKE) -C $(CPP_PATH) wasm