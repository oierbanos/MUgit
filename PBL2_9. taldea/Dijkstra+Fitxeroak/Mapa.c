#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphics.h"
#include "SDL.h"
#include "imagen.h"
#include "FileReading.h"
#include "Mapa.h"
#include "text.h"
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "math.h"

#define MAPAREN_ATZEKALDEA "Recursos PBL2/hoja en blanco.bmp"

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, int** pisuak) {

	MAPA_ELEMENTUA fondoa;
	int jarraitu = 0;

	if (sgHasieratu() == -1)
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		
	}
	else
	{
		textuaGaitu();
		fondoa.id = maparenAtzekaldea();
		zuzenakMarraztu(fitxategia, burua, pisuak);
		pantailaBerriztu();
	}
}


int maparenAtzekaldea() {

	int fondoId = -1;

	fondoId = irudiaKargatu(MAPAREN_ATZEKALDEA);
	irudiaMugitu(fondoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return fondoId;

}

void zuzenakMarraztu(FILE* fitxategia, ptrPuntua* burua, int** pisuak) {

	int pkop, i, j, konexioa = 0, kont, kont2, kont3=0;
	char str[2] = { '0', '\0' };

	puntuakJaso(burua, fitxategia);
	pisuakJaso(*burua, fitxategia, pisuak);
	ptrPuntua ptrAux = *burua;
	ptrPuntua ptrAux2 = *burua;
	pkop = puntuakZenbatu(*burua);
	arkatzKoloreaEzarri(300, 300, 300);

	while (ptrAux != NULL)
	{
		ptrAux->visitado = 0;
		ptrAux = ptrAux->ptrHurrengoa;
	}

	ptrAux = *burua;
	
	for (kont = 0; kont <= pkop; kont++) {

		j = 0;
		kont2 = 0;

		while (j != pkop) {
			i = 0;
			while (i != pkop) {
				if (*(pisuak + i * pkop + j) != 0) konexioa = 1;

				if (konexioa == 1) {
					ptrAux2 = *burua;

					while (ptrAux2->id != i && ptrAux2->ptrHurrengoa != NULL && ptrAux->visitado == 0)
						ptrAux2 = ptrAux2->ptrHurrengoa;
					/*if (ptrAux->pos.x != ptrAux2->pos.x && ptrAux->pos.y != ptrAux2->pos.y) erregulatu(ptrAux, ptrAux2);
					else*/ zuzenaMarraztu(ptrAux->pos.x, ptrAux->pos.y, ptrAux2->pos.x, ptrAux2->pos.y);
				}
				i++;
			}
			ptrAux->visitado = 1;
			j++;
		}
		kont3++;
		
		printf("%c\n", *str);
		zirkuluaMarraztu(ptrAux->pos.x, ptrAux->pos.y, 5);
	
		ptrAux = *burua;
		ptrAux2 = *burua;

		for (kont2 = 0; kont2 < kont; kont2++) ptrAux = ptrAux->ptrHurrengoa;
		if (ptrAux != NULL) {
		
		*(str) = enteroACaracter(ptrAux);
		textuaIdatzi(ptrAux->pos.x+5, ptrAux->pos.y+5 , &str);
		}
	}
}

void erregulatu(ptrPuntua ptrAux, ptrPuntua ptrAux2) {

	int egoera = -1;

	if (fabs((Uint64)ptrAux->pos.x - (Uint64)ptrAux2->pos.x) >= fabs((Uint64)ptrAux->pos.y - (Uint64)ptrAux2->pos.y)) egoera = 0;
	else egoera = 1;

	if (egoera == 0) {

		zuzenaMarraztu(ptrAux->pos.x, ptrAux->pos.y, ptrAux->pos.x, ptrAux2->pos.y);
		zuzenaMarraztu(ptrAux->pos.x, ptrAux2->pos.y, ptrAux2->pos.x, ptrAux2->pos.y);
	}
	if (egoera == 1) {

		zuzenaMarraztu(ptrAux->pos.x, ptrAux->pos.y, ptrAux2->pos.x, ptrAux->pos.y);
		zuzenaMarraztu(ptrAux2->pos.x, ptrAux->pos.y, ptrAux2->pos.x, ptrAux2->pos.y);
	}
}


char enteroACaracter(ptrPuntua ptrAux) {
	return (ptrAux->id + 48);
}