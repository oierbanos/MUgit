#ifndef BITMAP
#define BITMAP
#include "Erabilgarriak.h"

typedef struct B_KONEXIOAK
{
	int org;
	int dest;
} CONECT;

void bitmap(void);
DIM eskatuDimentzioak(void);
int checkPlace(POS* points, int kont, SDL_Event ebentu);
void konexioBerria(POS org, POS dest, CONECT** konexioak, int* kont);
void koordenatuakGorde(POS** points, int* kont, float mouseX, float mouseY);

#endif