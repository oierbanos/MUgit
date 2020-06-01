#ifndef MUGIMENDUA
#define MUGIMENDUA
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

void mugitu(float propX, float propY, POS org, POS dest, int mugit, SDL_Window* window, ptrPuntua* pBurua, FILE* fitxategia, float* pisuak);
int movement(ptrPuntua* burua, ptrPuntua ptrAux, ptrMugi* mugiBurua, FILE* fitxategia, float** pisuak, int mugit, int* idOrg, SDL_Window* window);
void kalkulatuMugimendua(ptrPuntua pBurua, ptrMugi mBurua, FILE* fitxategia, float* pisuak, int jokalaria, SDL_Window* window);
int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest);

#endif