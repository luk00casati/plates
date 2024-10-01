#ifndef CPIATTI_H
#define CPIATTI_H

#define STRING(s) #s
#define SIGERRS STRING(SIGINT recived); 

struct Stack {
  unsigned int *ptr;
  unsigned int size;
  short int debugprint;
};

void transpile(const char* path ,const char* flag);
void debugenable(struct Stack* s);
void init_stack(struct Stack* s);
void deinit_stack(struct Stack* s);
void deinitquiterr(struct Stack* s);
void push(struct Stack* s, const unsigned int val);
unsigned int pop(struct Stack* s);
void rot(struct Stack* s);
void put(struct Stack* s);
void sputc(struct Stack* s); //naming collision
void sdiv(struct Stack* s); //naming collision
void copy(struct Stack* s);
void swap(struct Stack* s);
void sub(struct Stack* s);
void sum(struct Stack* s);
void mul(struct Stack* s);
void rem(struct Stack* s);
unsigned int peek(struct Stack* s);
unsigned int size(struct Stack* s);
void drop(struct Stack* s);

#endif
