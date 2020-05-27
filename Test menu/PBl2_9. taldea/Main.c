#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"
#include "SDL.h"
#include "SDL_ttf.h"

#define WIDTH 1109
#define HEIGHT 680

// Funtzio orokorra
int main(int argc, char** argv)
{
	DIM mapDim = { mapDim.height = 0, mapDim.width = 0 };
	char fileName[128] = "", mapName[128] = "";
	int running = 0, egoera;
	SDL_Window* window;
	SDL_Event ebentu;

	if (!hasieratu(&window, &renderer, WIDTH, HEIGHT, "MUgit") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		textuaGaitu(1);

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