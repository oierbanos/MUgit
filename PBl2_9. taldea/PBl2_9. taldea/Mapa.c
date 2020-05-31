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

void MapaMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak, ptrMugi* burua2)
{
	ptrPuntua ptrAux;
	SDL_Window* window;
	SDL_Event ebentu;
	int jarraitu = 0, running = 0, aurkitu, jokalaria=0, kont=0, id1=0, id2=0;
	puntuakJaso(burua, fitxategia);
	pisuakJaso(*burua, fitxategia, &pisuak);

	if (!hasieratu(&window, &renderer, 600, 600, "Mapa") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		textuaGaitu(1);
		SDL_RenderClear(renderer);
		grafoaMarraztu(fitxategia, burua, pisuak);
		rewind(fitxategia);
		
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
						if (aurkitu != 1) ptrAux = ptrAux->ptrHurrengoa;
					}

				if (aurkitu == 1 && kont == 0) { 
					id1 = ptrAux->id; 
					jokalaria = JOKOA_jokalariaIrudiaSortu(*burua);
				}
				if (aurkitu == 1 && kont == 1) {
					id2 = ptrAux->id;
					setUp(fitxategia, burua, burua2, &pisuak, id1, id2);
					kalkulatu(burua, burua2, fitxategia, pisuak, jokalaria);
					free(pisuak);
				}
				kont++;
				if (aurkitu == 1 && kont == 2) kont = 0;
				break;
			default:
				break;
			}
		}
	//irudiaKendu(jokalaria);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
}

void grafoaMarraztu(FILE* fitxategia, ptrPuntua* burua, int* pisuak) {

	int pkop, i, j=0, konexioa = 0, kont, kont2, kont3 = 0;
	char str[2] = { '0', '\0' };

	ptrPuntua ptrAux = *burua, ptrAux2 = *burua;
	pkop = puntuakZenbatu(*burua);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	while (ptrAux != NULL) {
		ptrAux->visitado = 0;
		ptrAux = ptrAux->ptrHurrengoa;
	}
	ptrAux = *burua;

	for (kont = 1; kont <= pkop; kont++) {
		kont2 = 0;
		i = 0;
			while (i != pkop) {
				if (*(pisuak + j * pkop + i) != 0) konexioa = 1;

				if (konexioa == 1) {
					ptrAux2 = *burua;

					if (ptrAux != NULL && ptrAux2 != NULL && ptrAux->visitado == 0) {
						while (ptrAux2->id != j && ptrAux2->ptrHurrengoa != NULL) ptrAux2 = ptrAux2->ptrHurrengoa;
						SDL_RenderDrawLine(renderer, (int)ptrAux->pos.x, (int)ptrAux->pos.y, (int)ptrAux2->pos.x, (int)ptrAux2->pos.y);
					}
					konexioa = 0;
				}
				i++;
			}
			if (ptrAux != NULL) ptrAux->visitado = 1;
			j++;
	

		if (ptrAux != NULL) {
			zirkuluaMarraztu(ptrAux->pos.x, ptrAux->pos.y, 5);
			

			if (ptrAux != NULL) {

				*(str) = enteroACaracter(ptrAux);
				printf("ID del punto: %c\n", *str);
				textuaIdatzi((int)ptrAux->pos.x + 5, (int)ptrAux->pos.y + 5, str);
			}
			ptrAux = ptrAux->ptrHurrengoa;
		}
	}
}

void zirkuluaMarraztu(float x, float y, int r)
{
	float i, h;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (i = x - r; i <= x + r; i++) {
		h = (float)llround(sqrt((double)(r * r - (i - x) * (i - x))));
		SDL_RenderDrawLine(renderer, (int)i, (int)y + (int)h, (int)i, (int)y - (int)h);
	}
}

char enteroACaracter(ptrPuntua ptrAux) {
	return (ptrAux->id + 48);
}