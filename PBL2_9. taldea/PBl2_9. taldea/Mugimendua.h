#ifndef MUGIMENDUA
#define MUGIMENDUA
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

int irudiaSortu(ptrPuntua ptrAux);
int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest);
void mugitu(float propX, float propY, POS org, POS dest, int jokalaria, FILE* fitxategia, float* pisuak, ptrPuntua pBurua);
int movement(ptrPuntua* burua, ptrPuntua ptrAux, ptrMugi* mugiBurua, FILE* fitxategia, float** pisuak, int mugit, int* idOrg);
void kalkulatuMugimendua(ptrPuntua pBurua, ptrMugi mBurua, FILE* fitxategia, float* pisuak, int jokalaria);

#endif