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

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak, ptrMugi* burua2);
void zirkuluaMarraztu(int x, int y, int r);
void zuzenakMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak);
char enteroACaracter(ptrPuntua ptrAux);

#endif