#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"
#include "Mapa.h"
#include "Menu.h"

int main(int argc, char** argv)
{
	DIM mapDim = { mapDim.height = 0, mapDim.width = 0 };
	char fileName[128] = "", mapName[128] = "";
	int running = 0, egoera;
	SDL_Window* window;
	SDL_Event ebentu;
	int* Grafo = NULL, aukera;
	FILE* fitxategia = NULL;
	ptrPuntua burua = NULL;
	ptrMugi mBurua = NULL;
	
	if (!hasieratu(&window, &renderer, WIDTH, HEIGHT, "MUgit") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		textuaGaitu(1);

		do {
			aukera = menu();
			switch (aukera)
			{
			case 0:
				break;
			case 1: // Error desde 100
				//Mapa bat sortu
				fitxategiBatSortu();
				break;
			case 2: // Error desde 200
				//Mapa bat kargatu
				fitxategiaJaso(&fitxategia);
				break;
			case 3: // Error desde 300
				//Dijkstra
				if (fitxategia == NULL) printf("301 Errorea\n");
				else setUp(fitxategia, &burua, &mBurua, &Grafo);
				break;
			case 4:
				//Mapa marraztu
				if (fitxategia == NULL) printf("301 Errorea\n");
				else MapaMarraztu(fitxategia, &burua, &Grafo);
			default:
				printf("Aukera ez da egokia.\n\n");
				break;
			}
		} while (aukera != 0);

		while (running == 0) { // Loop infinito para mantener la pantalla
			while ((egoera = SDL_PollEvent(&ebentu)) == 1 && running == 0) {
				SDL_RenderClear(renderer); // Limpiar
				if (egoera == 1) running = aukeraMenu(ebentu, fileName, mapName, mapDim);
				textuaIdatzi(0, 0, "Fitxategiaren Helbidea");
				textuaIdatzi(0, 20, "Irudiaren Helbidea");
				textuaIdatzi(0, 40, "Dijkstra aplikatu");
				SDL_RenderPresent(renderer); // Refrescar
				SDL_UpdateWindowSurface(window); // Actualizar pantalla
			}
		}
	}
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_StopTextInput();
	SDL_Quit(); // Necesario poner esto, sino en Linux da warning

	return 0;
}