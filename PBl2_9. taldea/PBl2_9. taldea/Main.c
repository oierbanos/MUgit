#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"
#include "SDL_ttf.h"
#include "imagen.h"
#include "bitMap.h"
#include "Mapa.h"
#include "Menu.h"

int main(int argc, char** argv)
{
	DIM mapDim = { mapDim.height = 600, mapDim.width = 600 };
	char fileName[128] = "", mapName[128] = "";
	int running = 0, egoera, menu = -1;
	FILE * fitxategia = NULL;
	ptrPuntua burua = NULL;
	ptrMugi mBurua = NULL;
	float* pisuak = NULL;
	SDL_Window* window;
	SDL_Event ebentu;

	//bitmap();
	if (!hasieratu(&window, &renderer, WIDTH, HEIGHT, "MUgit") && TTF_Init() == 0) { // Hasieratu lehioa
		atexit(TTF_Quit);
		menu = irudiaSortu(0, 0, MENU_IMAGE, window); // Menu nagusiaren irudia sortu
		textuaGaitu(1);

		while (running == 0) { // Loop nagusia
			while ((egoera = SDL_PollEvent(&ebentu)) == 1 && running == 0) { // Ebentu baten bila egon
				if (egoera == 1) running = aukeraMenu(ebentu, &fitxategia, &burua, &mBurua, &pisuak, fileName, mapName, &mapDim); // Programaren aukera desberdinak aurrera eraman
				SDL_RenderPresent(renderer); // Pantailaren elementu desberdinak marraztu/berriztu
				SDL_UpdateWindowSurface(window);
				irudiakMarraztu();
			}
		}
		irudiaKendu(menu); // Menuaren irudia kendu
	}
	closeFont();
	free(pisuak); // Elementu desberdinak memoriatik ezabatu
	askatuMugitu(&mBurua);
	askatuPuntuak(&burua);
	if (fitxategia != NULL) fclose(fitxategia); // Fitxategia irekita badago, hau itxi
	if (renderer) SDL_DestroyRenderer(renderer); // Render-a kendu
	if (window) SDL_DestroyWindow(window); // Lehioa kendu
	SDL_StopTextInput();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
