#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "Fitxategia_Irakurri.h"
#include "Mapa.h"
#include "Menu.h"
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "math.h"
#include "SDL_ttf.h"
#include "imagen.h"
#include "Mugimendua.h"

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, float* pisuak, ptrMugi* mugiBurua, char* mapName)
{
	int running = 0, mugit = -1, idOrg, mapbackground = -1;
	DIM mapDim = { mapDim.width = -1, mapDim.height = -1 };
	SDL_Window* window;
	ptrPuntua ptrAux;

	dimentsioakJaso(fitxategia, &mapDim);
	puntuakJaso(burua, fitxategia);
	pisuakJaso(*burua, fitxategia, &pisuak);

	if (mapDim.height > 0 && mapDim.width > 0 && !hasieratu(&window, &renderer, mapDim.width, mapDim.height, "Mapa") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		textuaGaitu(1);
		SDL_RenderClear(renderer);
		if (strcmp(mapName, "") != 0) mapbackground = irudiaSortu(0, 0, mapName, window);

		ptrAux = *burua;
		idOrg = ptrAux->id;
		SDL_RenderPresent(renderer);
		mugit = irudiaSortu(ptrAux->pos.x, ptrAux->pos.y, MUGIT_IMAGE, window);

		grafoaMarraztu(burua, pisuak);
		rewind(fitxategia);
		
		while (running == 0) running = movement(burua, ptrAux, mugiBurua, fitxategia, &pisuak, mugit, &idOrg, window);

		irudiaKendu(mugit);
		irudiaKendu(mapbackground);
		if (renderer) SDL_DestroyRenderer(renderer);
		if (window) SDL_DestroyWindow(window);
	}
	else fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
}

void grafoaMarraztu(ptrPuntua* burua, float* pisuak)
{
	char str[12];
	int pkop, i, j=0, konexioa = 0, kont;
	ptrPuntua ptrAux = *burua, ptrAux2 = *burua;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	pkop = puntuakZenbatu(*burua);

	while (ptrAux2 != NULL) {
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

					if (ptrAux != NULL && ptrAux2 != NULL) {
						while (ptrAux->id != i + 1 && ptrAux->ptrHurrengoa != NULL) ptrAux = ptrAux->ptrHurrengoa;
						if (ptrAux2->visitado == 0) {
							SDL_RenderDrawLine(renderer, (int)ptrAux->pos.x, (int)ptrAux->pos.y, (int)ptrAux2->pos.x, (int)ptrAux2->pos.y);
						}
					}
					konexioa = 0;
				}
				i++;
			}
			if (ptrAux2 != NULL) ptrAux2->visitado = 1;
			j++;
	
		if (ptrAux2 != NULL) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			zirkuluaMarraztu(ptrAux2->pos.x, ptrAux2->pos.y, 5);

			if (ptrAux2 != NULL) {
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

	for (i = x - r; i <= x + r; i++) {
		h = (float)llround(sqrt((double)(r * r - (i - x) * (i - x))));
		SDL_RenderDrawLine(renderer, (int)i, (int)y + (int)h, (int)i, (int)y - (int)h);
	}
}
