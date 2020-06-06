#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "imagen.h"
#include "SDL_ttf.h"
#include "Dijkstra.h"
#include "Mugimendua.h"
#include "Erabilgarriak.h"
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
		case SDL_KEYDOWN: // Lehioa itxi
			if (ebentu.key.keysym.sym == SDLK_ESCAPE) running = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ebentu.button.button == SDL_BUTTON_LEFT)
				while (ptrAux != NULL && aurkitu == 0) { // Maparen zein puntuan klikatu den kalkulatu
					aurkitu = checkArea(ptrAux->pos.x - 5, ptrAux->pos.y - 5, 10, 10, ebentu);
					if (aurkitu == 0) ptrAux = ptrAux->ptrHurrengoa;
				}
			if (aurkitu == 1) {
				idDest = ptrAux->id;
				setUp(fitxategia, burua, mugiBurua, pisuak, *idOrg, idDest); // dijkstra kalkulatu
				if (mugiBurua != NULL) { kalkulatuMugimendua(*burua, *mugiBurua, fitxategia, *pisuak, mugit, window); *idOrg = idDest; } // Mugimendua kalkulatu
				if (mugiBurua != NULL) askatuMugitu(mugiBurua); // Bariableak askatu
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

	while (p1 != NULL && p2 != NULL) {
		bilatu(pBurua, &org.x, &org.y, p1->moveId); // Hasierako puntua aurkitu
		bilatu(pBurua, &dest.x, &dest.y, p2->moveId); // Amaierako puntua aurkitu

		difX = dest.x - org.x; // Hasierako eta amaierako puntuen arteko distantzia 'x' ardatzean
		difY = dest.y - org.y; // Hasierako eta amaierako puntuen arteko distantzia 'y' ardatzean
		propX = difX / 100; // Aurrera egiteko proportzioa 'x' ardatzean
		propY = difY / 100; // Aurrera egiteko proportzioa 'y' ardatzean

		// Robota mugitu
		mugitu(propX, propY, org, dest, mugit, window, &pBurua, fitxategia, pisuak);

		p1 = p1->ptrHurrengoa;
		p2 = p1->ptrHurrengoa;
	}
}

void mugitu(float propX, float propY, POS org, POS dest, int mugit, SDL_Window* window, ptrPuntua* pBurua, FILE* fitxategia, float* pisuak)
{
	while (org.x <= dest.x - 0.5 || org.x >= dest.x + 0.5 || org.y <= dest.y - 0.5 || org.y >= dest.y + 0.5) {
		if (org.x <= dest.x - 0.5 || org.x >= dest.x + 0.5) org.x += propX;
		if (org.y <= dest.y - 0.5 || org.y >= dest.y + 0.5) org.y += propY;

		marraztu(mugit, org.x, org.y, pBurua, pisuak, window); // Mapa marraztu
	}// Desbideraketa badago, amaierako puntura mugitu
	if (org.x != dest.x || org.y != dest.y) marraztu(mugit, dest.x, dest.y, pBurua, pisuak, window);
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

void marraztu(int mugit, float x, float y, ptrPuntua* pBurua, float* pisuak, SDL_Window* window)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	irudiaMugitu(mugit, x, y); // Irudia posizio berrira mugitu
	SDL_RenderClear(renderer);
	irudiakMarraztu(); // Irudiak pantailan jarri
	grafoaMarraztu(pBurua, pisuak); // Grafoa berriz marraztu
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}