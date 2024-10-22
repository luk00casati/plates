#include <string>
#include <regex>
#include <iostream>
#include <array>
#include <stack>
#include <fstream>
#include <algorithm>
#include <vector>
#include "cpiatti.hpp"

std::vector<int> codesection;
std::vector<std::string> datasection;

std::array<std::regex, REGEX_LIST_SIZE> regex_patterns = {
    std::regex(R"(\s*DEBUGON\s*)"),      // Pattern 0: DEBUGON
    std::regex(R"(\s*DEBUGOFF\s*)"),     // Pattern 1: DEBUGOFF
    std::regex(
    R"(\s*REPEAT\s+((SIZE|TOP|\d+)\s+(\+|\-|\*|\\|\%)\s+(SIZE|TOP|\d+)|(SIZE|TOP|\d+))\s+DO\s*)"
    ), // Pattern 2: REPEAT
    std::regex(R"(\s*BREAK\s*)"),        // Pattern 3: BREAK
    std::regex(R"(\s*END\s*)"),          // Pattern 4: END
    std::regex(
    R"(\s*IF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+))\s+DO\s*)"
    ), // Pattern 5: IF
    std::regex(
    R"(\s*ELIF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+))\s+DO\s*)"
    ), // Pattern 6: ELIF
    std::regex(R"(\s*ELSE\s+DO\s*)"),    // Pattern 7: ELSE
    std::regex(R"(\s*PUSH\s+(\d+)\s*)"), // Pattern 8: PUSH
    std::regex(R"(\s*ROT\s*)"),          // Pattern 9: ROT
    std::regex(R"(\s*PUT\s*)"),          // Pattern 10: PUT
    std::regex(R"(\s*PUTC\s*)"),         // Pattern 11: PUTC
    std::regex(R"(\s*PUTNL\s*)"),        // Pattern 12: PUTNL
    std::regex(R"(\s*COPY\s*)"),         // Pattern 13: COPY
    std::regex(R"(\s*SWAP\s*)"),         // Pattern 14: SWAP
    std::regex(R"(\s*SUM\s*)"),          // Pattern 15: SUM
    std::regex(R"(\s*SUB\s*)"),          // Pattern 16: SUB
    std::regex(R"(\s*MUL\s*)"),          // Pattern 17: MUL
    std::regex(R"(\s*DIV\s*)"),          // Pattern 18: DIV
    std::regex(R"(\s*REM\s*)"),          // Pattern 19: REM
    std::regex(R"(\s*DROP\s*)"),         // Pattern 20: DROP
    std::regex(R"(\s*)"),                // Pattern 21: EMPTYLINE
    std::regex(R"(\s*POP\s*)"),          // Pattern 22: POP
    std::regex(R"(\s*LOOP\s+DO\s*)"),    // Pattern 23: LOOP
};

std::pair<bool, int> regex_in_list(const std::string str){
    std::pair<bool, int> ret {false, 0};
    for (int i = 0; i  < REGEX_LIST_SIZE; i++){
            std::regex reg = regex_patterns[i];
            if (std::regex_match(str, reg)){
                return ret = {true, i};
            }
        }
    return ret;
}

std::string removecomment(const std::string &in){
    std::size_t pos = in.find(COMMENT);
    if (pos != std::string::npos) {
        return in.substr(0, pos);
    }
    return in;
}

std::string removespace(std::string str){
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    return str;
}

/*
void closeanddeletefile(std::ofstream &wfile, const std::string str){
    if (wfile.is_open()){
        wfile.close();
        remove(str.c_str());
    }
    else{
        std::cout << "file already closed" << std::endl;
    }
}
*/

