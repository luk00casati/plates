#include <string>
#include <regex>
#include <iostream>
#include <array>
#include <stack>
#include <fstream>
#include "cpiatti.hpp"

std::array<std::regex, REGEX_LIST_SIZE> regex_patterns = {
    std::regex(R"(\s*DEBUGON\s*\n)"),      // Pattern 0: DEBUGON
    std::regex(R"(\s*DEBUGOFF\s*\n)"),     // Pattern 1: DEBUGOFF
    std::regex(
    R"(\s*REPEAT\s+((SIZE|TOP|\d+)\s+(\+|\-|\*|\\|\%)\s+(SIZE|TOP|\d+)|(SIZE|TOP|\d+))\s+DO\s*\n)"
    ), // Pattern 2: REPEAT
    std::regex(R"(\s*BREAK\s*\n)"),        // Pattern 3: BREAK
    std::regex(R"(\s*END\s*\n)"),          // Pattern 4: END
    std::regex(
    R"(\s*IF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+)|\d+)\s+DO\s*\n)"
    ), // Pattern 5: IF
    std::regex(
    R"(\s*ELIF\s+((SIZE|TOP|\d+)\s+(\==|\!=|\<|\>|\<=|\>=)\s+(SIZE|TOP|\d+)|\d+)\s+DO\s*\n)"
    ), // Pattern 6: ELIF
    std::regex(R"(\s*ELSE\s+DO\s*\n)"),    // Pattern 7: ELSE
    std::regex(R"(\s*PUSH\s+(\d+)\s*\n)"), // Pattern 8: PUSH
    std::regex(R"(\s*ROT\s*\n)"),          // Pattern 9: ROT
    std::regex(R"(\s*PUT\s*\n)"),          // Pattern 10: PUT
    std::regex(R"(\s*PUTC\s*\n)"),         // Pattern 11: PUTC
    std::regex(R"(\s*PUTNL\s*\n)"),        // Pattern 12: PUTNL
    std::regex(R"(\s*COPY\s*\n)"),         // Pattern 13: COPY
    std::regex(R"(\s*SWAP\s*\n)"),         // Pattern 14: SWAP
    std::regex(R"(\s*SUM\s*\n)"),          // Pattern 15: SUM
    std::regex(R"(\s*SUB\s*\n)"),          // Pattern 16: SUB
    std::regex(R"(\s*MUL\s*\n)"),          // Pattern 17: MUL
    std::regex(R"(\s*DIV\s*\n)"),          // Pattern 18: DIV
    std::regex(R"(\s*REM\s*\n)"),          // Pattern 19: REM
    std::regex(R"(\s*DROP\s*\n)"),         // Pattern 20: DROP
    std::regex(R"(\s*\n)"),                // Pattern 21: EMPTYLINE
    std::regex(R"(\s*POP\s*\n)"),          // Pattern 22: POP
    std::regex(R"(\s*LOOP\s+DO\s*\n)"),    // Pattern 23: LOOP
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

void closeanddeletefile(std::ofstream &wfile, const std::string str){
    if (wfile.is_open()){
        wfile.close();
        remove(str.c_str());
    }
    else{
        std::cout << "file already closed" << std::endl;
    }
}

void genir(const std::string inputfilename, const std::string outputfilename){
    std::ifstream inputfile(inputfilename);    
    std::ofstream  outputfile(outputfilename);

    if (!inputfile.is_open()) {
        std::cerr << "Could not open the file: " << inputfilename << std::endl;
        exit(1);
    }

    if (!outputfile.is_open()) {
        std::cerr << "Could not open the file: " << outputfilename << std::endl;
        exit(1);
    }

    std::string line;
    std::smatch Match;
    std::stack<int> end_type;
    unsigned long linenumber = 0;
    //outputfile << "MAINSTART;" << std::endl;
    while (std::getline(inputfile, line)) {
        std::string linenl = line+'\n';
        std::pair<bool, int> res = regex_in_list(linenl);
        if (res.first){
            std::cout << "match found: " << res.second << std::endl;
            switch (res.second)
            {
            case REGEX_PUSH:
                if(std::regex_search(linenl, Match, regex_patterns[REGEX_PUSH])){
                    outputfile << "PUSH," << Match.str(1) << ';' << std::endl;
                    break;
                }
                else{
                    std::cout << "invalid PUSH arg" << std::endl;
                }
            
            case REGEX_REPEAT:
                if(std::regex_search(linenl, Match, regex_patterns[REGEX_REPEAT])){
                    outputfile << "REPEAT," << Match.str(1) << ';' << std::endl;
                    end_type.push(END_REPEAT);
                    break;
                }
                else{
                    std::cout << "invalid REPEAT arg" << std::endl;
                }

            case REGEX_COPY:
                outputfile << "COPY;" << std::endl;
                break;

            case REGEX_ROT:
                outputfile << "ROT;" << std::endl;
                break;
            
            case REGEX_SUM:
                outputfile << "SUM;" << std::endl;
                break;

            case REGEX_END:
                if (end_type.empty()){
                    std::cout << "ERROR END miss match" << std::endl;
                }
                else{
                switch (end_type.top())
                {
                case END_REPEAT:
                    outputfile << "ENDREPEAT;" << std::endl;
                    break;
                
                case END_LOOP:
                    outputfile << "ENDLOOP;" << std::endl;
                    break;

                case END_IF:
                    outputfile << "ENDIF;" << std::endl;
                    break;

                case END_ELIF:
                    outputfile << "ENDELIF;" << std::endl;
                    break;

                case END_ELSE:
                    outputfile << "ENDELSE;" << std::endl;
                    break;

                default:
                    std::cout << "invalid end type" << std::endl;
                    break;
                }
                }

            case REGEX_PUT:
                outputfile << "PUT;" << std::endl;
                break;

            case REGEX_PUTC:
                outputfile << "PUTC;" << std::endl;
                break;

            case REGEX_PUTNL:
                outputfile << "PUTNL;" << std::endl;
                break;

            case REGEX_SWAP:
                outputfile << "SWAP;" << std::endl;
                break;

            case REGEX_SUB:
                outputfile << "SUB;" << std::endl;
                break;

            case REGEX_EMPTYLINE:
                //NULL
                break;
            
            default:
                std::cout << "invalid regex code " << linenumber <<
                ": " << res.second << std::endl;
                break;
            }
        }
        else{
            std::cout << "match not found on line " << linenumber << ": " << std::endl;
            std::cout << line << std::endl;
            closeanddeletefile(outputfile, outputfilename);
            inputfile.close();
            exit(1);
        }
        linenumber++;
    }
    outputfile << "EXIT;";
    inputfile.close();
    outputfile.close();
}
