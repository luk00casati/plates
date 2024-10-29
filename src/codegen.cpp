#include "codegen.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

#include "define.hpp"
#define COMMENT '#'

std::array<std::regex, REGEX_LIST_SIZE> regex_patterns = {
    std::regex(R"(\s*DEBUGON\s*)"),   // Pattern 0: DEBUGON
    std::regex(R"(\s*DEBUGOFF\s*)"),  // Pattern 1: DEBUGOFF
    std::regex(
        R"(\s*REPEAT\s+((SIZE|TOP|\d+)\s+(\+|\-|\*|\\|\%)\s+(SIZE|TOP|\d+)|(SIZE|TOP|\d+))\s+DO\s*)"),  // Pattern 2: REPEAT
    std::regex(R"(\s*BREAK\s*)"),  // Pattern 3: BREAK
    std::regex(R"(\s*END\s*)"),    // Pattern 4: END
    std::regex(
        R"(\s*IF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+))\s+DO\s*)"),  // Pattern 5: IF
    std::regex(
        R"(\s*ELIF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+))\s+DO\s*)"),  // Pattern 6: ELIF
    std::regex(R"(\s*ELSE\s+DO\s*)"),           // Pattern 7: ELSE
    std::regex(R"(\s*PUSH\s+(\d+)\s*)"),        // Pattern 8: PUSH
    std::regex(R"(\s*ROT\s*)"),                 // Pattern 9: ROT
    std::regex(R"(\s*PUT\s*)"),                 // Pattern 10: PUT
    std::regex(R"(\s*PUTC\s*)"),                // Pattern 11: PUTC
    std::regex(R"(\s*PUTNL\s*)"),               // Pattern 12: PUTNL
    std::regex(R"(\s*COPY\s*)"),                // Pattern 13: COPY
    std::regex(R"(\s*SWAP\s*)"),                // Pattern 14: SWAP
    std::regex(R"(\s*SUM\s*)"),                 // Pattern 15: SUM
    std::regex(R"(\s*SUB\s*)"),                 // Pattern 16: SUB
    std::regex(R"(\s*MUL\s*)"),                 // Pattern 17: MUL
    std::regex(R"(\s*DIV\s*)"),                 // Pattern 18: DIV
    std::regex(R"(\s*REM\s*)"),                 // Pattern 19: REM
    std::regex(R"(\s*DROP\s*)"),                // Pattern 20: DROP
    std::regex(R"(\s*)"),                       // Pattern 21: EMPTYLINE
    std::regex(R"(\s*POP\s*)"),                 // Pattern 22: POP
    std::regex(R"(\s*LOOP\s+DO\s*)"),           // Pattern 23: LOOP
    std::regex(R"(\s*PUSHC\s+([A-Za-z])\s*)"),  // Pattern 24: PUSHC
};

std::pair<bool, int> regex_in_list(const std::string str) {
    std::pair<bool, int> ret{false, 0};
    for (int i = 0; i < REGEX_LIST_SIZE; i++) {
        std::regex reg = regex_patterns[i];
        if (std::regex_match(str, reg)) {
            return ret = {true, i};
        }
    }
    return ret;
}

std::string removecomment(const std::string &in) {
    std::size_t pos = in.find(COMMENT);
    if (pos != std::string::npos) {
        return in.substr(0, pos);
    }
    return in;
}

std::string removespace(std::string str) {
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    return str;
}

int handle_end_type(std::stack<int> &end_type, std::vector<int> &codesection) {
    if (end_type.empty()) {
        return 1;
    } else {
        switch (end_type.top()) {
            case END_REPEAT:
                codesection.push_back(OP_ENDREPEAT);
                end_type.pop();
                break;

            case END_LOOP:
                codesection.push_back(OP_ENDLOOP);
                end_type.pop();
                break;

            case END_IF:
                codesection.push_back(OP_ENDIF);
                end_type.pop();
                break;

            case END_ELIF:
                codesection.push_back(OP_ELIF);
                end_type.pop();
                break;

            case END_ELSE:
                codesection.push_back(OP_ELSE);
                end_type.pop();
                break;

            default:
                std::cout << "invalid end type" << std::endl;
                return 1;
        }
    }
    return 0;
}

