#ifndef BITMAP
#define BITMAP
#include "Erabilgarriak.h"

typedef struct DE_MAP_POINTS 
{
	POS pos;
	int* konexioak;
} MP;

DIM eskatuDimentzioak(void);
void bitmap(MP** points, int* pkop);
void ordenatu(MP* points, int pkop);
int eskatuIrudia(SDL_Window* window);
void konektatu(MP** points, int org, int dest);
int checkPlace(MP* points, int kont, SDL_Event ebentu);
void koordenatuakGorde(MP** points, int* kont, float mouseX, float mouseY);

#endif