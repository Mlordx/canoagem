#include <stdlib.h>
#include <stdio.h>


void* mallocSafe (size_t n){
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n");
    exit(-1);
  }
  return pt;
}
