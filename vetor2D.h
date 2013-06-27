#ifndef VETOR2D_H
#define VETOR2D_H


typedef struct vetor2d* Vetor2D;


Vetor2D novoVetor(float, float);


float getVetorX(Vetor2D);
float getVetorY(Vetor2D);

Vetor2D somaVetores(Vetor2D, Vetor2D);

void freeVetor(Vetor2D vetor);


void setVetorX(Vetor2D, float);
void setVetorY(Vetor2D, float);


void rotVetor(Vetor2D, float);

float getAngulo(Vetor2D);



#endif
