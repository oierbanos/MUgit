#ifndef MUGIMENDUA
#define MUGIMENDUA
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

int* kalkulatu(ptrMugi burua, ptrPuntua* burua2, FILE* fitxategia, int* Grafo, int jokalaria);
void mugitu(float x, float y, float z, float k, float j, float i, FILE** fitxategia, ptrPuntua* burua, int** Grafo);
int JOKOA_jokalariaIrudiaSortu(ptrPuntua ptrAux);

#endif