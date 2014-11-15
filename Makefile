FLAGS=-std=c++11 -g -lrt
IPATH=-Isrc

.PHONY: test

all: test

test:
	mkdir -p bin
	g++ $(FLAGS) $(IPATH) test/child.cpp -o bin/child
	g++ $(FLAGS) $(IPATH) test/test.cpp -o bin/test
