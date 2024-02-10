#ifndef CPIATTI_H
#define CPIATTI_H

struct Sstack {
  int *ptr;
  int size;
  int store;
};

extern struct Sstack stack;

void init_stack();
void deinit_stack();
void push(const int arg);
void sgetc();
void sgets(const char *str);
void sgeti();
void pop();
void stpop();
void rot();
void put();
void aput();
void copy();
void swap();
void sub();
void sum();
void mul();
void sdiv();
void rem();
void drop();
void stpeek();
#endif