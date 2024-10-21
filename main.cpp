#include "cpiatti.hpp"
#include <string>
#include <iostream>

int main(int argc, char** argv){
    if (argc <= 1){
        std::cout << "error needed a file path" << std::endl;
        return 1;
    }
    if (argc > 2){
        std::cout << "error too many arguments" << std::endl;
        return 1;
    }
    if (argc == 2){
    std::string inputfilename = argv[1]; 
    std::string outputfilename = "output.irpiatti";
    genir(inputfilename, outputfilename);
    }
    return 0;
}
