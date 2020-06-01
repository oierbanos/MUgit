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

int movement(ptrPuntua* burua, ptrPuntua ptrAux, ptrMugi* mugiBurua,FILE* fitxategia, float** pisuak, int mugit, int* idOrg, SDL_Window* window)
{
	SDL_Event ebentu;
	int running = 0, aurkitu, idDest;

	while (SDL_PollEvent(&ebentu) && running == IN) {
		aurkitu = 0;
		ptrAux = *burua;
		switch (ebentu.type)
		{
		case SDL_KEYDOWN:
			if (ebentu.key.keysym.sym == SDLK_ESCAPE) running = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ebentu.button.button == SDL_BUTTON_LEFT)
				while (ptrAux != NULL && aurkitu == 0) {
					aurkitu = checkArea(ptrAux->pos.x - 5, ptrAux->pos.y - 5, 10, 10, ebentu);
					if (aurkitu == 0) ptrAux = ptrAux->ptrHurrengoa;
				}

			if (aurkitu == 1) {
				idDest = ptrAux->id;
				setUp(fitxategia, burua, mugiBurua, pisuak, *idOrg, idDest);
				if (mugiBurua != NULL) { kalkulatuMugimendua(*burua, *mugiBurua, fitxategia, *pisuak, mugit, window); *idOrg = idDest; }
				if (mugiBurua != NULL) askatuMugitu(mugiBurua);
			}
			break;
		default:
			break;
		}
	}

	return running;
}

void kalkulatuMugimendua(ptrPuntua pBurua, ptrMugi mBurua, FILE* fitxategia, float* pisuak, int mugit, SDL_Window* window) 
{
	POS org, dest;
	ptrMugi p1 = mBurua, p2 = p1->ptrHurrengoa;
	float difX = 0, difY = 0, propX = 0, propY = 0;
	int pkop = puntuakZenbatu(pBurua);

	while (p1 != NULL && p2 != NULL) {
		bilatu(pBurua, &org.x, &org.y, p1->moveId);
		bilatu(pBurua, &dest.x, &dest.y, p2->moveId);

		difX = dest.x - org.x; // Distancia entre un punto y otro en x
		difY = dest.y - org.y; // Distancia entre un punto y otro en y
		propX = difX / 100; // Proporción del avance en x
		propY = difY / 100; // Proporción del avance en y

		mugitu(propX, propY, org, dest, mugit, window);

		p1 = p1->ptrHurrengoa;
		p2 = p1->ptrHurrengoa;
	}
}

void mugitu(float propX, float propY, POS org, POS dest, int mugit, SDL_Window* window)
{
	while (org.x != dest.x || org.y != dest.y) {
		if (org.x != dest.x) org.x += propX;
		if (org.y != dest.y) org.y += propY;

		irudiaMugitu(mugit, org.x, org.y);
		irudiakMarraztu();
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}
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