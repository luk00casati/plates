#include <stdio.h>
#include <stdlib.h>

// config
// #define DEBUG
// #define NOOUT

struct Sstack {
  int *ptr;
  int size;
  int store;
};

struct Sstack stack;

void init_stack() {
  stack.size = 0;
  stack.store = 0;
}

void deint_stack() {
  if (stack.size < 0) {
    printf("\nnegative size error on deinit\n");
    exit(1);
  }
  if (stack.size == 0) {
#ifdef DEBUG
    printf("DEBUG no need to deinit size: %d\n", stack.size);
#endif
  }
  if (stack.size > 0) {
#ifdef DEBUG
    printf("DEBUG need to deinit size: %d\n", stack.size);
#endif
    if (stack.ptr != NULL) {
      free(stack.ptr);
    } else {
      printf("WARMING NULL PTR ON DEINIT\nPANIC!!!\n");
      exit(1);
    }
  }
}

void push(int arg) {
  if (stack.size < 0) {
    printf("\nnegative size error on push\n");
    exit(1);
  }
  if (stack.size == 0) {
    stack.size++;
    stack.ptr = (int *)malloc(stack.size * sizeof(int));
    if (stack.ptr != NULL) {
      stack.ptr[0] = arg;
#ifdef DEBUG
      printf("DEBUG push: \n%d\n", stack.ptr[0]);
#endif
    } else {
      printf("\nerror null ptr on push malloc\n");
      exit(1);
    }
  } else if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size++;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = arg;
#ifdef DEBUG
        printf("DEBUG push:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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

void sgetc() {
  if (stack.size < 0) {
    printf("\nnegative size error on sgetc\n");
    exit(1);
  }
  if (stack.size == 0) {
    stack.size++;
    stack.ptr = (int *)malloc(stack.size * sizeof(int));
    if (stack.ptr != NULL) {
      char input;
      scanf("%c", &input);
      stack.ptr[0] = (int) input;
#ifdef DEBUG
      printf("DEBUG sgetc: \n%d\n", stack.ptr[0]);
#endif
    } else {
      printf("\nerror null ptr on sgetc malloc\n");
      exit(1);
    }
  } else if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size++;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        char input;
        stack.ptr = tmp;
        scanf("%c", &input);
        stack.ptr[stack.size - 1] = (int) input;
#ifdef DEBUG
        printf("DEBUG sgetc:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
      } else {
        printf("\nerror null ptr on sgetc realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on sgetc size > 0\n");
      exit(1);
    }
  }
}

void sgeti() {
  if (stack.size < 0) {
    printf("\nnegative size error on sgeti\n");
    exit(1);
  }
  if (stack.size == 0) {
    stack.size++;
    stack.ptr = (int *)malloc(stack.size * sizeof(int));
    if (stack.ptr != NULL) {
      int input;
      scanf("%d", &input);
      stack.ptr[0] = input;
#ifdef DEBUG
      printf("DEBUG sgeti: \n%d\n", stack.ptr[0]);
#endif
    } else {
      printf("\nerror null ptr on sgeti malloc\n");
      exit(1);
    }
  } else if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size++;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        int input;
        stack.ptr = tmp;
        scanf("%d", &input);
        stack.ptr[stack.size - 1] = input;
#ifdef DEBUG
        printf("DEBUG sgeti:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
      } else {
        printf("\nerror null ptr on sgeti realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on sgeti size > 0\n");
      exit(1);
    }
  }
}

