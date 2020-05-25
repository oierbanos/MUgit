#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "SDL_ttf.h"

#define WIDTH 500
#define HEIGHT 500
#define TERMINATE -1
#define IN 0
#define OUT 1
TTF_Font* font = 0;
SDL_Renderer* renderer;

int hasieratu(SDL_Window** window, SDL_Renderer** renderer);
void textuaIdatzi(int x, int y, char* str);
int textuaPantailanIdatzi(char* title, char* input);
void textuaGaitu(int aukera);

SDL_Renderer* getRenderer(void) { return renderer; }

// Funtzio orokorra
int main(int argc, char** argv)
{
	char input[128] = "";
	SDL_Window* window;
	int running = IN;
	
	if (!hasieratu(&window, &renderer)) {
		TTF_Init();
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		textuaGaitu(1);
		SDL_StartTextInput();
		

		// Loop infinito para mantener la pantalla
		while (running == IN)
		{
			SDL_RenderClear(renderer);
			running = textuaPantailanIdatzi("Fitxategiaren Izena", input);
			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
	}
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_StopTextInput();
	SDL_Quit(); // Necesario poner esto, sino en Linux da warning
	return 0;
}

void textuaGaitu(int aukera)
{
	switch (aukera)
	{
	case 1:
		font = TTF_OpenFont("../SDL2/Fonts/Font_Types/Courier_Prime.ttf", 16);
		break;
	default:
		printf("Aukera desegokia.\n");
		break;
	}
	if (!font)
		printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
		// handle error
}

int textuaPantailanIdatzi(char* title, char* input)
{
	char str[128];
	SDL_Event ebentu;
	int running = 0;

	// Mirar a ver si hay un evento
	while (SDL_PollEvent(&ebentu) && running == IN) {
		if (ebentu.type == SDL_QUIT)
			running = TERMINATE;
		else if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN) {
			if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
				*(input + strlen(input) - 1) = '\0';
			else if (ebentu.type == SDL_TEXTINPUT)
				strcat(input, ebentu.text.text);
			else if (ebentu.key.keysym.sym == SDLK_ESCAPE || ebentu.key.keysym.sym == SDLK_RETURN) {
				if (ebentu.key.keysym.sym == SDLK_RETURN) running = OUT;
				else running = TERMINATE;
			}
		}
	}
	sprintf(str, "%s: %s", title, input);
	textuaIdatzi(10, 10, str);
	textuaIdatzi(10, 30, "Sakatu enter jarraitzeko.");

	return running;
}

void textuaIdatzi(int x, int y, char *str)
{
	SDL_Surface* textSurface;
	SDL_Texture *mTexture;
	SDL_Color textColor = { 0, 0, 0 };
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