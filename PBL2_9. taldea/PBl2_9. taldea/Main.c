#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "SDL_ttf.h"

#define WIDTH 500
#define HEIGHT 500
TTF_Font* font = 0;
SDL_Renderer* gRenderer;
SDL_Renderer* getRenderer(void) { return gRenderer; }

int hasieratu(SDL_Window** window, SDL_Renderer** renderer);
void textuaIdatzi(int x, int y, char* str);

// Funtzio orokorra
int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event ebentu;
	int running = 0;
	char str[128] = "", title[128] = "Textua Sartu: ";

	SDL_StartTextInput();
	if (!hasieratu(&window, &renderer)) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// Loop infinito para mantener la pantalla
		while (running == 0)
		{
			// Mirar a ver si hay un evento
			while (SDL_PollEvent(&ebentu)) {
				if (ebentu.type == SDL_QUIT)
					running = 1;
				else if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN) {
					if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(str) > 0)
						*(str + strlen(str) - 1) = '\0';
					else if (ebentu.type == SDL_TEXTINPUT)
						strcat(str, ebentu.text.text);
				}
			}

			// Limpiar la pantalla
			SDL_RenderClear(renderer);

			// Dibujar algo
			sprintf(title, "Textua Sartu: %s", str);
			textuaIdatzi(10, 10, title);

			// Mostrar lo que se ha dibujado
			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
	}
	// Liberar informacion y terminar
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_StopTextInput();
	//SDL_QUIT; Para que no de warning (en linux) hay que poner SDL_Quit()
	SDL_Quit();
	return 0;
}

void textuaIdatzi(int x, int y, char *str)
{
	SDL_Surface* textSurface;
	SDL_Texture *mTexture;
	SDL_Color textColor = { 0XFF, 0XFF, 0XFF };
	SDL_Rect src, dst;
	SDL_Renderer* gRenderer;

	if (font == 0) return;
	gRenderer = getRenderer();
	textSurface = TTF_RenderText_Solid(font, str, textColor);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	src.x = 0; dst.x = x;
	src.y = 0; dst.y = y;
	src.w = dst.w = textSurface->w;
	src.h = dst.h = textSurface->h;
	SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);
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