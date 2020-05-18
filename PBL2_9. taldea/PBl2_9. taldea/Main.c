#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define WIDTH 500
#define HEIGHT 500

// Funtzio orokorra
int main(int argc, char** argv)
{
	SDL_Event event;
	int running = 0;

	// Iniciar SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Crear una ventana con SDL
	SDL_Window* window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	// Crear un renderizador (Esta sincronizado con la pantalla que aparece al usuario y con el ratio en el que se refresca)
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

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
		SDL_RenderClear(render);
		// Dibujar algo

		// Mostrar lo que se ha dibujado
		SDL_RenderPresent(render);
	}

	// Liberar informacion y terminar
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_QUIT;

	return 0;
}