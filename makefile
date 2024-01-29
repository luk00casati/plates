CC = cc
#CFLAGS = -Wall -Wextra
OBJ = cpiatti.o
SRC = cpiatti.c
HH = cpiatti.h
LIB = libcpiatti.so

all:
	@echo command:
	@echo make object
	@echo make library
	@echo make install
	@echo make remove

object: $(SRC)
	@$(CC) -fPIC -c $(SRC)

library: object
	@$(CC) -shared -o $(LIB) $(OBJ)

install: library $(HH)
	@cp $(LIB) /usr/lib
	@cp $(HH) /usr/include/

remove:
	@rm /usr/lib/$(LIB)
	@rm /usr/include/$(HH)