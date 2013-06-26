#ifndef BARCO_H
#define BARCO_H

#include "vetor2D.h"


typedef struct barco* BarcoT;


BarcoT novoBarco(Vetor2D, Vetor2D, Vetor2D);
Vetor2D getVelocidadeBarco(BarcoT);
Vetor2D getPosBarco(BarcoT);
Vetor2D getTamBarco(BarcoT);
Vetor2D setVelocidadeBarco(BarcoT, Vetor2D);
Vetor2D atualizaPos(BarcoT, float);








#endif
