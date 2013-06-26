#include <stdio.h>
#include <stdlib.h>
#include "barco.h"
#include "utils.h"


struct barco
{
  Vetor2D pos;
  Vetor2D vel;
  Vetor2D tam;
};


BarcoT novoBarco(Vetor2D pos, Vetor2D vel, Vetor2D tam)
{
    BarcoT barco;
    barco = mallocSafe(sizeof(*barco));

    barco->pos = pos;
    barco->vel = vel;
    barco->tam = tam;

    return barco;
}
Vetor2D getVelocidadeBarco(BarcoT barco)
{
    return barco->vel;
}
Vetor2D getPosBarco(BarcoT barco)
{
    return barco->pos;
}
Vetor2D setVelocidadeBarco(BarcoT barco, Vetor2D vel)
{
    barco->vel = vel;
}
Vetor2D getTamBarco(BarcoT barco)
{
    return barco->tam;
}

