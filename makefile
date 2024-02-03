CC = cc
CFLAGS = -Wall -Wextra -O2
TRANSPILER = cpiattict.c
BIN = cpiattict
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

transpiler: $(TRANSPILER)
	@$(CC) -o $(BIN) $(TRANSPILER) $(CFLAGS)

install: library $(HH) transpiler
	@cp $(LIB) /usr/lib
	@cp $(HH) /usr/include/
	@cp $(BIN) /usr/bin/

remove:
	@rm /usr/lib/$(LIB)
	@rm /usr/include/$(HH)
	@rm /usr/bin/$(BIN)