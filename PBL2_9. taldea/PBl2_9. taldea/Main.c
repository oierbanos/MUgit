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
		textuaGaitu(1);

		while (running == 0) { // Loop infinito para mantener la pantalla
			while ((egoera = SDL_PollEvent(&ebentu)) == 1 && running == 0) {
				SDL_RenderClear(renderer); // Limpiar
				menu = irudiaKargatu(MENU_IMAGE);
				if (egoera == 1) running = aukeraMenu(ebentu, &fitxategia, &burua, &mBurua, &pisuak, fileName, mapName, mapDim);
				textuaIdatzi(0, 0, "Fitxategiaren Helbidea");
				textuaIdatzi(0, 20, "Irudiaren Helbidea");
				textuaIdatzi(0, 40, "Mapa berri bat sortu");
				textuaIdatzi(0, 60, "Mapa marraztu");
				SDL_RenderPresent(renderer); // Refrescar
				SDL_UpdateWindowSurface(window); // Actualizar pantalla
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