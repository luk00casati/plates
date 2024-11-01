#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "codegen.hpp"
#include "define.hpp"
#include "vmpiatti.hpp"

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "error needed a file path" << std::endl;
        return 1;
    }
    if (argc > 2) {
        std::cout << "error too many arguments" << std::endl;
        return 1;
    }
    if (argc == 2) {
        std::string inputfilename = argv[1];
        int ret = 0;
        std::vector<int> codesection;
        std::vector<std::string> datasection;
        std::stack<long> s;
        bool debugprint = false;
        ret = genir(inputfilename, codesection, datasection);
        if (ret == 0) {
#ifdef DEBUG
            std::cout << "ir generated" << std::endl;

            std::cout << "code" << std::endl;
            for (const auto& code : codesection) {
                std::cout << code << std::endl;
            }
            std::cout << "data" << std::endl;
            for (const auto& data : datasection) {
                std::cout << data << std::endl;
            }
#endif
        } else {
            std::cout << "ir error" << std::endl;
            return 1;
        }
        vmrun(s, debugprint, codesection, datasection);
    }
    return 0;
}
