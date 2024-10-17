#include "cpiatti.hpp"
#include <iostream>
#include <cstdlib>
//default compiler clang++

void compile_program(std::string input, std::string output) {
    int ret = 0;
    std::string cmd = "clang++ " + input + " -lcpiatti -o " + output;
    ret = std::system(cmd.c_str());
    if (ret != 0){
        std::cerr << "fail to compile: " << std::endl
        <<  cmd << std::endl;
    }
      
}

void run_program(std::string path) {
    int ret = 0;
    ret = std::system(path.c_str());
    if (ret != 0){
        std::cerr << "fail to run: " << std::endl
        <<  path << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string input = "/tmp/tmppiattiout.c";
    std::string output = "/tmp/tmppiattiout";

    if (argc < 2) {
        fprintf(stderr, "error: too few arguments\n");
        exit(1);
    }
    if (argc == 2) {
        transpile(argv[1]);
    }
    if (argc > 2) {
        fprintf(stderr, "error: too many arguments\n");
        exit(1);
    }
    
    compile_program(input, output);
    run_program(output);

    return 0;
}
