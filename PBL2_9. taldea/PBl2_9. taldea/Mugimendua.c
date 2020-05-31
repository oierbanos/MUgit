#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "Mugimendua.h"
#include "imagen.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

#define JOKOA_PLAYER_IMAGE "../Media/mugit.bmp"

void kalkulatu(ptrPuntua* burua2, ptrMugi* burua, FILE* fitxategia, int* Grafo, int jokalaria) 
{
	float mainx = 0, mainy = 0, mx = 0, my = 0;
	POS org, dest;

	ptrMugi p1 = *burua, p2 = p1->ptrHurrengoa;	
	while (p1 != NULL && p2!=NULL) {

		bilatu(burua2, &org.x, &org.y, p1->moveId);
		bilatu(burua2, &dest.x, &dest.y, p2->moveId);

		mainx = dest.x - org.x; // Distancia entre un punto y otro en x
		mainy = dest.y - org.y; // Distancia entre un punto y otro en y

		mx = mainx / mainy; // Proporción del avance en x
		my = mainy / mainx; // Proporción del avance en y

		mugitu(mx, my, org.x, org.y, dest.x, dest.y, jokalaria, fitxategia, Grafo, burua2);

		p1 = p1->ptrHurrengoa;
		p2 = p1->ptrHurrengoa;
	}
}

void mugitu(float x, float y, float z, float k, float j, float i, int jokalaria, FILE* fitxategia, int* pisuak, ptrPuntua* burua2) {

	while (z != j && k != i) {

		z += x;
		k += y;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		irudiaMugitu(jokalaria, z, k);
		grafoaMarraztu(fitxategia, burua2, pisuak);
		irudiakMarraztu();
		SDL_RenderPresent(renderer);
	}
}

int JOKOA_jokalariaIrudiaSortu(ptrPuntua ptrAux)
{
	int mugit = -1;
	mugit = irudiaKargatu(JOKOA_PLAYER_IMAGE);
	irudiaMugitu(mugit, ptrAux->pos.x , ptrAux->pos.y);
	irudiakMarraztu();
	SDL_RenderPresent(renderer);
	return mugit;

}


int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest)
{
	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = pDest->w;
	src.h = pDest->h;
	SDL_RenderCopy(renderer, texture, &src, pDest);
	return 0;
}