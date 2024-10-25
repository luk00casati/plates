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
    for (int i = index; i > 0; i--) {
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
    // bool repeatflag = false;
    bool debugprint = false;
    int offset = 0;
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
                // std::cout << "hey" << std::endl;
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
                } else {
                    std::cout << "not digit: " << data << std::endl;
                }
                break;

            case OP_ENDREPEAT:
                if (repeatn != 0) {
                    i = jumpbackto(codesection, i, OP_REPEAT);
                    repeatn--;
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