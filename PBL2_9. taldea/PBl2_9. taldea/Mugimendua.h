#ifndef MUGIMENDUA
#define MUGIMENDUA
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

void kalkulatu(ptrPuntua* burua2, ptrMugi* burua , FILE* fitxategia, int* Grafo, int jokalaria);
void mugitu(float x, float y, float z, float k, float j, float i, int jokalaria, FILE* fitxategia, int* pisuak, ptrPuntua* burua2);
int JOKOA_jokalariaIrudiaSortu(ptrPuntua ptrAux);
int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest);

#endif