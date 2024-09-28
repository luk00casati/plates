CC = clang
CFLAGS = -Wall -Wextra -O2 -std=c11 -pedantic
TRANSPILER = cpiattict
OBJ = cpiatti.o
SRC = cpiatti.c
HH = cpiatti.h
LIB = libcpiatti.so

all:
	@echo command:
	@echo make object
	@echo make library
	#@echo make transpiler
	@echo make install
	@echo make remove

object: $(SRC)
	@$(CC) -fPIC -c $(SRC) $(CFLAGS)

library: object
	@$(CC) -shared -o $(LIB) $(OBJ)

install: library $(HH)
	@cp $(LIB) /usr/local/lib
	@cp $(HH) /usr/local/include/
	#@cp $(TRANSPILER) /usr/bin/

remove:
	@rm /usr/local/lib/$(LIB)
	@rm /usr/local/include/$(HH)
	#@rm /usr/bin/$(TRANSPILER)