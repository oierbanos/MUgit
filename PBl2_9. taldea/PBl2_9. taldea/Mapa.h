#ifndef DRAW_THE_MAP
#define DRAW_THE_MAP
#include <stdlib.h>
#include "Erabilgarriak.h"
#include"SDL.h"

typedef struct
{
	POS pos;
	int id;
}MAPA_ELEMENTUA;

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, float* pisuak, ptrMugi* mugiBurua, DIM mapDim, char* mapName);
void grafoaMarraztu(ptrPuntua* burua, float* pisuak);
void zirkuluaMarraztu(float x, float y, int r);
char enteroACaracter(ptrPuntua ptrAux);

#endif