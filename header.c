#include <stdio.h>
#include <stdlib.h>

// config
#define DEBUG
#define NOOUT

// init
int *ptr;
int size = 0;
int store = 0;

void push(int arg) {
  if (size < 0) {
    printf("\nnegative size error on push\n");
    exit(1);
  }
  if (size == 0) {
    size++;
    ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
      ptr[0] = arg;
#ifdef DEBUG
      printf("DEBUG after push: \n%d\n", ptr[0]);
#endif
    } else {
      printf("\nerror null ptr on push malloc\n");
      exit(1);
    }
  } else if (size > 0) {
    if (ptr != NULL) {
      size++;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        ptr[size - 1] = arg;
#ifdef DEBUG
        printf("DEBUG push:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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

void pop() {
  if (size < 0) {
    printf("\nnegative size error on pop\n");
    exit(1);
  }
  if (size == 0) {
    printf("\npop on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    if (ptr != NULL) {
      size--;
#ifdef DEBUG
      printf("DEBUG pop: \n%d -> EMPTY\n", ptr[0]);
#endif
      free(ptr);
    } else {
      printf("\nerror on free pop\n");
      exit(1);
    }
  }
  if (size > 1) {
    if (ptr != NULL) {
      size--;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
#ifdef DEBUG
        printf("DEBUG pop:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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

void spop() {
  if (size < 0) {
    printf("\nnegative size error on spop\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nspop on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    if (ptr != NULL) {
      size--;
#ifdef DEBUG
      printf("DEBUG spop: \n%d -> EMPTY\n", ptr[0]);
#endif
      store = ptr[0];
      free(ptr);
    } else {
      printf("\nerror on free spop\n");
      exit(1);
    }
  }
  if (size > 1) {
    if (ptr != NULL) {
      size--;
      store = ptr[size - 1];
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
#ifdef DEBUG
        printf("DEBUG spop:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
        }
        printf("\nstored: %d\n", store);
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

void rot() {
  if (size < 0) {
    printf("\nnegative size error on rot\n");
    exit(1);
  }
  if (size >= 2) {
    if (ptr != NULL) {
      int tmp[size];
#ifdef DEBUG
      printf("DEBUG rot before:\n");
      for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
      }
      printf("\nDEBUG rot after:\n");
#endif
      int temp;
      int start = 0;
      int end = size - 1;
      while (start < end) {
        temp = ptr[start];
        ptr[start] = ptr[end];
        ptr[end] = temp;
        start++;
        end--;
      }
#ifdef DEBUG
      for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on put\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nput on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    if (ptr != NULL) {
      size--;
#ifdef DEBUG
      printf("DEBUG put: \n%d -> EMPTY\n", ptr[0]);
#endif
#ifndef NOOUT
      printf("%d", ptr[0]);
#endif
      free(ptr);
    } else {
      printf("\nerror on free put\n");
      exit(1);
    }
  }
  if (size > 1) {
    if (ptr != NULL) {
      size--;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
#ifndef NOOUT
        printf("%d", ptr[size]);
#endif
#ifdef DEBUG
        printf("DEBUG put:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on aput\n");
    exit(1);
  }
  if (size == 0) {
    printf("\naput on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    if (ptr != NULL) {
      size--;
#ifdef DEBUG
      printf("DEBUG aput: \n%d -> EMPTY\n", ptr[0]);
#endif
#ifndef NOOUT
      printf("%c", ptr[0]);
#endif
      free(ptr);
    } else {
      printf("\nerror on free aput\n");
      exit(1);
    }
  }
  if (size > 1) {
    if (ptr != NULL) {
      size--;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
#ifndef NOOUT
        printf("%c", ptr[size]);
#endif
#ifdef DEBUG
        printf("DEBUG aput:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on copy\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nerror copy on empty stack\n");
    exit(1);
  } else if (size >= 1) {
    if (ptr != NULL) {
      size++;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        ptr[size - 1] = ptr[size - 2];
#ifdef DEBUG
        printf("DEBUG copy:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on swap\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nerror swap on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    printf("\nerror swap on sigle item\n");
    exit(1);
  } else if (size > 1) {
    if (ptr != NULL) {
      int tmp = ptr[size - 1];
      ptr[size - 1] = ptr[size - 2];
      ptr[size - 2] = tmp;
#ifdef DEBUG
      printf("DEBUG swap:\n");
      for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on sub\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nsub on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    printf("\nerror sub on sigle item\n");
    exit(1);
  }
  if (size > 1) {
    if (ptr != NULL) {
      int res = ptr[size - 1] - ptr[size - 2];
      size--;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        ptr[size - 1] = res;
#ifdef DEBUG
        printf("DEBUG sub:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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
  if (size < 0) {
    printf("\nnegative size error on sum\n");
    exit(1);
  }
  if (size == 0) {
    printf("\nsum on empty stack\n");
    exit(1);
  }
  if (size == 1) {
    printf("\nerror sum on sigle item\n");
    exit(1);
  }
  if (size > 1) {
    if (ptr != NULL) {
      int res = ptr[size - 1] + ptr[size - 2];
      size--;
      int *tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        ptr[size - 1] = res;
#ifdef DEBUG
        printf("DEBUG sum:\n");
        for (int i = 0; i < size; i++) {
          printf("%d ", ptr[i]);
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