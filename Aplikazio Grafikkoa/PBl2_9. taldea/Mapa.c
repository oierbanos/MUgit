#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "Mapa.h"
#include "Menu.h"
#include "math.h"
#include "imagen.h"
#include "SDL_ttf.h"
#include "Dijkstra.h"
#include "Mugimendua.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, float* pisuak, ptrMugi* mugiBurua, char* mapName)
{
	int running = 0, mugit = -1, idOrg, mapbackground = -1, egoera;
	DIM mapDim = { mapDim.width = -1, mapDim.height = -1 };
	SDL_Window* window;
	ptrPuntua ptrAux;

	egoera = dimentsioakJaso(fitxategia, &mapDim); // Maparen dimentsioak jaso
	if (egoera == 1) egoera = puntuakJaso(burua, fitxategia); // Maparen puntu desberdinak jaso
	if (egoera == 1) egoera = pisuakJaso(*burua, fitxategia, &pisuak); // Mapan konektatuta 

	if (egoera == 1 && mapDim.height > 0 && mapDim.width > 0 && !hasieratu(&window, &renderer, mapDim.width, mapDim.height, "Mapa") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		textuaGaitu(1);
		SDL_RenderClear(renderer);
		if (strcmp(mapName, "") != 0) 
			mapbackground = irudiaSortu(0, 0, mapName, window); // Maparen atzekaldeea sortu (erabiltzaileak hala aukeratu badu)

		ptrAux = *burua;
		idOrg = ptrAux->id;
		SDL_RenderPresent(renderer); // Robotaren irudia sortu
		mugit = irudiaSortu(ptrAux->pos.x, ptrAux->pos.y, MUGIT_IMAGE, window);

		grafoaMarraztu(burua, pisuak); // Robota mugituko den puntuak eta haien konexioak pantailan marraztu
		rewind(fitxategia);

		while (running == 0) // Robota pantailan zehar mugitzeko aukera
			running = movement(burua, ptrAux, mugiBurua, fitxategia, &pisuak, mugit, &idOrg, window);

		irudiaKendu(mugit); // Irudiak kendu
		irudiaKendu(mapbackground);
		if (renderer) SDL_DestroyRenderer(renderer);
		if (window) SDL_DestroyWindow(window);
	}
	else printf("#101 Errorea");
}

void grafoaMarraztu(ptrPuntua* burua, float* pisuak)
{
	char str[12];
	int pkop, i, j=0, konexioa = 0, kont;
	ptrPuntua ptrAux = *burua, ptrAux2 = *burua;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	pkop = puntuakZenbatu(*burua); // Puntu kopurua jaso

	while (ptrAux2 != NULL) { // ptrAux2 hasieratu
		ptrAux2->visitado = 0;
		ptrAux2 = ptrAux2->ptrHurrengoa;
	}
	ptrAux2 = *burua;

	for (kont = 1; kont <= pkop; kont++) {
		i = 0;
			while (i != pkop) {
				if (*(pisuak + j * pkop + i) != 0) konexioa = 1;

				if (konexioa == 1) {
					ptrAux = *burua;

					if (ptrAux != NULL && ptrAux2 != NULL) { // Puntuen arteko konexioak irudikatzen duten zuzenak 
						while (ptrAux->id != i + 1 && ptrAux->ptrHurrengoa != NULL) ptrAux = ptrAux->ptrHurrengoa;
						if (ptrAux2->visitado == 0) // Konexioa irudikatuta ez badago irudikatu
							SDL_RenderDrawLine(renderer, (int)ptrAux->pos.x, (int)ptrAux->pos.y, (int)ptrAux2->pos.x, (int)ptrAux2->pos.y);
					}
					konexioa = 0;
				}
				i++;
			}
			if (ptrAux2 != NULL) ptrAux2->visitado = 1;
			j++;
	
		if (ptrAux2 != NULL) { // Puntu desberdinak marraztu
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			zirkuluaMarraztu(ptrAux2->pos.x, ptrAux2->pos.y, 5);

			if (ptrAux2 != NULL) { // Puntuen id-ak pantailan jarri
				sprintf(str, "%d", ptrAux2->id);
				textuaIdatzi((int)ptrAux2->pos.x + 5, (int)ptrAux2->pos.y + 5, str);
			}
			ptrAux2 = ptrAux2->ptrHurrengoa;
		}
	}
	SDL_RenderPresent(renderer);
}

void zirkuluaMarraztu(float x, float y, int r)
{
	float i, h;

	for (i = x - r; i <= x + r; i++) { // Zirkulua marraztu
		h = (float)llround(sqrt((double)(r * r - (i - x) * (i - x))));
		SDL_RenderDrawLine(renderer, (int)i, (int)y + (int)h, (int)i, (int)y - (int)h);
	}
}
