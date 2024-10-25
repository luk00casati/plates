#include <iostream>
#include <string>
#include <vector>

#include "piatti.hpp"

bool isstrdigits(const std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int jumpbackto(std::vector<int> codesection, const int index, const int inst) {
    for (int i = index; i >= 0; i--) {
        if (codesection[i] == inst) {
            return i;
        }
    }
    return -1;
}

int jumpforwardto(std::vector<int> codesection, const int index,
                  const int inst) {
    for (int i = 0; i < index; i++) {
        if (codesection[i] == inst) {
            return i;
        }
    }
    return -1;
}

void vmrun(std::stack<long> &s, std::vector<int> &codesection,
           std::vector<std::string> &datasection,
           std::vector<std::pair<int, int>> &pairtable) {
    bool ifflag = false;
    bool elifflag = false;
    bool loopflag = false;
    bool debugprint = false;
    int offset = 0;
    long jump = 0;
    long repeatn = 0;
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

        // printstack(s);

        switch (inst) {
            case OP_PUSH:
                offset = get_offset(pairtable, i);
                data = datasection[offset];
                // std::cout << data << std::endl;
                spush(s, stol(data), debugprint);
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
                offset = get_offset(pairtable, i);
                data = datasection[offset];
                if (isstrdigits(data)) {
                    repeatn = stol(data);
                } else if (data.compare("SIZE") == 0) {
                    repeatn = ssize(s, debugprint);
                } else if (data.compare("TOP") == 0) {
                    repeatn = stop(s, debugprint);
                } else {
                    std::cout << "no impl: " << data << std::endl;
                }
                if (repeatn == 0) {
                    jump = jumpforwardto(codesection, i, OP_ENDREPEAT);
                    if (jump != -1) {
                        i = jump;
                    } else {
                        std::cout << "error on jump repeat" << std::endl;
                    }
                }
                break;

            case OP_ENDREPEAT:
                if (repeatn == 0) { /*null*/
                } else if (repeatn != 1) {
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

            default:
                std::cout << "unsupport or invalid instrution: " << inst
                          << std::endl;
                // exit(1);
                break;
        }

        i++;
    }
}