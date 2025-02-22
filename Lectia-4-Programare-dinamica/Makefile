CC=g++
CFLAGS=-std=c++20

.PHONY = build clean

build: ./build/recyclebin ./build/antivirus ./build/superhedgy

./build/recyclebin: ./examples/recyclebin.cpp
	$(CC) $(CFLAGS) -o ./build/recyclebin ./examples/recyclebin.cpp

./build/antivirus: ./examples/antivirus.cpp
	$(CC) $(CFLAGS) -o ./build/antivirus ./examples/antivirus.cpp

./build/superhedgy: ./examples/superhedgy.cpp
	$(CC) $(CFLAGS) -o ./build/superhedgy ./examples/superhedgy.cpp

clean:
	rm ./build/*

