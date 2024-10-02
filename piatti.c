#include <cpiatti.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// cc default clang

int uniquechar(const char* str)
{
    for (size_t i = 0; i < strlen(str) - 1; i++) {
        for (size_t j = i + 1; j < strlen(str); j++) {
            if (str[i] == str[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv){
    int r = 0;
    char* outputfile = NULL;
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
    if (argc > 3){
        fprintf(stderr, "error: too many armuments\n");
        exit(1);
    }
    r = system("clang /tmp/temppiattiout.c -lcpiatti -o /tmp/temppiattiout");
        if (r == 1){
            fprintf(stderr, "error: compiling error\n");
            exit(1);
        }
    r = system("clang /tmp/temppiattiout");
        if (r == 1){
            fprintf(stderr, "error: executable error\n");
            exit(1);
        }
    return 0;
}
