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

// Zirkulu bat koordenatu zehatz batzuetan marraztu
void zirkuluaMarraztu(float x, float y, int r);
// Kargatutako mapa baten grafoa marraztu
void grafoaMarraztu(ptrPuntua* burua, float* pisuak);
// Mapa bat marraztu (Grafoa + irudia)
void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, float* pisuak, ptrMugi* mugiBurua, char* mapName);

#endif