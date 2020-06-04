#ifndef BITMAP
#define BITMAP
#include "Erabilgarriak.h"

typedef struct DE_MAP_POINTS 
{
	POS pos;
	int* konexioak;
} MP;

void eskatuIrudia(char* img);
DIM eskatuDimentzioak(char* aukera);
void ordenatu(MP* points, int pkop);
void konektatu(MP** points, int org, int dest);
void bitmap(MP** points, int* pkop, DIM* mapDim);
int checkPlace(MP* points, int kont, SDL_Event ebentu);
void aukeraJaso(SDL_Event ebentu, int* option, char* input);
void koordenatuakGorde(MP** points, int* kont, float mouseX, float mouseY);

#endif