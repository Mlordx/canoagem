#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include <time.h>




int main(int argc, char* argv[])
{
    Rio nilo;
    int milisec = 100; // length of time to sleep, in miliseconds
    struct timespec req = {0};

    nilo = alocaRio(30,100,0,0);
    rioInit(nilo);


    while(1)
    {
        desenhaRio(nilo);



      req.tv_sec = 0;
      req.tv_nsec = milisec * 1000000L;
      nanosleep(&req, (struct timespec *)NULL);


        system("clear");
        atualizaRio(nilo);
    }
    return 0;
}
