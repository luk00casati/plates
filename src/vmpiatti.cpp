#include "vmpiatti.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "codegen.hpp"
#include "cpiatti.hpp"
#include "define.hpp"

long ctol(std::string str) {
    long value = static_cast<long>(str[0]);
    return value;
}

std::pair<char, size_t> findsign(const std::string data,
                                 const std::string signs) {
    for (size_t i = 0; i < data.length(); i++) {
        if (signs.find(data[i]) != std::string::npos) {
            return {data[i], i};
        }
    }
    return {'A', 0};
}

bool isstrdigits(const std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

long handleroperationrepeat(std::stack<long> &s, bool debugprint,
                            const std::string data) {
    long arg1 = 0;
    std::string arg1str;
    long arg2 = 0;
    std::string arg2str;
    long ret = 0;
    char operation;
    size_t splitpoint;
    if (isstrdigits(data)) {
        ret = stol(data);
        return ret;
    }
    if (data.compare("SIZE") == 0) {
        ret = ssize(s, debugprint);
        return ret;
    }
    if (data.compare("TOP") == 0) {
        ret = stop(s, debugprint);
        return ret;
    }
    std::pair<char, size_t> opsignandops = findsign(data, "+-*/%");
    operation = opsignandops.first;
    splitpoint = opsignandops.second;
    arg1str = data.substr(0, splitpoint);
    arg2str = data.substr(splitpoint + 1, data.length());
    if (isstrdigits(arg1str)) {
        arg1 = stol(arg1str);
    }
    if (isstrdigits(arg2str)) {
        arg2 = stol(arg2str);
    }
    if (arg2str.compare("SIZE") == 0) {
        arg2 = ssize(s, debugprint);
    }
    if (arg1str.compare("SIZE") == 0) {
        arg1 = ssize(s, debugprint);
    }
    if (arg2str.compare("TOP") == 0) {
        arg2 = stop(s, debugprint);
    }
    if (arg1str.compare("TOP") == 0) {
        arg1 = stop(s, debugprint);
    }
    // std::cout << "arg1: " << arg1 << std::endl;
    // std::cout << "arg2: " << arg2 << std::endl;
    // std::cout << "operation: " << operation << std::endl;
    switch (operation) {
        case '+':
            ret = arg1 + arg2;
            break;

        case '-':
            ret = arg1 - arg2;
            break;

        case '*':
            ret = arg1 * arg2;
            break;

        case '/':
            if (arg2 == 0) {
                printred("repeat division by zero");
                exit(1);
            }
            ret = arg1 / arg2;
            break;

        case '%':
            if (arg2 == 0) {
                printred("repeat division by zero");
                exit(1);
            }
            ret = arg1 % arg2;
            break;

        default:
            std::cout << "invalid operation" << std::endl;
            break;
    }
    return ret;
}

bool handleroperationif(std::stack<long> &s, bool debugprint,
                        const std::string data) {
}

long jumpbackto(std::vector<int> codesection, const long index,
                const int inst) {
    for (long i = index; i >= 0; i--) {
        if (codesection[i] == inst) {
            return i;
        }
    }
    return -1;
}

long jumpforwardto(std::vector<int> codesection, const long index,
                   const int inst) {
    for (long i = 0; i < index; i++) {
        if (codesection[i] == inst) {
            return i;
        }
    }
    return -1;
}

void vmrun(std::stack<long> &s, bool &debugprint, std::vector<int> &codesection,
           std::vector<std::string> &datasection) {
    bool ifflag = false;
    bool elifflag = false;
    bool loopflag = false;
    long jump = 0;
    long repeatn = 0;
    long datai = 0;
    std::string data;

    size_t i = 0;
    bool run = true;
    while (run) {
        if (i >= codesection.size()) {
            std::cout << "reaching end codesetion" << std::endl;
            break;
        }
        int inst = codesection[i];

        // std::cout << "instruction " << inst << " i: " << i << std::endl;

        switch (inst) {
            case OP_PUSH:
                data = datasection[datai];
                // std::cout << data << std::endl;
                spush(s, stol(data), debugprint);
                datai++;
                break;

            case OP_PUSHC:
                data = datasection[datai];
                spushc(s, ctol(data), debugprint);
                datai++;
                break;

            case OP_SWAP:
                sswap(s, debugprint);
                break;

            case OP_ROT:
                srot(s, debugprint);
                break;

            case OP_SUB:
                ssub(s, debugprint);
                break;

            case OP_SUM:
                ssum(s, debugprint);
                break;

            case OP_DEBUGON:
                debugprint = true;
                break;

            case OP_DEBUGOFF:
                debugprint = false;
                break;

            case OP_MUL:
                smul(s, debugprint);
                break;

            case OP_DIV:
                sdiv(s, debugprint);
                break;

            case OP_REM:
                srem(s, debugprint);
                break;

            case OP_PUTC:
                sputc(s, debugprint);
                break;

            case OP_PUT:
                sput(s, debugprint);
                break;

            case OP_PUTNL:
                printf("\n");
                break;

            case OP_EXIT:
                run = false;
                break;

            case OP_COPY:
                scopy(s, debugprint);
                break;

            case OP_REPEAT:
                data = datasection[datai];
                repeatn = handleroperationrepeat(s, debugprint, data);
                // std::cout << repeatn << std::endl;
                if (repeatn == 0) {
                    jump = jumpforwardto(codesection, i, OP_ENDREPEAT);
                    if (jump != -1) {
                        i = jump;
                    } else {
                        std::cout << "error on jump repeat" << std::endl;
                    }
                }
                datai++;
                break;

            case OP_ENDREPEAT:
                if (repeatn < 0) {
                    std::cout << "error reapeat panic" << std::endl;
                } else if (repeatn == 1) { /*null*/
                } else if (repeatn > 1) {
                    jump = jumpbackto(codesection, i, OP_REPEAT);
                    if (jump != -1) {
                        i = jump;
                        // std::cout << "jump: " << i << std::endl;
                        repeatn--;
                    } else {
                        std::cout << "error on jump endrepeat" << std::endl;
                    }
                }
                break;

            case OP_LOOP:
                loopflag = true;
                break;

            case OP_BREAK:
                loopflag = false;
                jump = jumpforwardto(codesection, i, OP_ENDLOOP);
                if (jump != -1) {
                    i = jump;
                } else {
                    std::cout << "error on jump break" << std::endl;
                }
                break;

            case OP_ENDLOOP:
                if (loopflag) {
                    jump = jumpbackto(codesection, i, OP_LOOP);
                    if (jump != -1) {
                        i = jump;
                    } else {
                        std::cout << "error on jump endloop" << std::endl;
                    }
                }
                break;

            default:
                std::cout << "unsupport or invalid instrution: " << inst
                          << std::endl;
                // exit(1);
                break;
        }

        i++;
    }
}