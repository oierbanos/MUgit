#ifndef MUGIMENDUA
#define MUGIMENDUA
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

// Irudi bat pantailan marraztu
int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest);
// Mapa pantailan marraztu
void marraztu(int mugit, float x, float y, ptrPuntua* pBurua, float* pisuak, SDL_Window* window);
// Puntu batetik besterako mugimendua kalkulatu
void kalkulatuMugimendua(ptrPuntua pBurua, ptrMugi mBurua, FILE* fitxategia, float* pisuak, int jokalaria, SDL_Window* window);
// Robota mugitu
void mugitu(float propX, float propY, POS org, POS dest, int mugit, SDL_Window* window, ptrPuntua* pBurua, FILE* fitxategia, float* pisuak);
// Mugimendua kontrolatu
int movement(ptrPuntua* burua, ptrPuntua ptrAux, ptrMugi* mugiBurua, FILE* fitxategia, float** pisuak, int mugit, int* idOrg, SDL_Window* window);

#endif