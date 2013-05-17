#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include <time.h>




int main(int argc, char* argv[])
{
    Rio nilo;
    nilo = alocaRio(15,30,0,0);
    rioInit(nilo);


    while(1)
    {
        desenhaRio(nilo);



        meuSleep(100);

        system("clear");
        atualizaRio(nilo);
    }
    return 0;
}
