CC=g++
CFLAGS=-std=c++20

.PHONY = build clean

build: ./build/automaton_trivial ./build/strmatch ./build/strmatch_c ./build/automaton ./build/strmatch_aut

./build/strmatch: ./examples/strmatch.cpp
	$(CC) $(CFLAGS) -o ./build/strmatch ./examples/strmatch.cpp

./build/strmatch_c: ./examples/strmatch_c.cpp
	$(CC) $(CFLAGS) -o ./build/strmatch_c ./examples/strmatch_c.cpp

./build/automaton_trivial: ./examples/automaton_trivial.cpp
	$(CC) $(CFLAGS) -o ./build/automaton_trivial ./examples/automaton_trivial.cpp

./build/automaton: ./examples/automaton.cpp
	$(CC) $(CFLAGS) -o ./build/automaton ./examples/automaton.cpp

./build/strmatch_aut: ./examples/strmatch_aut.cpp
	$(CC) $(CFLAGS) -o ./build/strmatch_aut ./examples/strmatch_aut.cpp

clean:
	rm ./build/*

