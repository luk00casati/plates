#include "cpiatti.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        fprintf(stderr, "error: too few armuments\n");
        exit(1);
    }
    if (argc == 2){
        transpile(argv[1], "hidden");
    }
    if (argc == 3){
        transpile(argv[2], "show");
    }
    printf("%d\n", argc);
    return 0;
}