CC=g++
CFLAGS=-std=c++20

.PHONY = build clean

build: ./build/conexidad ./build/nestemate ./build/nestemate-no-stl ./build/ateleport ./build/ninjago

./build/conexidad: ./examples/conexidad.cpp
	$(CC) $(CFLAGS) -o ./build/conexidad ./examples/conexidad.cpp

./build/nestemate: ./examples/nestemate.cpp
	$(CC) $(CFLAGS) -o ./build/nestemate ./examples/nestemate.cpp

./build/nestemate-no-stl: ./examples/nestemate-no-stl.cpp
	$(CC) $(CFLAGS) -o ./build/nestemate-no-stl ./examples/nestemate-no-stl.cpp

./build/ateleport: ./examples/ateleport.cpp
	$(CC) $(CFLAGS) -o ./build/ateleport ./examples/ateleport.cpp

./build/ninjago: ./examples/ninjago.cpp
	$(CC) $(CFLAGS) -o ./build/ninjago ./examples/ninjago.cpp

clean:
	rm ./build/*


