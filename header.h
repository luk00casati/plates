//#define DEBUG
//#define NOOUT

struct Sstack {
  int *ptr;
  int size;
  int store;
};

extern struct Sstack stack;

void init_stack();
void deint_stack();
void push(int arg);
void pop();
void spop();
void rot();
void put();
void aput();
void copy();
void swap();
void sub();
void sum();