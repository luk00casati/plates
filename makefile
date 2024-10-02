CC = clang
CFLAGS = -Wall -Wextra -O2 -std=c11 -pedantic 
TRANSPILER = piatti
OBJ = cpiatti.o
SRC = cpiatti.c
HH = cpiatti.h
LIB = libcpiatti.so

all:
	@echo command:
	@echo make object
	@echo make library
	@echo make transpiler
	@echo make install
	@echo make remove

object: $(SRC)
	@$(CC) -fPIC -c $(SRC) $(CFLAGS)

library: object
	@$(CC) -shared -o $(LIB) $(OBJ)

transpiler: transpiler.l piatti.c
	@flex transpiler.l
	@$(CC) lex.yy.c piatti.c -lfl $(CFLAGS) -D_XOPEN_SOURCE=700 -o $(TRANSPILER)

install: library transpiler $(HH) $(TRANSPILER) $(LIB)
	@cp $(LIB) /usr/lib
	@cp $(HH) /usr/include/
	@cp $(TRANSPILER) /usr/bin/

remove:
	@rm /usr/lib/$(LIB)
	@rm /usr/include/$(HH)
	@rm /usr/bin/$(TRANSPILER)