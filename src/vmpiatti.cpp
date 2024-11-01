#include "vmpiatti.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "codegen.hpp"
#include "cpiatti.hpp"
#include "define.hpp"

long ctol(const std::string str) {
    return static_cast<long>(str[0]);
}

std::pair<char, size_t> findsign(const std::string data,
                                 const std::string signs) {
    for (size_t i = 0; i < data.length(); i++) {
        if (signs.find(data[i]) != std::string::npos) {
            return {data[i], i};
        }
    }
    std::cout << "findsign panic" << std::endl;
    exit(1);
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
                        std::string data) {
    long arg1 = 0;
    long arg2 = 0;
    std::string arg1str;
    std::string arg2str;
    bool ret = false;
    size_t splitpoint = 0;
    char operation1;
    char operation2;
    int operationstrsize = 0;
    std::pair<char, size_t> opsignandops = findsign(data, "=!<>");
    operation1 = opsignandops.first;
    splitpoint = opsignandops.second;
    operation2 = data[splitpoint + 1];
    switch (operation1) {
        case '<':
            if (operation2 == '=') {
                operationstrsize = 2;
            } else {
                operationstrsize = 1;
            }
            break;

        case '>':
            if (operation2 == '=') {
                operationstrsize = 2;
            } else {
                operationstrsize = 1;
            }
            break;

        case '=':
            operationstrsize = 2;
            break;

        case '!':
            operationstrsize = 2;
            break;

        default:
            std::cout << "invalid operator" << std::endl;
            break;
    }
    arg1str = data.substr(0, splitpoint);
    arg2str = data.substr(splitpoint + operationstrsize, data.length());
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
    // std::cout << arg1 << std::endl;
    // std::cout << arg2 << std::endl;
    // std::cout << operation1 << std::endl;
    // std::cout << operation2 << std::endl;
    switch (operation1) {
        case '=':
            ret = (arg1 == arg2);
            break;

        case '!':
            ret = (arg1 != arg2);
            break;

        case '>':
            if (operationstrsize == 1) {
                ret = (arg1 > arg2);
            }
            if (operationstrsize == 2) {
                ret = (arg1 >= arg2);
            }
            break;

        case '<':
            if (operationstrsize == 1) {
                ret = (arg1 < arg2);
            }
            if (operationstrsize == 2) {
                ret = (arg1 <= arg2);
            }
            break;

        default:
            std::cout << "invalid operation" << std::endl;
            break;
    }
    return ret;
}

size_t jumpbackto(std::vector<int> &codesection, const size_t current_index,
                  const int current_inst, const int dest_inst) {
    long current_inst_counter = 0;
    for (long i = static_cast<long>(current_index); i >= 0; i--) {
#ifdef DEBUG
        std::cout << "code: " << codesection[i] << std::endl;
        std::cout << "couter: " << current_inst_counter << std::endl;
#endif
        if (codesection[i] == current_inst &&
            i != static_cast<long>(current_index)) {
            current_inst_counter++;
        }
        if (codesection[i] == dest_inst && current_inst_counter == 0) {
            //std::cout << "ret: " << i << std::endl;
            return i + current_index;

        } else if (codesection[i] == dest_inst && current_inst_counter != 0) {
            current_inst_counter--;
        }
    }
    std::cout << "panic jumpbackto" << std::endl;
    exit(1);
}

size_t jumpforwardto(std::vector<int> &codesection, const size_t current_index,
                     const int current_inst, const int dest_inst) {
    long current_inst_counter = 0;
    for (size_t i = current_index; i < codesection.size(); i++) {
#ifdef DEBUG
        std::cout << "code: " << codesection[i] << std::endl;
        std::cout << "couter: " << current_inst_counter << std::endl;
#endif
        if (codesection[i] == current_inst && i != current_index) {
            current_inst_counter++;
        }
        if (codesection[i] == dest_inst && current_inst_counter == 0) {
            return i;
        } else if (codesection[i] == dest_inst && current_inst_counter != 0) {
            current_inst_counter--;
        }
    }
    std::cout << "panic jumpforwardto" << std::endl;
    exit(1);
}

void vmrun(std::stack<long> &s, bool &debugprint, std::vector<int> &codesection,
           std::vector<std::string> &datasection) {
    bool ifflag = false;
    bool elifflag = false;
    bool loopflag = false;
    long repeatn = 0;
    long jump = 0;
    std::string data;

    size_t i = 0;
    bool run = true;
    while (run) {
        if (i >= codesection.size()) {
            std::cout << "reaching end codesetion" << std::endl;
            break;
        }
        int inst = codesection[i];

#ifdef DEBUG
        std::cout << "instruction " << inst << " i: " << i << std::endl;
#endif
        switch (inst) {
            case OP_PUSH:
                data = datasection[i];
                // std::cout << data << std::endl;
                spush(s, stol(data), debugprint);
                break;

            case OP_PUSHC:
                data = datasection[i];
                spushc(s, ctol(data), debugprint);

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

            case OP_DROP:
                sdrop(s, debugprint);
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

            case OP_ENDELSE:
                break;

            case OP_ENDELIF:
                break;

            case OP_ENDIF:
                break;

            case OP_IF:
                data = datasection[i];
                // std::cout << data << std::endl;
                ifflag = handleroperationif(s, debugprint, data);
                // std::cout << ifflag << std::endl;
                if (ifflag == false) {
                    i += jumpforwardto(codesection, i, OP_IF, OP_ENDIF);
                }
                break;

            case OP_ELIF:
                data = datasection[i];
                elifflag = handleroperationif(s, debugprint, data);
                if (ifflag == true || elifflag == false) {
                    i += jumpforwardto(codesection, i, OP_ELIF, OP_ENDELIF);
                }
                break;

            case OP_ELSE:
                if (ifflag == true || elifflag == true) {
                    i += jumpforwardto(codesection, i, OP_ELSE, OP_ENDELSE);
                }
                break;

            case OP_REPEAT:
                data = datasection[i];
                repeatn = handleroperationrepeat(s, debugprint, data);
                if (repeatn == 0) {
                    jump = jumpforwardto(codesection, i, OP_REPEAT, OP_ENDREPEAT);
                    i = jump + i;
                    //std::cout << "repeat: " << i << std::endl;
                }
                break;

            case OP_ENDREPEAT:
                if (repeatn < 0) {
                    std::cout << "error reapeat panic" << std::endl;
                } else if (repeatn == 1) { /*null*/
                } else if (repeatn > 1) {
                    //std::cout << "before endrepeat: " << i << std::endl;
                    jump = jumpbackto(codesection, i, OP_ENDREPEAT, OP_REPEAT);
                    i = jump - i;
                    //std::cout << "endrepeati: " << i << "endrepeatjump: " << jump << std::endl;
                    repeatn--;
                }
                break;

            case OP_LOOP:
                loopflag = true;
                break;

            case OP_BREAK:
                loopflag = false;
                i += jumpforwardto(codesection, i, OP_BREAK, OP_ENDLOOP);
                break;

            case OP_ENDLOOP:
                if (loopflag) {
                    i -= jumpbackto(codesection, i, OP_ENDLOOP, OP_LOOP);
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