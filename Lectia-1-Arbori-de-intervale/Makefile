CC=g++
CFLAGS=-std=c++20

.PHONY = build clean

build: ./build/recap ./build/example1 ./build/example2 ./build/lupusor

./build/recap: ./examples/recap.cpp
	$(CC) $(CFLAGS) -o ./build/recap ./examples/recap.cpp

./build/example1: ./examples/example1.cpp
	$(CC) $(CFLAGS) -o ./build/example1 ./examples/example1.cpp

./build/example2: ./examples/example2.cpp
	$(CC) $(CFLAGS) -o ./build/example2 ./examples/example2.cpp

./build/lupusor: ./problems/lupusor.cpp
	$(CC) $(CFLAGS) -o ./build/lupusor ./problems/lupusor.cpp

clean:
	rm ./build/*

