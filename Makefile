CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -g -Wall -Werror -Wextra -I.

all: main

main: GameRunner.cpp GameState.cpp GameTree.cpp
	$(CC) $(CFLAGS) -o main.o GameRunner.cpp GameState.cpp GameTree.cpp

clean:
	rm *.out *.o &> /dev/null

run: main
	./main.o