#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define WIDTH 500
#define HEIGHT 500

int hasieratu(SDL_Window** window, SDL_Renderer** renderer);

// Funtzio orokorra
int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	int running = 0;

	if (!hasieratu(&window, &renderer)) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// SDL_Delay(20000); Utilizarlo como el sleep

		// Loop infinito para mantener la pantalla
		while (running == 0)
		{
			// Mirar a ver si hay un evento
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) running = 1;
			}

			// Limpiar la pantalla
			SDL_RenderClear(renderer);

			// Dibujar algo

			// Mostrar lo que se ha dibujado
			SDL_RenderPresent(renderer);
		}
	}
	// Liberar informacion y terminar
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_QUIT;
	return 0;
}

int hasieratu(SDL_Window** window, SDL_Renderer** renderer)
{
	// Iniciar SDL comprobando errores
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL ez da hasieratu: %s\n", SDL_GetError());
		return 1;
	}

	// Crear una ventana con SDL comprobando error
	*window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!window) {
		fprintf(stderr, "Ez da leihoa sortu.\n");
		return 1;
	}

	// Crear un renderizador (Esta sincronizado con la pantalla que aparece al usuario y con el ratio en el que se refresca)
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		fprintf(stderr, "Could not create renderer\n");
		return 1;
	}

	return 0;
}