void pop() {
  if (stack.size < 0) {
    printf("\nnegative size error on pop\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\npop on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
#ifdef DEBUG
      printf("DEBUG pop: \n%d -> EMPTY\n", stack.ptr[0]);
#endif
      free(stack.ptr);
    } else {
      printf("\nerror on free pop\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
#ifdef DEBUG
        printf("DEBUG pop:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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

void stpop() {
  if (stack.size < 0) {
    printf("\nnegative size error on stpop\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\nstpop on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
#ifdef DEBUG
      printf("DEBUG stpop: \n%d -> EMPTY\n", stack.ptr[0]);
      printf("stored: %d\n", stack.ptr[0]);
#endif
      stack.store = stack.ptr[0];
      free(stack.ptr);
    } else {
      printf("\nerror on free stpop\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      stack.store = stack.ptr[stack.size - 1];
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
#ifdef DEBUG
        printf("DEBUG stpop:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\nstored: %d\n", stack.store);
#endif
      } else {
        printf("\nerror null ptr on stpop realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on stpop size > 1\n");
      exit(1);
    }
  }
}

void rot() {
  if (stack.size < 0) {
    printf("\nnegative size error on rot\n");
    exit(1);
  }
  if (stack.size >= 2) {
    if (stack.ptr != NULL) {
      int tmp[stack.size];
#ifdef DEBUG
      printf("DEBUG rot before:\n");
      for (int i = 0; i < stack.size; i++) {
        printf("%d ", stack.ptr[i]);
      }
      printf("\nDEBUG rot after:\n");
#endif
      int temp;
      int start = 0;
      int end = stack.size - 1;
      while (start < end) {
        temp = stack.ptr[start];
        stack.ptr[start] = stack.ptr[end];
        stack.ptr[end] = temp;
        start++;
        end--;
      }
#ifdef DEBUG
      for (int i = 0; i < stack.size; i++) {
        printf("%d ", stack.ptr[i]);
      }
      printf("\n");
#endif
    } else {
      printf("\nnull ptr on rot\n");
      exit(1);
    }
  }
}

void put() {
  if (stack.size < 0) {
    printf("\nnegative size error on put\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\nput on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
#ifdef DEBUG
      printf("DEBUG put: \n%d -> EMPTY\n", stack.ptr[0]);
#endif
#ifndef NOOUT
      printf("%d", stack.ptr[0]);
#endif
      free(stack.ptr);
    } else {
      printf("\nerror on free put\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
#ifndef NOOUT
        printf("%d", stack.ptr[stack.size]);
#endif
#ifdef DEBUG
        printf("DEBUG put:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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

void aput() {
  if (stack.size < 0) {
    printf("\nnegative size error on aput\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\naput on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    if (stack.ptr != NULL) {
      stack.size--;
#ifdef DEBUG
      printf("DEBUG aput: \n%d -> EMPTY\n", stack.ptr[0]);
#endif
#ifndef NOOUT
      printf("%c", stack.ptr[0]);
#endif
      free(stack.ptr);
    } else {
      printf("\nerror on free aput\n");
      exit(1);
    }
  }
  if (stack.size > 1) {
    if (stack.ptr != NULL) {
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
#ifndef NOOUT
        printf("%c", stack.ptr[stack.size]);
#endif
#ifdef DEBUG
        printf("DEBUG aput:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
      } else {
        printf("\nerror null ptr on aput realloc\n");
        exit(1);
      }
    } else {
      printf("\nnull ptr on aput size > 1\n");
      exit(1);
    }
  }
}

void copy() {
  if (stack.size < 0) {
    printf("\nnegative size error on copy\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\nerror copy on empty stack\n");
    exit(1);
  } else if (stack.size >= 1) {
    if (stack.ptr != NULL) {
      stack.size++;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = stack.ptr[stack.size - 2];
#ifdef DEBUG
        printf("DEBUG copy:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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
  if (stack.size < 0) {
    printf("\nnegative size error on swap\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\nerror swap on empty stack\n");
    exit(1);
  }
  if (stack.size == 1) {
    printf("\nerror swap on sigle item\n");
    exit(1);
  } else if (stack.size > 1) {
    if (stack.ptr != NULL) {
      int tmp = stack.ptr[stack.size - 1];
      stack.ptr[stack.size - 1] = stack.ptr[stack.size - 2];
      stack.ptr[stack.size - 2] = tmp;
#ifdef DEBUG
      printf("DEBUG swap:\n");
      for (int i = 0; i < stack.size; i++) {
        printf("%d ", stack.ptr[i]);
      }
      printf("\n");
#endif
    } else {
      printf("\nnull ptr on swap\n");
      exit(1);
    }
  }
}

void sub() {
  if (stack.size < 0) {
    printf("\nnegative size error on sub\n");
    exit(1);
  }
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
      int res = stack.ptr[stack.size - 1] - stack.ptr[stack.size - 2];
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
#ifdef DEBUG
        printf("DEBUG sub:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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
  if (stack.size < 0) {
    printf("\nnegative size error on sum\n");
    exit(1);
  }
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
      int res = stack.ptr[stack.size - 1] + stack.ptr[stack.size - 2];
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
#ifdef DEBUG
        printf("DEBUG sum:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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
  if (stack.size < 0) {
    printf("\nnegative size error on mul\n");
    exit(1);
  }
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
      int res = stack.ptr[stack.size - 1] * stack.ptr[stack.size - 2];
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
#ifdef DEBUG
        printf("DEBUG mul:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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

void sdiv() {
  if (stack.size < 0) {
    printf("\nnegative size error on div\n");
    exit(1);
  }
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
      int res = stack.ptr[stack.size - 1] / stack.ptr[stack.size - 2];
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
#ifdef DEBUG
        printf("DEBUG div:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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
  if (stack.size < 0) {
    printf("\nnegative size error on rem\n");
    exit(1);
  }
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
      int res = stack.ptr[stack.size - 1] % stack.ptr[stack.size - 2];
      stack.size--;
      int *tmp = (int *)realloc(stack.ptr, stack.size * sizeof(int));
      if (tmp != NULL) {
        stack.ptr = tmp;
        stack.ptr[stack.size - 1] = res;
#ifdef DEBUG
        printf("DEBUG rem:\n");
        for (int i = 0; i < stack.size; i++) {
          printf("%d ", stack.ptr[i]);
        }
        printf("\n");
#endif
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
  if (stack.size < 0) {
    printf("\nnegative size error on drop\n");
    exit(1);
  }
  if (stack.size == 0) {
    printf("\ndrop on empty stack\n");
    exit(1);
  }
  if (stack.size > 0) {
    if (stack.ptr != NULL) {
      stack.size = 0;
      free(stack.ptr);
#ifdef DEBUG
      printf("DEBUG drop:\nEMPTY\n");
#endif
    } else {
      printf("\nerror null ptr on drop\n");
      exit(1);
    }
  }
}