#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void* mallocSafe (size_t n){
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n");
    exit(-1);
  }
  return pt;
}

void meuSleep(int ms)
{
  struct timespec req = {0};

  req.tv_sec = 0;
  req.tv_nsec = ms * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);


}
