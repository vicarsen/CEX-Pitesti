CC=g++
CFLAGS=-std=c++20

.PHONY = build clean

build: ./build/sqrt-decomp ./build/holes ./build/dquery ./build/postpone-1

./build/sqrt-decomp: ./examples/sqrt-decomp.cpp
	$(CC) $(CFLAGS) -o ./build/sqrt-decomp ./examples/sqrt-decomp.cpp

./build/holes: ./examples/holes.cpp
	$(CC) $(CFLAGS) -o ./build/holes ./examples/holes.cpp

./build/dquery: ./examples/dquery.cpp
	$(CC) $(CFLAGS) -o ./build/dquery ./examples/dquery.cpp

./build/postpone-1: ./examples/postpone-1.cpp
	$(CC) $(CFLAGS) -o ./build/postpone-1 ./examples/postpone-1.cpp

clean:
	rm ./build/*

