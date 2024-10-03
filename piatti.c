#include "cpiatti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// cc default clang

int main(int argc, char** argv){
    int r = 0;
    if (argc < 2){
        fprintf(stderr, "error: too few armuments\n");
        exit(1);
    }
    if (argc == 2){
        transpile(argv[1]);
    }
    if (argc > 2){
        fprintf(stderr, "error: too many armuments\n");
        exit(1);
    }
    r = system("clang /tmp/temppiattiout.c -lcpiatti -o /tmp/temppiattiout");
        if (r == 1){
            fprintf(stderr, "error: compiling error\n");
            exit(1);
        }
    r = system("/tmp/temppiattiout");
        if (r == 1){
            fprintf(stderr, "error: executable error\n");
            exit(1);
        }
    return 0;
}
