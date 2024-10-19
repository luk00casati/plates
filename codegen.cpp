#include <string>
#include <regex>
#include <iostream>
#include <array>

#define REGEX_LIST_SIZE 21

std::array<std::regex, REGEX_LIST_SIZE> regex_patterns = {
    std::regex(R"(\s*DEBUGON\s*\n)"),      // Pattern 0: DEBUGON
    std::regex(R"(\s*DEBUGOFF\s*\n)"),     // Pattern 1: DEBUGOFF
    std::regex(R"(\s*REPEAT\s*(.*)\s*DO\s*\n)"), // Pattern 2: REPEAT
    std::regex(R"(\s*BREAK\s*\n)"),        // Pattern 3: BREAK
    std::regex(R"(\s*END\s*\n)"),          // Pattern 4: END
    std::regex(R"(\s*IF\s*(.*)\s*DO\s*\n)"), // Pattern 5: IF
    std::regex(R"(\s*ELIF\s*(.*)\s*DO\s*\n)"), // Pattern 6: ELIF
    std::regex(R"(\s*ELSE\s+DO\s*\n)"),    // Pattern 7: ELSE
    std::regex(R"(\s*PUSH\s*(\d+)\s*\n)"), // Pattern 8: PUSH
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

int main(){
    std::string str = "PUSH 10\n";
    std::pair<bool, int> res = regex_in_list(str);
        if (res.first){
            std::cout << "match found: " << res.second << std::endl;
        }
        else{
            std::cout << "match not found" << std::endl;
        }
}
