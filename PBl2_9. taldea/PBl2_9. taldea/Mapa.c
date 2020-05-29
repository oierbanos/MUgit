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
#include "mugimendua.h"

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak) 
{
	ptrPuntua ptrAux;
	SDL_Window* window;
	SDL_Event ebentu;
	int jarraitu = 0, running = 0, aurkitu;

	if (!hasieratu(&window, &renderer, 600, 600, "Mapa") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		textuaGaitu(1);
		SDL_RenderClear(renderer);
		zuzenakMarraztu(fitxategia, burua, pisuak);
		
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}
	else {
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
	}
	while (running == 0)
		while (SDL_PollEvent(&ebentu) && running == IN) {
			aurkitu = 0;
			ptrAux = *burua;
			switch (ebentu.type)
			{
			case SDL_QUIT:
				running = 1;
				break;
			case SDL_KEYDOWN:
				if (ebentu.key.keysym.sym == SDLK_ESCAPE) running = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (ebentu.button.button == SDL_BUTTON_LEFT)
					while (ptrAux != NULL && aurkitu == 0) {
						aurkitu = checkArea(ptrAux->pos.x - 5, ptrAux->pos.y - 5, 10, 10, ebentu);
						if (aurkitu == 1) printf("Aurkitu da %d puntua.\n", ptrAux->id);
						ptrAux = ptrAux->ptrHurrengoa;
					}
				break;
			default:
				break;
			}
		}

	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
}

void zuzenakMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak) {

	int pkop, i, j, konexioa = 0, kont, kont2, kont3 = 0;
	char str[2] = { '0', '\0' };

	puntuakJaso(burua, fitxategia);
	pisuakJaso(*burua, fitxategia, &pisuak);
	ptrPuntua ptrAux = *burua;
	ptrPuntua ptrAux2 = *burua;
	pkop = puntuakZenbatu(*burua);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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
					SDL_RenderDrawLine(renderer, ptrAux->pos.x, ptrAux->pos.y, ptrAux2->pos.x, ptrAux2->pos.y);
					konexioa = 0;
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
			textuaIdatzi(ptrAux->pos.x + 5, ptrAux->pos.y + 5, str);
		}
	}
}

void zirkuluaMarraztu(int x, int y, int r)
{
	int i, h;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (i = x - r; i <= x + r; i++) {
		h = (int)llround(sqrt((double)(r * r - (i - x) * (i - x))));
		SDL_RenderDrawLine(renderer, i, y + h, i, y - h);
	}
}

char enteroACaracter(ptrPuntua ptrAux) {
	return (ptrAux->id + 48);
}