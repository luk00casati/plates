#include <iostream>
#include "cpiatti.hpp"

bool debugprint = false;

void printred(const char *str)
{
  puts(ANSI_COLOR_RED);
  puts(str);
  puts(ANSI_COLOR_RESET);
}

void printstack(std::stack<long> &stack)
{
  std::stack<long> d = stack;
  while (!d.empty())
  {
    std::cout << d.top() << std::endl;
    d.pop();
  }
}

void sdebugbool(bool b)
{
  if (b){
    debugprint = true;
  }
  if (!b){
    debugprint = false;
  }
}

void spush(std::stack<long> &s, const long val)
{
  if (s.empty())
  {
    s.push(val);
    if (debugprint)
    {
      printf("DEBUG push: \n%ld\n", val);
    }
  }
}

void spop(std::stack<long> &s)
{
  if (s.empty())
  {
    printred("ERROR pop on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    if (debugprint)
    {
      printf("DEBUG pop: \n%ld\n", s.top());
    }
    s.pop();
  }
}

void srot(std::stack<long> &s)
{
  if (s.size() >= 2)
  {
    if (debugprint)
    {
      printf("DEBUG rot before:\n");
      printstack(s);
      printf("DEBUG rot after:\n");
    }
    std::stack<long> t;
    while (!s.empty())
    {
      t.push(s.top());
      s.pop();
    }
    s = t;
  }
  else
  {
    // null
  }
}

void sput(std::stack<long> &s)
{
  if (s.empty())
  {
    printred("ERROR put on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    if (debugprint)
    {
      printf("DEBUG put: \n%ld -> EMPTY\n", s.top());
    }
    if (!debugprint)
    { // no out
      printf("%ld", s.top());
    }
    s.pop();
  }
}

void sputc(std::stack<long> &s)
{
  if (s.empty())
  {
    printred("ERROR putc on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    if (debugprint)
    {
      printf("DEBUG putc: \n%c -> EMPTY\n", static_cast<char>(s.top()));
    }
    if (!debugprint)
    { // no out
      printf("%c", static_cast<char>(s.top()));
    }
    s.pop();
  }
}

void scopy(std::stack<long> &s)
{
  if (s.empty())
  {
    printred("\nerror copy on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    if (debugprint)
    {
      printf("DEBUG copy: %ld\n", s.top());
    }
    s.push(s.top());
  }
}

void sswap(std::stack<long> &s)
{
  if (s.size() > 1)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    s.pop();
    s.push(t1);
    s.push(t2);
  }
  else
  {
    printred("ERROR swap on stack size <= 1\n");
    exit(1);
  }
}

void ssub(std::stack<long> &s)
{
  if (s.size() < 2)
  {
    printred("ERROR sub on stack size < 2\n");
    exit(1);
  }
  if (s.size() >= 2)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    s.pop();
    long res = t1 - t2;
    if (debugprint)
    {
      printf("sub: %ld\n", res);
    }
    s.push(res);
  }
}

void ssum(std::stack<long> &s)
{
  if (s.size() < 2)
  {
    printred("ERROR sum on stack size < 2\n");
    exit(1);
  }
  if (s.size() >= 2)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    s.pop();
    long res = t1 + t2;
    if (debugprint)
    {
      printf("sum: %ld\n", res);
    }
    s.push(res);
  }
}

void smul(std::stack<long> &s)
{
  if (s.size() < 2)
  {
    printred("ERROR mol on stack size < 2\n");
    exit(1);
  }
  if (s.size() >= 2)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    s.pop();
    long res = t1 * t2;
    if (debugprint)
    {
      printf("mol: %ld\n", res);
    }
    s.push(res);
  }
}

void sdiv(std::stack<long> &s)
{
  if (s.size() < 2)
  {
    printred("ERROR div on stack size < 2\n");
    exit(1);
  }
  if (s.size() >= 2)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    if (t2 == 0)
    {
      printred("ERROR division by 0\n");
      exit(1);
    }
    s.pop();
    long res = t1 / t2;
    if (debugprint)
    {
      printf("div: %ld\n", res);
    }
    s.push(res);
  }
}

void srem(std::stack<long> &s)
{
  if (s.size() < 2)
  {
    printred("ERROR rem on stack size < 2\n");
    exit(1);
  }
  if (s.size() >= 2)
  {
    long t1 = s.top();
    s.pop();
    long t2 = s.top();
    if (t2 == 0)
    {
      printred("ERROR division by 0\n");
      exit(1);
    }
    s.pop();
    long res = t1 % t2;
    if (debugprint)
    {
      printf("rem: %ld\n", res);
    }
    s.push(res);
  }
}

long stop(std::stack<long> &s)
{
  if (s.empty())
  {
    printred("ERROR peek on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    if (debugprint)
    {
      printf("DEBUG peek: %ld\n", s.top());
    }
  }
  return s.top();
}

long ssize(std::stack<long> &s)
{
  if (debugprint)
  {
    printf("DEBUG size: %ld\n", s.size());
  }
  return s.size();
}

void sdrop(std::stack<long> &s)
{
  if (debugprint)
  {
    printf("DEBUG drop:\nEMPTY\n");
  }
  while (!s.empty())
  {
    s.pop();
  }
}
