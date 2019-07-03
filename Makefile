CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -g -Wall -Werror -Wextra -I.
WEBASSMFLAGS=-O3 -s WASM=1 -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++11

all: main

main: GameRunner.cpp GameState.cpp GameTree.cpp
	$(CC) $(CFLAGS) -o main.o GameRunner.cpp GameState.cpp GameTree.cpp

clean:
	rm *.out *.o &> /dev/null

run: main
	./main.o

webassm:
	emcc GameRunner.cpp GameTree.cpp GameState.cpp -o main.js $(WEBASSMFLAGS)