#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"
#include "imagen.h"
#include "Mapa.h"
#include "Menu.h"
#include "SDL_ttf.h"

int main(int argc, char** argv)
{
	DIM mapDim = { mapDim.height = 0, mapDim.width = 0 };
	char fileName[128] = "", mapName[128] = "";
	int running = 0, egoera, menu = -1;
	SDL_Window* window;
	SDL_Event ebentu;
	float* pisuak = NULL;
	FILE* fitxategia = NULL;
	ptrPuntua burua = NULL;
	ptrMugi mBurua = NULL;

	if (!hasieratu(&window, &renderer, WIDTH, HEIGHT, "MUgit") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		menu = irudiaSortu(0, 0, MENU_IMAGE, window);
		textuaGaitu(1);

		while (running == 0) { // Loop infinito para mantener la pantalla
			while ((egoera = SDL_PollEvent(&ebentu)) == 1 && running == 0) {
				if (egoera == 1) running = aukeraMenu(ebentu, &fitxategia, &burua, &mBurua, &pisuak, fileName, mapName, mapDim);
				SDL_RenderPresent(renderer);
				SDL_UpdateWindowSurface(window);
				irudiakMarraztu();
			}
		}
		irudiaKendu(menu);
	}
	closeFont();
	if (fitxategia != NULL) fclose(fitxategia);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_StopTextInput();
	SDL_Quit(); // Necesario poner esto, sino en Linux da warning

	return 0;
}