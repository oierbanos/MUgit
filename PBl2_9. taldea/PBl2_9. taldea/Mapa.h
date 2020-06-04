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

void zirkuluaMarraztu(float x, float y, int r);
void grafoaMarraztu(ptrPuntua* burua, float* pisuak);
void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, float* pisuak, ptrMugi* mugiBurua, char* mapName);

#endif