#include <iostream>

#include "piatti.hpp"

void printred(const char *str) {
    puts(ANSI_COLOR_RED);
    puts(str);
    puts(ANSI_COLOR_RESET);
}

// no opcode
void printstack(std::stack<long> &stack) {
    std::stack<long> d = stack;
    while (!d.empty()) {
        std::cout << "print stack stack start" << std::endl;
        std::cout << d.top() << std::endl;
        d.pop();
    }
    std::cout << "print stack stack end" << std::endl;
}

void spush(std::stack<long> &s, const long val, bool debugprint) {
    s.push(val);
    if (debugprint) {
        printf("DEBUG push: \n%ld\n", val);
    }
}

void spop(std::stack<long> &s, bool debugprint) {
    if (s.empty()) {
        printred("ERROR pop on empty stack\n");
        exit(1);
    }
    if (!s.empty()) {
        if (debugprint) {
            printf("DEBUG pop: \n%ld\n", s.top());
        }
        s.pop();
    }
}

void srot(std::stack<long> &s, bool debugprint) {
    if (s.size() >= 2) {
        if (debugprint) {
            printf("DEBUG rot before:\n");
            printstack(s);
            printf("DEBUG rot after:\n");
        }
        std::stack<long> t;
        while (!s.empty()) {
            t.push(s.top());
            s.pop();
        }
        s = t;
    } else {
        // null
        if (debugprint) {
            printf("rotated: NULL\n");
        }
    }
}

void sput(std::stack<long> &s, bool debugprint) {
    if (s.empty()) {
        printred("ERROR put on empty stack\n");
        exit(1);
    }
    if (!s.empty()) {
        if (debugprint) {
            printf("DEBUG put: \n%ld\n", s.top());
        }
        if (!debugprint) {  // no out
            printf("%ld", s.top());
        }
        s.pop();
    }
}

void sputc(std::stack<long> &s, bool debugprint) {
    if (s.empty()) {
        printred("ERROR putc on empty stack\n");
        exit(1);
    }
    if (!s.empty()) {
        if (debugprint) {
            printf("DEBUG putc: \n%c\n", static_cast<char>(s.top()));
        }
        if (!debugprint) {  // no out
            printf("%c", static_cast<char>(s.top()));
        }
        s.pop();
    }
}

void scopy(std::stack<long> &s, bool debugprint) {
    if (s.empty()) {
        printred("\nerror copy on empty stack\n");
        exit(1);
    }
    if (!s.empty()) {
        if (debugprint) {
            printf("DEBUG copy: %ld\n", s.top());
        }
        s.push(s.top());
    }
}

void sswap(std::stack<long> &s, bool debugprint) {
    if (s.size() > 1) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        s.pop();
        s.push(t1);
        s.push(t2);
        if (debugprint) {
            printf("swapped: %ld %ld\n", t1, t2);
        }
    } else {
        // printred("ERROR swap on stack size <= 1\n");
        // exit(1);
        // null
        if (debugprint) {
            printf("swapped: NULL\n");
        }
    }
}

void ssub(std::stack<long> &s, bool debugprint) {
    if (s.size() < 2) {
        printred("ERROR sub on stack size < 2\n");
        exit(1);
    }
    if (s.size() >= 2) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        s.pop();
        long res = t1 - t2;
        if (debugprint) {
            printf("sub: %ld\n", res);
        }
        s.push(res);
    }
}

void ssum(std::stack<long> &s, bool debugprint) {
    if (s.size() < 2) {
        printred("ERROR sum on stack size < 2\n");
        exit(1);
    }
    if (s.size() >= 2) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        s.pop();
        long res = t1 + t2;
        if (debugprint) {
            printf("sum: %ld\n", res);
        }
        s.push(res);
    }
}

void smul(std::stack<long> &s, bool debugprint) {
    if (s.size() < 2) {
        printred("ERROR mol on stack size < 2\n");
        exit(1);
    }
    if (s.size() >= 2) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        s.pop();
        long res = t1 * t2;
        if (debugprint) {
            printf("mol: %ld\n", res);
        }
        s.push(res);
    }
}

void sdiv(std::stack<long> &s, bool debugprint) {
    if (s.size() < 2) {
        printred("ERROR div on stack size < 2\n");
        exit(1);
    }
    if (s.size() >= 2) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        if (t2 == 0) {
            printred("ERROR division by 0\n");
            exit(1);
        }
        s.pop();
        long res = t1 / t2;
        if (debugprint) {
            printf("div: %ld\n", res);
        }
        s.push(res);
    }
}

void srem(std::stack<long> &s, bool debugprint) {
    if (s.size() < 2) {
        printred("ERROR rem on stack size < 2\n");
        exit(1);
    }
    if (s.size() >= 2) {
        long t1 = s.top();
        s.pop();
        long t2 = s.top();
        if (t2 == 0) {
            printred("ERROR division by 0\n");
            exit(1);
        }
        s.pop();
        long res = t1 % t2;
        if (debugprint) {
            printf("rem: %ld\n", res);
        }
        s.push(res);
    }
}

long stop(std::stack<long> &s, bool debugprint) {
    if (s.empty()) {
        printred("ERROR top on empty stack\n");
        exit(1);
    }
    if (!s.empty()) {
        if (debugprint) {
            printf("DEBUG top: %ld\n", s.top());
        }
    }
    return s.top();
}

long ssize(std::stack<long> &s, bool debugprint) {
    if (debugprint) {
        printf("DEBUG size: %ld\n", static_cast<long>(s.size()));
    }
    return s.size();
}

void sdrop(std::stack<long> &s, bool debugprint) {
    if (debugprint) {
        printf("DEBUG drop: EMPTY\n");
    }
    while (!s.empty()) {
        s.pop();
    }
}
