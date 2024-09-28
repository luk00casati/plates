#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool bool_debug = false;
bool bool_noout = false;

struct Sstack {
  unsigned int *ptr;
  unsigned int size;
} stack;

void debug(){
  bool_debug = true;
}

void noout(){
  bool_noout = true;
}

void init_stack() {
  stack.size = 0;
  stack.ptr = NULL;
}

void deinit_stack() {
  if (stack.size == 0) {
    if (bool_debug) {
      printf("DEBUG no need to deinit size: %d\n", stack.size);
    }
    return;
  }
  if (stack.size > 0) {
    if (bool_debug) {
      printf("DEBUG need to deinit size: %d\n", stack.size);
    }
    if (stack.ptr != NULL) {
      free(stack.ptr);
    } else {
      printf("WARMING NULL PTR ON DEINIT\nPANIC!!!\n");
      exit(1);
    }
  }
}

void push(const unsigned int val) {
  if (stack.size == 0) {
    stack.size++;
    stack.ptr = malloc(stack.size * sizeof(unsigned int));
    if (stack.ptr != NULL) {
      stack.ptr[0] = val;
      if (bool_debug) {
        printf("DEBUG push: \n%d\n", stack.ptr[0]);
      }
    } else {
      printf("\nerror null ptr on push malloc\n");
      exit(1);
    }
  } else if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size++;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = val;
        if (bool_debug) {
          printf("DEBUG push:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on push realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on push size > 0\n");
      exit(1);
    }
  }
}

void pop() {
  if (stack.size == 0) {
    printf("\npop on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      if (bool_debug) {
        printf("DEBUG pop: \n%d -> EMPTY\n", stack.ptr[0]);
      }
      free(stack.ptr);
    } else {
      printf("\nerror on free pop\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        if (bool_debug) {
          printf("DEBUG pop:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on pop realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on pop size > 1\n");
      exit(1);
    }
  }
}

void rot() {
  if (stack.size >= 2) {
    if (stack.ptr != NULL) {
      if (bool_debug) {
        printf("DEBUG rot before:\n");
        for (unsigned int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\nDEBUG rot after:\n");
      }
      unsigned int temp;
      unsigned int start = 0;
      unsigned int end = stack.size - 1;
      while (start < end) {
        temp = stack.ptr[start];
        stack.ptr[start] = stack.ptr[end];
        stack.ptr[end] = temp;
        start++;
        end--;
      }
      if (bool_debug) {
        for (unsigned int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
      }
    } else {
      printf("\nnull ptr on rot\n");
      exit(1);
    }
  }
}

void put() {
  if (stack.size == 0) {
    printf("\nput on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      if (bool_debug) {
        printf("DEBUG put: \n%d -> EMPTY\n", stack.ptr[0]);
      }
      if (!bool_noout) {
        printf("%d", stack.ptr[0]);
      }
      free(stack.ptr);
    } else {
      printf("\nerror on free put\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        if (!bool_noout) {
          printf("%d", stack.ptr[stack.size]);
        }
        if (bool_debug) {
          printf("DEBUG put:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on put realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on put size > 1\n");
      exit(1);
    }
  }
}

void putc() {
  if (stack.size == 0) {
    printf("\nputc on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      if (bool_debug) {
        printf("DEBUG putc: \n%d -> EMPTY\n", stack.ptr[0]);
      }
      if (!bool_noout) {
        printf("%c", stack.ptr[0]);
      }
      free(stack.ptr);
    } else {
      printf("\nerror on free putc\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        if (!bool_noout) {
          printf("%c", stack.ptr[stack.size]);
        }
        if (bool_debug) {
          printf("DEBUG putc:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on putc realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on putc size > 1\n");
      exit(1);
    }
  }
}

void copy() {
  if (stack.size == 0) {
    printf("\nerror copy on empty stack\n");
    exit(1);
  } else if (stack.size >= 1) {
    if (stack.ptr != NULL) {
      stack.size++;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = stack.ptr[stack.size - 2];
        if (bool_debug) {
          printf("DEBUG copy:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on copy realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on copy\n");
      exit(1);
    }
  }
}

void swap() {
  if (stack.size == 0) {
    printf("\nerror swap on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror swap on sigle item\n");
    exit(1);
  } else if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int tmp = stack.ptr[stack.size - 1];
      stack.ptr[stack.size - 1] = stack.ptr[stack.size - 2];
      stack.ptr[stack.size - 2] = tmp;
      if (bool_debug) {
        printf("DEBUG swap:\n");
        for (unsigned int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
      }
    } else {
      printf("\nnull ptr on swap\n");
      exit(1);
    }
  }
}

void sub() {
  if (stack.size == 0) {
    printf("\nsub on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror sub on sigle item\n");
    exit(1);
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int res = stack.ptr[stack.size - 1] - stack.ptr[stack.size - 2];
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
        if (bool_debug) {
          printf("DEBUG sub:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on sub realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on sub size > 1\n");
      exit(1);
    }
  }
}

void sum() {
  if (stack.size == 0) {
    printf("\nsum on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror sum on sigle item\n");
    exit(1);
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int res = stack.ptr[stack.size - 1] + stack.ptr[stack.size - 2];
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
        if (bool_debug) {
          printf("DEBUG sum:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on sum realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on sum size > 1\n");
      exit(1);
    }
  }
}

void mul() {
  if (stack.size == 0) {
    printf("\nmul on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror mul on sigle item\n");
    exit(1);
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int res = stack.ptr[stack.size - 1] * stack.ptr[stack.size - 2];
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
        if (bool_debug) {
          printf("DEBUG mul:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on mul realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on mul size > 1\n");
      exit(1);
    }
  }
}

void div() {
  if (stack.size == 0) {
    printf("\ndiv on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror div on sigle item\n");
    exit(1);
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int res = stack.ptr[stack.size - 1] / stack.ptr[stack.size - 2];
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
        if (bool_debug) {
          printf("DEBUG div:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on div realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on div size > 1\n");
      exit(1);
    }
  }
}

void rem() {
  if (stack.size == 0) {
    printf("\nrem on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror rem on sigle item\n");
    exit(1);
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      unsigned int res = stack.ptr[stack.size - 1] % stack.ptr[stack.size - 2];
      stack.size--;
      unsigned int *tmp = realloc(stack.ptr, stack.size * sizeof(unsigned int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
        if (bool_debug) {
          printf("DEBUG rem:\n");
          for (unsigned int i = 0; i < stack.size; i++) {
            printf("%d ", stack.ptr[i]);
          }
          printf("\n");
        }
      } else {
        printf("\nerror null ptr on rem realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on rem size > 1\n");
      exit(1);
    }
  }
}

void drop() {
  if (stack.size == 0) {
    printf("\ndrop on empty stack\n");
    exit(1);
  }
  if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size = 0;
      free(stack.ptr);
      if (bool_debug) {
        printf("DEBUG drop:\nEMPTY\n");
      }
    } else {
      printf("\nerror null ptr on drop\n");
      exit(1);
    }
  }
}
