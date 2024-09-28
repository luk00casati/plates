#include <stdio.h>
#include <stdlib.h>

struct Stack {
  unsigned int *ptr;
  unsigned int size;
  short int debugprint;
};

void init_stack(struct Stack* s) {
  s->size = 0;
  s->ptr = NULL;
  s->debugprint = 0;
}

void debugenable(struct Stack* s){
  s->debugprint = 1;
}

void deinit_stack(struct Stack* s) {
  if (s->size == 0) {
    if (s->debugprint) {
      printf("DEBUG no need to deinit size: %d\n", s->size);
    }
    return;
  }
  if (s->size > 0) {
    if (s->debugprint) {
      printf("DEBUG need to deinit size: %d\n", s->size);
    }
    if (s->ptr != NULL) {
      free(s->ptr);
    } else {
      printf("WARMING NULL PTR ON DEINIT\nPANIC!!!\n");
      exit(1);
    }
  }
}

void push(struct Stack* s, const unsigned int val) {
  if (s->size == 0) {
    s->size++;
    s->ptr = malloc(s->size * sizeof(unsigned int));
    if (s->ptr != NULL) {
      s->ptr[0] = val;
      if (s->debugprint) {
        printf("DEBUG push: \n%d\n", s->ptr[0]);
      }
    } else {
      printf("\nerror null ptr on push malloc\n");
      exit(1);
    }
  } else if (s->size > 0) {
    if (s->ptr != NULL) {
      s->size++;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = val;
        if (s->debugprint) {
          printf("DEBUG push:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void pop(struct Stack* s) {
  if (s->size == 0) {
    printf("\npop on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    if (s->ptr != NULL) {
      s->size--;
      if (s->debugprint) {
        printf("DEBUG pop: \n%d -> EMPTY\n", s->ptr[0]);
      }
      free(s->ptr);
    } else {
      printf("\nerror on free pop\n");
      exit(1);
    }
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        if (s->debugprint) {
          printf("DEBUG pop:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void rot(struct Stack* s) {
  if (s->size >= 2) {
    if (s->ptr != NULL) {
      if (s->debugprint) {
        printf("DEBUG rot before:\n");
        for (unsigned int i = 0; i < s->size; i++) {
          printf("%d ", s->ptr[i]);
        }
        printf("\nDEBUG rot after:\n");
      }
      unsigned int temp;
      unsigned int start = 0;
      unsigned int end = s->size - 1;
      while (start < end) {
        temp = s->ptr[start];
        s->ptr[start] = s->ptr[end];
        s->ptr[end] = temp;
        start++;
        end--;
      }
      if (s->debugprint) {
        for (unsigned int i = 0; i < s->size; i++) {
          printf("%d ", s->ptr[i]);
        }
        printf("\n");
      }
    } else {
      printf("\nnull ptr on rot\n");
      exit(1);
    }
  }
}

void put(struct Stack* s) {
  if (s->size == 0) {
    printf("\nput on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    if (s->ptr != NULL) {
      s->size--;
      if (s->debugprint) {
        printf("DEBUG put: \n%d -> EMPTY\n", s->ptr[0]);
      }
      if (!s->debugprint) { //no out
        printf("%d", s->ptr[0]);
      }
      free(s->ptr);
    } else {
      printf("\nerror on free put\n");
      exit(1);
    }
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        if (!s->debugprint) { //no out
          printf("%d", s->ptr[s->size]);
        }
        if (s->debugprint) {
          printf("DEBUG put:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void sputc(struct Stack* s) {
  if (s->size == 0) {
    printf("\nputc on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    if (s->ptr != NULL) {
      s->size--;
      if (s->debugprint) {
        printf("DEBUG putc: \n%d -> EMPTY\n", s->ptr[0]);
      }
      if (!s->debugprint) { //no out
        printf("%c", s->ptr[0]);
      }
      free(s->ptr);
    } else {
      printf("\nerror on free putc\n");
      exit(1);
    }
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        if (!s->debugprint) { //no out
          printf("%c", s->ptr[s->size]);
        }
        if (s->debugprint) {
          printf("DEBUG putc:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void copy(struct Stack* s) {
  if (s->size == 0) {
    printf("\nerror copy on empty stack\n");
    exit(1);
  } else if (s->size >= 1) {
    if (s->ptr != NULL) {
      s->size++;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = s->ptr[s->size - 2];
        if (s->debugprint) {
          printf("DEBUG copy:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void swap(struct Stack* s) {
  if (s->size == 0) {
    printf("\nerror swap on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror swap on sigle item\n");
    exit(1);
  } else if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int tmp = s->ptr[s->size - 1];
      s->ptr[s->size - 1] = s->ptr[s->size - 2];
      s->ptr[s->size - 2] = tmp;
      if (s->debugprint) {
        printf("DEBUG swap:\n");
        for (unsigned int i = 0; i < s->size; i++) {
          printf("%d ", s->ptr[i]);
        }
        printf("\n");
      }
    } else {
      printf("\nnull ptr on swap\n");
      exit(1);
    }
  }
}

void sub(struct Stack* s) {
  if (s->size == 0) {
    printf("\nsub on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror sub on sigle item\n");
    exit(1);
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int res = s->ptr[s->size - 1] - s->ptr[s->size - 2];
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = res;
        if (s->debugprint) {
          printf("DEBUG sub:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void sum(struct Stack* s) {
  if (s->size == 0) {
    printf("\nsum on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror sum on sigle item\n");
    exit(1);
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int res = s->ptr[s->size - 1] + s->ptr[s->size - 2];
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = res;
        if (s->debugprint) {
          printf("DEBUG sum:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void mul(struct Stack* s) {
  if (s->size == 0) {
    printf("\nmul on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror mul on sigle item\n");
    exit(1);
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int res = s->ptr[s->size - 1] * s->ptr[s->size - 2];
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = res;
        if (s->debugprint) {
          printf("DEBUG mul:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void sdiv(struct Stack* s) {
  if (s->size == 0) {
    printf("\ndiv on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror div on sigle item\n");
    exit(1);
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int res = s->ptr[s->size - 1] / s->ptr[s->size - 2];
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = res;
        if (s->debugprint) {
          printf("DEBUG div:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void rem(struct Stack* s) {
  if (s->size == 0) {
    printf("\nrem on empty stack\n");
    exit(1);
  }
  if (s->size == 1) {
    printf("\nerror rem on sigle item\n");
    exit(1);
  }
  if (s->size > 1) {
    if (s->ptr != NULL) {
      unsigned int res = s->ptr[s->size - 1] % s->ptr[s->size - 2];
      s->size--;
      unsigned int *tmp = realloc(s->ptr, s->size * sizeof(unsigned int));
      if (tmp != NULL) {
        s->ptr = tmp;
        s->ptr[s->size - 1] = res;
        if (s->debugprint) {
          printf("DEBUG rem:\n");
          for (unsigned int i = 0; i < s->size; i++) {
            printf("%d ", s->ptr[i]);
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

void drop(struct Stack* s) {
  if (s->size == 0) {
    printf("\ndrop on empty stack\n");
    exit(1);
  }
  if (s->size > 0) {
    if (s->ptr != NULL) {
      s->size = 0;
      free(s->ptr);
      if (s->debugprint) {
        printf("DEBUG drop:\nEMPTY\n");
      }
    } else {
      printf("\nerror null ptr on drop\n");
      exit(1);
    }
  }
}
