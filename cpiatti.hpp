#pragma once

#include<stack>

#define STRING(s) #s
#define SIGERRS STRING(Error: signal received)
#define NL "\n"

std::stack<long> s;
bool debugprint = false;

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
extern "C" {
void transpile(const char* path);
}
void sdebugenable(void);
void sdebugdisable(void);
void spush(std::stack<long> s, long val);
long spop(std::stack<long> s);
void srot(std::stack<long> s);
void sput(std::stack<long> s);
void sputc(std::stack<long> s); 
void sdiv(std::stack<long> s); 
void scopy(std::stack<long> s);
void sswap(std::stack<long> s);
void ssub(std::stack<long> s);
void ssum(std::stack<long> s);
void smul(std::stack<long> s);
void srem(std::stack<long> s);
long speek(std::stack<long> s);
long ssize(std::stack<long> s);
void sdrop(std::stack<long> s);
