#include "cpiatti.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//default compiler clang

int compile_program(const char* input, const char* output) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("error: fork failed");
        return 1;
    } else if (pid == 0) {
        execl("/usr/bin/clang", "clang", \
        input, "-lcpiatti", \
        "-o", output, NULL);
        perror("error: exec clang failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 0;
        } else {
            fprintf(stderr, "error: compiling error\n");
            return 1;
        }
    }
}

int run_program(const char* path) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("error: fork failed");
        return 1;
    } else if (pid == 0) {
        execl(path, path, NULL);
        perror("error: exec program failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 0;
        } else {
            fprintf(stderr, "error: executable error\n");
            return 1;
        }
    }
}

int main(int argc, char** argv) {
    const char* input = "/tmp/tmppiattiout.c";
    const char* output = "/tmp/tmppiattiout";

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

    if (compile_program(input, output) != 0) {
        exit(1);
    }

    if (run_program(output) != 0) {
        exit(1);
    }

    return 0;
}
