#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "piatti.hpp"

int main(int argc, char **argv) {
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
        std::vector<std::pair<int, int>> pairtable;
        std::stack<long> s;
        bool debugprint = false;
        ret = genir(inputfilename, codesection, datasection);
        if (ret == 0) {
            // std::cout << "ir generated" << std::endl;
            /*
            std::cout << "code" << std::endl;
            for (const auto& code : codesection) {
                 std::cout << code << std::endl;
            }
            std::cout << "data" << std::endl;
            for (const auto& data : datasection) {
                 std::cout << data << std::endl;
            }
            */
        } else {
            std::cout << "ir error" << std::endl;
            return 1;
        }
        pairtable = gen_pairtable(codesection);
        // std::cout << "table generated" << std::endl;
        /*
        for (const auto& pair : pairtable) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
        */
        vmrun(s, debugprint, codesection, datasection, pairtable);
    }
    return 0;
}