void genir(const std::string inputfilename){
    std::ifstream inputfile(inputfilename);    
    //std::ofstream  outputfile(outputfilename);

    if (!inputfile.is_open()) {
        std::cerr << "Could not open the file: " << inputfilename << std::endl;
        exit(1);
    }

    /*
    if (!outputfile.is_open()) {
        std::cerr << "Could not open the file: " << outputfilename << std::endl;
        exit(1);
    }
    */

    std::string line;
    std::smatch Match;
    std::string M;
    std::stack<int> end_type;
    unsigned long linenumber = 1;
    while (std::getline(inputfile, line)) {
        line = removecomment(line);
        std::pair<bool, int> res = regex_in_list(line);
        if (res.first){
            //std::cout << "match found: " << res.second << std::endl;
            switch (res.second)
            {
            case REGEX_PUSH:
                std::regex_search(line, Match, regex_patterns[REGEX_PUSH]);
                //outputfile << OP_PUSH << "," << Match.str(1) << std::endl;
                codesection.push_back(OP_PUSH);
                datasection.push_back(Match.str(1));
                break;
            
            case REGEX_REPEAT:
                std::regex_search(line, Match, regex_patterns[REGEX_REPEAT]);
                M = removespace(Match.str(1));
                //outputfile << OP_REPEAT << "," << M << std::endl;
                codesection.push_back(OP_REPEAT);
                datasection.push_back(M);
                end_type.push(END_REPEAT);
                break;

            case REGEX_IF:
                std::regex_search(line, Match, regex_patterns[REGEX_IF]);
                M = removespace(Match.str(1));
                //outputfile << OP_IF << "," << M << std::endl;
                codesection.push_back(OP_IF);
                datasection.push_back(M);
                end_type.push(END_IF);
                break;

            case REGEX_ELIF:
                std::regex_search(line, Match, regex_patterns[REGEX_ELIF]);
                M = removespace(Match.str(1));
                //outputfile << OP_ELIF << "," << M << std::endl;
                codesection.push_back(OP_ELIF);
                datasection.push_back(M);
                end_type.push(END_ELIF);
                break;

            case REGEX_ELSE:
                //outputfile << OP_ELSE << std::endl;
                codesection.push_back(OP_ELSE);
                end_type.push(END_ELSE);
                break;

            case REGEX_LOOP:
                //outputfile << OP_LOOP << std::endl;
                codesection.push_back(OP_LOOP);
                end_type.push(END_LOOP);
                break;

            case REGEX_COPY:
                //outputfile << OP_COPY << std::endl;
                codesection.push_back(OP_COPY);
                break;

            case REGEX_ROT:
                //outputfile << OP_ROT << std::endl;
                codesection.push_back(OP_ROT);
                break;
            
            case REGEX_SUM:
                //outputfile << OP_SUM << std::endl;
                codesection.push_back(OP_SUM);
                break;

            case REGEX_END:
                if (end_type.empty()){
                    std::cout << "ERROR END miss match" << std::endl;
                    //closeanddeletefile(outputfile, outputfilename);
                    inputfile.close();
                    exit(1);
                }
                else{
                switch (end_type.top())
                {
                case END_REPEAT:
                    //outputfile << OP_ENDREPEAT << std::endl;
                    codesection.push_back(OP_ENDREPEAT);
                    break;
                
                case END_LOOP:
                    //outputfile << OP_ENDLOOP << std::endl;
                    codesection.push_back(OP_ENDLOOP);
                    break;

                case END_IF:
                    //outputfile << OP_ENDIF << std::endl;
                    codesection.push_back(OP_ENDIF);
                    break;

                case END_ELIF:
                    //outputfile << OP_ENDELIF << std::endl;
                    codesection.push_back(OP_ELIF);
                    break;

                case END_ELSE:
                    //outputfile << OP_ENDELSE << std::endl;
                    codesection.push_back(OP_ELSE);
                    break;

                default:
                    std::cout << "invalid end type" << std::endl;
                    break;
                }
                end_type.pop();
                }

            case REGEX_PUT:
                //outputfile << OP_PUT << std::endl;
                codesection.push_back(OP_PUT);
                break;

            case REGEX_PUTC:
                //outputfile << OP_PUTC << std::endl;
                codesection.push_back(OP_PUTC);
                break;

            case REGEX_PUTNL:
                //outputfile << OP_PUTNL << std::endl;
                codesection.push_back(OP_PUTNL);
                break;

            case REGEX_SWAP:
                //outputfile << OP_SWAP << std::endl;
                codesection.push_back(OP_SWAP);
                break;

            case REGEX_SUB:
                //outputfile << OP_SUB << std::endl;
                codesection.push_back(OP_SUB);
                break;

            case REGEX_EMPTYLINE:
                //NULL
                break;
            
            default:
                std::cout << "invalid regex code on line " << linenumber <<
                " REGEX_CODE: " << res.second << std::endl;
                break;
            }
        }
        else{
            std::cout << "match not found on line " << linenumber << ": " << std::endl;
            std::cout << line << std::endl;
            //closeanddeletefile(outputfile, outputfilename);
            inputfile.close();
            exit(1);
        }
        linenumber++;
    }
    if (!end_type.empty()){
        std::cout << "ERROR END miss match" << std::endl;
        //closeanddeletefile(outputfile, outputfilename);
        inputfile.close();
        exit(1);
    }

    //outputfile << OP_EXIT;
    codesection.push_back(OP_EXIT);
    inputfile.close();
    //outputfile.close();
    std::cout << "ir generated" << std::endl;
}
