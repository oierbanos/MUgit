#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "Mugimendua.h"
#include "SDL_ttf.h"
#include "imagen.h"
#include "Erabilgarriak.h"
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

TTF_Font* font = 0;

SDL_Renderer* getRenderer(void)
{
	return renderer;
}

int getTextFromUser(char* input, char* windowName, int width, int height, char* image)
{
	SDL_Window* window;
	int running = IN, menu = -1;

	if (!hasieratu(&window, &renderer, width, height, windowName) && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		textuaGaitu(1);

		menu = irudiaSortu(0, 0, image, window);
		SDL_StartTextInput();
		while (running == IN) {
			SDL_RenderClear(renderer);
			irudiakMarraztu();
			running = textuaPantailanIdatzi(input, 50, 255);
			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
		irudiaKendu(menu);
		SDL_StopTextInput();
	}
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);

	return running;
}

int hasieratu(SDL_Window** window, SDL_Renderer** renderer, int width, int height, char* name)
{
	// Iniciar SDL comprobando errores
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL ez da hasieratu: %s\n", SDL_GetError());
		return 1;
	}

	// Crear una ventana con SDL comprobando error
	*window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
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

void textuaGaitu(int aukera)
{
	switch (aukera) // Posibilidad de meter distintos tipos de fuente
	{
	case 1:
		font = TTF_OpenFont("../Media/Fonts/Courier Prime.ttf", 16);
		break;
	case 2:
		font = TTF_OpenFont("../Media/Fonts/Amiko-Regular.ttf", 16);
		break;
	default:
		printf("Aukera desegokia.\n");
		break;
	}
	if (!font)
		printf("TTF_OpenFontIndex: %s\n", TTF_GetError()); // handle error
}

int textuaPantailanIdatzi(char* input, int x, int y)
{
	char str[MAX_SIZE];
	SDL_Event ebentu;
	int running = 0;

	// Mirar a ver si hay un evento
	while (SDL_PollEvent(&ebentu) && running == IN) {
		if (ebentu.type == SDL_QUIT)
			running = TERMINATE;
		else if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN || ebentu.type == SDL_MOUSEBUTTONDOWN) {
			if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
				*(input + strlen(input) - 1) = '\0';
			else if (ebentu.type == SDL_TEXTINPUT && strlen(input) <= MAX_SIZE)
				strcat(input, ebentu.text.text);
			else if (ebentu.key.keysym.sym == SDLK_ESCAPE || ebentu.key.keysym.sym == SDLK_RETURN || ebentu.type == SDL_MOUSEBUTTONDOWN) {
				if (ebentu.key.keysym.sym == SDLK_RETURN || ebentu.button.button == SDL_BUTTON_LEFT && checkArea(84, 365, 283, 41, ebentu)) running = OUT;
				else if (ebentu.type != SDL_MOUSEBUTTONDOWN) running = TERMINATE;
			}
		}
	}
	sprintf(str, " %s", input);
	textuaIdatzi(x, y, str);

	return running;
}

void textuaIdatzi(int x, int y, char* str)
{
	SDL_Surface* textSurface;
	SDL_Texture* mTexture;
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

int aukeraMenu(SDL_Event ebentu, FILE** fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, char* fileName, char* mapName, DIM mapDim)
{
	int running = 0, egoera, jokalaria=0;

	switch (ebentu.type)
	{
	case SDL_QUIT:
		running = -1;
		break;
	case SDL_KEYDOWN:
		if (ebentu.key.keysym.sym == SDLK_ESCAPE) running = -1;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 351, 482, 93, ebentu)) {
			egoera = getTextFromUser(fileName, "Get File", 450, 563, FILE_IMAGE);
			if (egoera == OUT) { egoera = fitxategiaIreki(fitxategia, fileName); }
			else { strcpy(fileName, ""); fitxategia = NULL; }

			egoera = getTextFromUser(mapName, "Get Map", 450, 563, MAP_IMAGE);
			if (egoera != OUT) strcpy(mapName, "");
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 224, 482, 93, ebentu)) {
			fitxategiBatSortu();
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 476, 482, 93, ebentu)) {
			if (*fitxategia != NULL) {
				MapaMarraztu(*fitxategia, burua, *pisuak, mBurua);
				rewind(*fitxategia);
			}
			else printf("Fitxategia ezin da ireki.\n");
		}
		break;
	default:
		break;
	}

	return running;
}

int checkArea(float x, float y, float xDistance, float yDistance, SDL_Event ebentu)
{
	int egoera = 0;

	if (ebentu.button.x >= x && ebentu.button.x <= x + xDistance && ebentu.button.y >= y && ebentu.button.y <= y + yDistance)
		egoera = 1;

	return egoera;
}

void closeFont(void)
{
	if (font != 0) TTF_CloseFont(font);
}