CC = clang
CC++ = clang++
CFLAGS = -Wall -Wextra -O2 -std=c++11 -pedantic 
TRANSPILER = plates
OBJ = cpiatti.o
SRC = cpiatti.cpp
HH = cpiatti.hpp
LIB = libcpiatti.so

all: transpiler library

help:
	@echo command:
	@echo make object
	@echo make library
	@echo make transpiler
	@echo make install
	@echo make cleaninstall
	@echo make remove

flex: transpiler.l
	@flex transpiler.l

object: $(SRC)
	@$(CC++) -fPIC -c $(SRC) $(CFLAGS)
	@$(CC) -c lex.yy.c 

library: object
	@$(CC++) -shared -o $(LIB) $(OBJ)

transpiler: $(SRC) flex
	@$(CC++) lex.yy.o $(SRC) -lfl $(CFLAGS) -D_XOPEN_SOURCE=700 -o $(TRANSPILER)

install: library transpiler $(HH) $(LIB)
	@cp $(LIB) /usr/lib
	@cp $(HH) /usr/include/
	@cp $(TRANSPILER) /usr/bin/

remove:
	@rm /usr/lib/$(LIB)
	@rm /usr/include/$(HH)
	@rm /usr/bin/$(TRANSPILER)

cleaninstall: remove install
