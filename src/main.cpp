#include "cpiatti.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cout << "error needed a file path" << std::endl;
        return 1;
    }
    if (argc > 2)
    {
        std::cout << "error too many arguments" << std::endl;
        return 1;
    }
    if (argc == 2)
    {
        std::string inputfilename = argv[1];
        int ret = 0;
        std::vector<int> codesection;
        std::vector<std::string> datasection;
        std::vector<std::shared_ptr<std::string>> ptrtable;
        ret = genir(inputfilename, codesection, datasection);
        if (ret == 0)
        {
            std::cout << "ir generated" << std::endl;
        }
        else
        {
            std::cout << "ir error" << std::endl;
            return 1;
        }
        ptrtable = gen_ptrtable(codesection, datasection);
        std::cout << "table generated" << std::endl;
        for (const auto& ptr : ptrtable) {
        if (ptr) {
            std::cout << *ptr << std::endl; 
        } else {
            std::cout << "nullptr" << std::endl; 
        }
    }
    }
    return 0;
}
