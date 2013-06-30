#ifndef BARCO_H
#define BARCO_H

#include "vetor2D.h"
#include "rio.h"


typedef struct barco* BarcoT;


BarcoT novoBarco(Vetor2D, Vetor2D, Vetor2D, int);
Vetor2D getVelocidadeBarco(BarcoT);
Vetor2D getPosBarco(BarcoT);
Vetor2D getTamBarco(BarcoT);
void setVelocidadeBarco(BarcoT, Vetor2D);
Vetor2D atualizaPos(BarcoT, float);
void atualizaBarco(BarcoT,int, int, float, float);
int estaBatendo(BarcoT, Rio);

int getVida(BarcoT);
int setVida(BarcoT,int);








#endif
