CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -g -Wall -Werror -Wextra -I.
WEBASSMFLAGS=--bind -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1  -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++11

all: main

main: GameAPI.cpp GameRunner.cpp GameState.cpp GameTree.cpp
	$(CC) $(CFLAGS) -o main.o GameAPI.cpp GameRunner.cpp GameState.cpp GameTree.cpp

clean:
	rm *.out *.o &> /dev/null

run: main
	./main.o

wasm:
	emcc GameAPI.cpp GameRunner.cpp GameTree.cpp GameState.cpp -o main.js $(WEBASSMFLAGS)