CC=clang++
CFLAGS=-stdlib=libc++ -std=c++11 -g -Wall -Werror -Wextra -I.

all: main

main: main.cpp GameState.cpp
	$(CC) $(CFLAGS) -o main.o main.cpp GameState.cpp

clean:
	rm *.out *.o &> /dev/null

run: main
	./main.o