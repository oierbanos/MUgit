#ifndef DRAW_THE_MAP
#define DRAW_THE_MAP
#include <stdlib.h>
#include "Erabilgarriak.h"
#include"SDL.h"

/*typedef struct
{
    int x;
    int y;

}POSIZIOA;*/

typedef struct
{
    POS pos;
    int id;

}MAPA_ELEMENTUA;


void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, int** pisuak);
int maparenAtzekaldea();
void zuzenakMarraztu(FILE* fitxategia, ptrPuntua* burua, int** pisuak);
void erregulatu(ptrPuntua ptrAux, ptrPuntua ptrAux2);
char enteroACaracter(ptrPuntua ptrAux);

#endif