#include <stdio.h>
#include <stdlib.h>

// init
#define DEBUG

int *ptr;
int size = 0;

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
        printf("\nDEBUG push: %d\n", arg);
      #endif
    } else {
      printf("\nerror null ptr on push malloc\n");
      exit(1);
    }
  } else if (size > 0) {
    if (ptr != NULL) {
      size++;
      int* tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        ptr[size - 1] = arg;
        #ifdef DEBUG
          printf("\nDEBUG push: %d\n", arg);
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
        printf("\nDEBUG pop: %d\n", ptr[0]);
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
      int* tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        ptr = tmp;
        #ifdef DEBUG
          printf("\nDEBUG pop: %d\n", ptr[size]);
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

void rot(){
  if (size < 0) {
    printf("\nnegative size error on rot\n");
    exit(1);
  }
  if (size >= 2){
    if (ptr != NULL){
      int tmp[size];
      #ifdef DEBUG
        printf("\nDEBUG rot before:\n");
        for (int i = 0; i < size; i++){
          printf("%d,", ptr[i]);
        }
        printf("\nDEBUG rot after:\n");
      #endif
      int temp;
      int start = 0;
      int end = size -1 ;
      while (start < end) { 
        temp = ptr[start]; 
        ptr[start] = ptr[end]; 
        ptr[end] = temp; 
        start++; 
        end--; 
      } 
      #ifdef DEBUG 
        for (int y = 0; y < size; y++){
          printf("%d,", ptr[y]);
        }
        printf("\n");
      #endif
    }
    else {
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
      /*
      #ifdef DEBUG
        printf("\nDEBUG put: %d\n", ptr[0]);
      #endif
      */
      printf("%d", ptr[0]);
      free(ptr);
    } else {
      printf("\nerror on free put\n");
      exit(1);
    }
  }
  if (size > 1) {
    if (ptr != NULL) {
      size--;
      int* tmp = (int *)realloc(ptr, size * sizeof(int));
      if (tmp != NULL) {
        printf("%d", ptr[size]);
        /*
        #ifdef DEBUG
          printf("\nDEBUG put: %d\n", ptr[size]);
        #endif
        */
        ptr = tmp;
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
