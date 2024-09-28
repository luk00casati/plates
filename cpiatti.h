#ifndef CPIATTI_H
#define CPIATTI_H

void debugenable(struct Stack* s);
void init_stack(struct Stack* s);
void deinit_stack(struct Stack* s);
void push(struct Stack* s, const unsigned int val);
void pop(struct Stack* s);
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
void drop(struct Stack* s);

#endif