int genir(const std::string inputfilename, std::vector<int> &codesection,
          std::vector<std::string> &datasection) {
    std::ifstream inputfile(inputfilename);

    if (!inputfile.is_open()) {
        std::cerr << "Could not open the file: " << inputfilename << std::endl;
        return 1;
    }

    std::stack<int> end_type;
    std::string line;
    std::smatch Match;
    std::string M;
    unsigned long linenumber = 1;
    while (std::getline(inputfile, line)) {
        line = removecomment(line);
        std::pair<bool, int> res = regex_in_list(line);
        if (res.first) {
            switch (res.second) {
                case REGEX_PUSH:
                    std::regex_search(line, Match, regex_patterns[REGEX_PUSH]);
                    codesection.push_back(OP_PUSH);
                    datasection.push_back(Match.str(1));
                    break;

                case REGEX_PUSHC:
                    std::regex_search(line, Match, regex_patterns[REGEX_PUSHC]);
                    codesection.push_back(OP_PUSHC);
                    datasection.push_back(Match.str(1));
                    break;

                case REGEX_REPEAT:
                    std::regex_search(line, Match,
                                      regex_patterns[REGEX_REPEAT]);
                    M = removespace(Match.str(1));
                    codesection.push_back(OP_REPEAT);
                    datasection.push_back(M);
                    end_type.push(END_REPEAT);
                    break;

                case REGEX_IF:
                    std::regex_search(line, Match, regex_patterns[REGEX_IF]);
                    M = removespace(Match.str(1));
                    codesection.push_back(OP_IF);
                    datasection.push_back(M);
                    end_type.push(END_IF);
                    break;

                case REGEX_ELIF:
                    std::regex_search(line, Match, regex_patterns[REGEX_ELIF]);
                    M = removespace(Match.str(1));
                    codesection.push_back(OP_ELIF);
                    datasection.push_back(M);
                    end_type.push(END_ELIF);
                    break;

                case REGEX_ELSE:
                    codesection.push_back(OP_ELSE);
                    end_type.push(END_ELSE);
                    break;

                case REGEX_LOOP:
                    codesection.push_back(OP_LOOP);
                    end_type.push(END_LOOP);
                    break;

                case REGEX_END:
                    if (handle_end_type(end_type, codesection) == 0) {
                        break;
                    } else {
                        std::cout << "ERROR END miss match" << std::endl;
                        inputfile.close();
                        return 1;
                    }

                case REGEX_COPY:
                    codesection.push_back(OP_COPY);
                    break;

                case REGEX_ROT:
                    codesection.push_back(OP_ROT);
                    break;

                case REGEX_SUM:
                    codesection.push_back(OP_SUM);
                    break;

                case REGEX_PUT:
                    codesection.push_back(OP_PUT);
                    break;

                case REGEX_PUTC:
                    codesection.push_back(OP_PUTC);
                    break;

                case REGEX_PUTNL:
                    codesection.push_back(OP_PUTNL);
                    break;

                case REGEX_SWAP:
                    codesection.push_back(OP_SWAP);
                    break;

                case REGEX_SUB:
                    codesection.push_back(OP_SUB);
                    break;

                case REGEX_EMPTYLINE:
                    // NULL
                    break;

                case REGEX_DEBUGON:
                    codesection.push_back(OP_DEBUGON);
                    break;

                case REGEX_DEBUGOFF:
                    codesection.push_back(OP_DEBUGOFF);
                    break;

                case REGEX_BREAK:
                    codesection.push_back(OP_BREAK);
                    break;

                default:
                    std::cout << "invalid regex code on line " << linenumber
                              << " REGEX_CODE: " << res.second << std::endl;
                    break;
            }
        } else {
            std::cout << "match not found on line " << linenumber << ": "
                      << std::endl;
            std::cout << line << std::endl;
            inputfile.close();
            return 1;
        }
        linenumber++;
    }
    if (!end_type.empty()) {
        std::cout << "ERROR END miss match" << std::endl;
        inputfile.close();
        return 1;
    }

    codesection.push_back(OP_EXIT);
    inputfile.close();
    return 0;
}
