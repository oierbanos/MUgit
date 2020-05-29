#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "Mugimendua.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

TTF_Font* font = 0;

SDL_Renderer* getRenderer(void)
{
	return renderer;
}

int getTextFromUser(char* input, char* title, char* windowName)
{
	SDL_Window* window;
	int running = IN;

	if (!hasieratu(&window, &renderer, 500, 36, windowName) && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		textuaGaitu(1);

		SDL_StartTextInput();
		while (running == IN) { // Loop infinito para mantener la pantalla
			SDL_RenderClear(renderer); // Limpiar
			running = textuaPantailanIdatzi(title, input, 10, 0);
			textuaIdatzi(10, 20, "Sakatu enter helbidea gordetzeko.");
			SDL_RenderPresent(renderer); // Refrescar
			SDL_UpdateWindowSurface(window); // Actualizar pantalla
		}
	}
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_StopTextInput();

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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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

int textuaPantailanIdatzi(char* title, char* input, int x, int y)
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
	textuaIdatzi(x, y, str);

	return running;
}

void textuaIdatzi(int x, int y, char* str)
{
	SDL_Surface* textSurface;
	SDL_Texture* mTexture;
	SDL_Color textColor = { 255, 255, 255 };
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

int aukeraMenu(SDL_Event ebentu, FILE** fitxategia, ptrPuntua* burua, ptrMugi* mBurua, int** Grafo, char* fileName, char* mapName, DIM mapDim)
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
		if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 0, 230, 20, ebentu)) {
			egoera = getTextFromUser(fileName, "Fitxategiaren Helbidea", "Get File");
			if (egoera == OUT) egoera = fitxategiaIreki(fitxategia, fileName);
			if (egoera != OUT) { strcpy(fileName, ""); fitxategia = NULL; }
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 20, 230, 20, ebentu)) {
			egoera = getTextFromUser(mapName, "Irudiaren Helbidea", "Get Map");
			if (egoera == OUT) printf("Helbidea: %s\n", mapName);
			else strcpy(mapName, "");
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 40, 230, 20, ebentu)) {
			fitxategiBatSortu();
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 60, 230, 20, ebentu)) {
			if (*fitxategia != NULL) setUp(*fitxategia, burua, mBurua, Grafo);
			else printf("Fitxategia ezin da ireki.\n");
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 80, 230, 20, ebentu)) {
			if (*fitxategia != NULL) {
				MapaMarraztu(*fitxategia, burua, *Grafo);
				rewind(*fitxategia);
			}
			else printf("Fitxategia ezin da ireki.\n");
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(0, 100, 230, 20, ebentu)) {
			jokalaria = JOKOA_jokalariaIrudiaSortu(burua);
			if (*fitxategia != NULL) kalkulatu(burua, mBurua, fitxategia, Grafo, jokalaria);
			else printf("Fitxategia ezin da ireki.\n");
		}
		break;
	default:
		break;
	}

	return running;
}

int checkArea(int x, int y, int xDistance, int yDistance, SDL_Event ebentu)
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