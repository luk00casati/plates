#include <iostream>
#include "cpiatti.hpp"

void printred(const char *str)
{
  puts(ANSI_COLOR_RED);
  puts(str);
  puts(ANSI_COLOR_RESET);
}

void printstack(std::stack<long> stack)
{
  std::stack<long> d = stack;
  while (!d.empty())
  {
    std::cout << d.top() << std::endl;
    d.pop();
  }
}

void sdebugenable(void)
{
  debugprint = true;
}

void sdebugdisable(void)
{
  debugprint = false;
}


void spush(std::stack<long> s, const long val)
{
  if (s.empty())
  {
    s.push(val);
    if (debugprint)
    {
      printf("DEBUG push: \n%d\n", val);
    }
  }
}

long spop(std::stack<long> s)
{
  long ret = 0;
  if (s.empty())
  {
    printred("ERROR pop on empty stack\n");
    exit(1);
  }
  if (!s.empty())
  {
    ret = s.top();
    s.pop();
    if (debugprint)
    {
      printf("DEBUG pop: \n%d -> EMPTY\n", ret);
    }
    return ret;
  }
}

void srot(std::stack<long> s)
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

void sput(std::stack<long> s)
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
      printf("DEBUG put: \n%d -> EMPTY\n", s.top());
    }
    if (!debugprint)
    { // no out
      printf("%d", s.top());
    }
    s.pop();
  }
}

void sputc(std::stack<long> s)
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
      printf("DEBUG putc: \n%c -> EMPTY\n", s.top());
    }
    if (!debugprint)
    { // no out
      printf("%c", s.top());
    }
    s.pop();
  }
}

void scopy(std::stack<long> s)
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
      printf("DEBUG copy: %d\n", s.top());
    }
    s.push(s.top());
  }
}

void sswap(std::stack<long> s)
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

void ssub(std::stack<long> s)
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
      printf("sub: %d\n", res);
    }
    s.push(res);
  }
}

void ssum(std::stack<long> s)
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
      printf("sum: %d\n", res);
    }
    s.push(res);
  }
}

void smol(std::stack<long> s)
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
      printf("mol: %d\n", res);
    }
    s.push(res);
  }
}

void sdiv(std::stack<long> s)
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
      printf("div: %d\n", res);
    }
    s.push(res);
  }
}

void srem(std::stack<long> s)
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
      printf("rem: %d\n", res);
    }
    s.push(res);
  }
}

long speek(std::stack<long> s)
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
      printf("DEBUG peek: %d\n", s.top());
    }
  }
  return s.top();
}

long size(std::stack<long> s)
{
  if (debugprint)
  {
    printf("DEBUG size: %d\n", s.size());
  }
  return s.size();
}

void drop(std::stack<long> s)
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
