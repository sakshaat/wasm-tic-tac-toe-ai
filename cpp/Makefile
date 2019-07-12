CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -g -Wall -Werror -Wextra -I.
WEBASSMFLAGS=--bind -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++11
CPP_PATH=./cpp/

all: main

main: game_runner.cpp game_state.cpp game_tree.cpp
	$(CC) $(CFLAGS) -o main.o game_runner.cpp game_state.cpp game_tree.cpp

clean:
	rm *.out *.o &> /dev/null

run: main
	./main.o

wasm:
	emcc game_api.cpp game_runner.cpp game_tree.cpp game_state.cpp -o ../public/main.js $(WEBASSMFLAGS)
