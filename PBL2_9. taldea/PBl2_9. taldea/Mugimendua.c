#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "imagen.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

#define JOKOA_PLAYER_IMAGE "../Media/mugit.bmp"

int* kalkulatu(ptrMugi burua, ptrPuntua* burua2, FILE* fitxategia, int* Grafo, int jokalaria) {

	float x = 0, y = 0, z = 0, k = 0, mainx=0, mainy=0, mx=0, my=0;

	SDL_Window* window;
	SDL_Event ebentu;
	int jarraitu = 0, running = 0, aurkitu;
	ptrMugi p1 = burua, p2 = p1->ptrHurrengoa;
	ptrPuntua ptrAux;

	while (p1 != NULL) {

		bilatu(burua2, x, y, p1->moveId);
		bilatu(burua2, z, k, p2->moveId);

		mainx = fabs(x - z);
		mainy = fabs(y - k);

		mx = mainx / mainy;
		my = mainy / mainx;

		mugitu(mx, my, x, y, z, k, fitxategia, burua, *Grafo, jokalaria);

		p1 = p1->ptrHurrengoa;
		p2 = p1->ptrHurrengoa;
	}
	while (running == 0)
		while (SDL_PollEvent(&ebentu) && running == IN) {
			aurkitu = 0;
			ptrAux = *burua2;
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
	if (jokalaria)  irudiaKendu(jokalaria);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);

}

void mugitu(float x, float y, float z, float k, float j, float i, FILE* fitxategia, ptrPuntua* burua, int* Grafo, int jokalaria) {

	while (z != j && k != i) {

		z += x;
		k += y;

		SDL_RenderClear(renderer);

		irudiaMugitu(jokalaria, z, k);
		MapaMarraztu(fitxategia, burua, *Grafo);
		irudiakMarraztu();
		SDL_RenderPresent(renderer);

	}

}

int JOKOA_jokalariaIrudiaSortu(ptrPuntua ptrAux)
{
	int mugit = -1;
	mugit = irudiaKargatu(JOKOA_PLAYER_IMAGE);
	irudiaMugitu(mugit, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return mugit;

}
