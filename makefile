# dcpu-asm Makefile
# Copyright (C) 2012 David Jolly

CC=g++
APP=asm
MAIN=main
SRC=src/
FLAG=-std=c++0x -O3 -funroll-all-loops

all: build dcpu

clean:
	rm -f $(SRC)*.o $(APP)

build: lexer.o parser.o pb_buffer.o token.o

dcpu: build $(SRC)$(MAIN).cpp
	$(CC) $(FLAG) -o $(APP) $(SRC)$(MAIN).cpp $(SRC)lexer.o $(SRC)parser.o $(SRC)pb_buffer.o $(SRC)token.o

lexer.o: $(SRC)lexer.cpp $(SRC)lexer.hpp
	$(CC) $(FLAG) -c $(SRC)lexer.cpp -o $(SRC)lexer.o

parser.o: $(SRC)parser.cpp $(SRC)parser.hpp
	$(CC) $(FLAG) -c $(SRC)parser.cpp -o $(SRC)parser.o

pb_buffer.o: $(SRC)pb_buffer.cpp $(SRC)pb_buffer.hpp
	$(CC) $(FLAG) -c $(SRC)pb_buffer.cpp -o $(SRC)pb_buffer.o

token.o: $(SRC)token.cpp $(SRC)token.hpp
	$(CC) $(FLAG) -c $(SRC)token.cpp -o $(SRC)token.o
