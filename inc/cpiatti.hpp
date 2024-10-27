#pragma once
#include <stack>

void printred(const char *str);

void printstack(std::stack<long> stack);

void spush(std::stack<long> &s, const long val, bool debugprint);

void spushc(std::stack<long> &s, const long val, bool debugprint);

void spop(std::stack<long> &s, bool debugprint);

void srot(std::stack<long> &s, bool debugprint);

void sput(std::stack<long> &s, bool debugprint);

void sputc(std::stack<long> &s, bool debugprint);

void sdiv(std::stack<long> &s, bool debugprint);

void scopy(std::stack<long> &s, bool debugprint);

void sswap(std::stack<long> &s, bool debugprint);

void ssub(std::stack<long> &s, bool debugprint);

void ssum(std::stack<long> &s, bool debugprint);

void smul(std::stack<long> &s, bool debugprint);

void srem(std::stack<long> &s, bool debugprint);

long stop(std::stack<long> &s, bool debugprint);

long ssize(std::stack<long> &s, bool debugprint);

void sdrop(std::stack<long> &s, bool debugprint);
