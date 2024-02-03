#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sts {
  unsigned nline;
  unsigned start_string;
  unsigned end_string;
  char *word;
  char *file;
  unsigned n_openbrackets;
  unsigned n_closedbrackets;
  unsigned n_quotes;
  unsigned n_loop;
  unsigned n_for_loop;
};

struct Sts ts;

char* substring(const char *str, size_t start, size_t end) {
    size_t len = strlen(str);

    // Check for valid input indices
    if (start >= len || end > len || start > end) {
        fprintf(stderr, "Invalid substring indices\n");
        return NULL;
    }

    // Allocate memory for the substring
    char* ret_str = (char*)malloc((end - start + 1) * sizeof(char));

    // Check for memory allocation failure
    if (ret_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Copy characters to the substring
    for (size_t i = 0; i < end - start; i++) {
        ret_str[i] = str[i + start];
    }

    // Null-terminate the substring
    ret_str[end - start] = '\0';

    return ret_str;
}


int main() {
  const char *str = "PUSH 10 POP";
  unsigned len = strlen(str);
  // FILE *fptr;
  // fptr = fopen("out.c", "w");
  //ts.end_string = 0;
  //ts.start_string = 0;
  for (int i = 0; i <= len; i++) {
    if (str[i] == ' ' || i == len) {
      // printf("%d", i);
      ts.start_string = ts.end_string;
      ts.end_string = i;
      char* sstr = substring(str, ts.start_string, ts.end_string);
      printf("%s\n", sstr);
      free(sstr);
    }
  }
}