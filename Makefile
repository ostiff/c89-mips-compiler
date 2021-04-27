LINK_TARGET = bin/c_compiler
CC = g++
CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter -Wno-unused-function
CPPFLAGS += -I inc/ast/ -I src/parser/ -I src/lexer/ -I inc/context/

SRCSAST = $(wildcard src/ast/*.cpp)
SRCSCONTEXT = $(wildcard src/context/*.cpp)
OBJSAST = $(SRCSAST:.cpp=.o)
OBJSCONTEXT = $(SRCSCONTEXT:.cpp=.o)

all: $(LINK_TARGET)

#linking and compiling
$(LINK_TARGET) : src/c_compiler.o $(OBJSAST) $(OBJSCONTEXT) src/lexer/c_lexer.yy.o src/parser/c_parser.tab.o
	mkdir -p bin
	$(CC) $(CPPFLAGS) -o $(LINK_TARGET) $^

#lexer
src/lexer/c_lexer.yy.cpp : src/lexer/c_lexer.flex src/parser/c_parser.tab.hpp
	flex -o $@ src/lexer/c_lexer.flex  

#parser
src/parser/c_parser.tab.cpp src/parser/c_parser.tab.hpp : src/parser/c_parser.y
	yacc -v -d $^ -o src/parser/c_parser.tab.cpp

#clean
.PHONY: clean
clean:
	find . -name "*.o" -type f -delete
	find . -name "*.tab.*" -type f -delete
	find . -name "*.output" -type f -delete
	find . -name "*.yy.*" -type f -delete
	find . -name c_compiler -type f -delete
	rm -f tmp/testMIPS/*
	rm -f tmp/testPy/*
	@echo "Clean done."