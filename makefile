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

build: lexer.o parser.o pb_buffer.o generic_instr.o basic_instr.o nonbasic_instr.o

dcpu: build $(SRC)$(MAIN).cpp
	$(CC) $(FLAG) -o $(APP) $(SRC)$(MAIN).cpp $(SRC)lexer.o $(SRC)parser.o $(SRC)pb_buffer.o $(SRC)generic_instr.o $(SRC)basic_instr.o $(SRC)nonbasic_instr.o

lexer.o: $(SRC)lexer.cpp $(SRC)lexer.hpp
	$(CC) $(FLAG) -c $(SRC)lexer.cpp -o $(SRC)lexer.o

parser.o: $(SRC)parser.cpp $(SRC)parser.hpp
	$(CC) $(FLAG) -c $(SRC)parser.cpp -o $(SRC)parser.o

pb_buffer.o: $(SRC)pb_buffer.cpp $(SRC)pb_buffer.hpp
	$(CC) $(FLAG) -c $(SRC)pb_buffer.cpp -o $(SRC)pb_buffer.o

generic_instr.o: $(SRC)generic_instr.cpp $(SRC)generic_instr.hpp
	$(CC) $(FLAG) -c $(SRC)generic_instr.cpp -o $(SRC)generic_instr.o

basic_instr.o: $(SRC)basic_instr.cpp $(SRC)basic_instr.hpp
	$(CC) $(FLAG) -c $(SRC)basic_instr.cpp -o $(SRC)basic_instr.o

nonbasic_instr.o: $(SRC)nonbasic_instr.cpp $(SRC)nonbasic_instr.hpp
	$(CC) $(FLAG) -c $(SRC)nonbasic_instr.cpp -o $(SRC)nonbasic_instr.o
