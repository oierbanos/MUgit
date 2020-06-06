#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "Menu.h"
#include "Mapa.h"
#include "imagen.h"
#include "bitMap.h"
#include "SDL_ttf.h"
#include "Dijkstra.h"
#include "Mugimendua.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

TTF_Font* font = 0;

SDL_Renderer* getRenderer(void) // Render bat jaso
{
	return renderer;
}

int aukeraMenu(SDL_Event ebentu, FILE** fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, char* fileName, char* mapName, DIM* mapDim, MP* points, int* pkop)
{
	int running = 0, egoera;

	switch (ebentu.type)
	{
	case SDL_QUIT: // Lehioa 'X' botoiaren bidez itxi
		running = -1;
		break;
	case SDL_KEYDOWN: // Escape teklaren bidez lehioa itxi
		if (ebentu.key.keysym.sym == SDLK_ESCAPE) running = -1;
		break;
	case SDL_MOUSEBUTTONDOWN: // Pantailan klikatu da
		if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 351, 482, 93, ebentu)) { // Fitxategiaren eta maparen irudiaren helbideak jaso
			if (*fitxategia != NULL) fclose(*fitxategia);
			egoera = getTextFromUser(fileName, "Get File", 450, 563, FILE_IMAGE); // Fitxategiaren helbidea jaso
			if (egoera == OUT && strcmp(fileName, "") != 0) { egoera = fitxategiaIreki(fitxategia, fileName); } // Textua gorde nahi bada, fitxategia ireki
			else { strcpy(fileName, ""); fitxategia = NULL; } // Gordeko ez bada jasotako textua ezabatu

			egoera = getTextFromUser(mapName, "Get Map", 450, 563, MAP_IMAGE); // Irudiaren helbidea jaso
			if (egoera != OUT)  strcpy(mapName, ""); // Gorde nahi ez bada, barruko textua ezabatu
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 224, 482, 93, ebentu)) {
			bitmap(&points, pkop, mapDim); // Erabiltzaileak mapa bat marraztu
			if (*pkop >= 2) fitxategiBatSortu(points, *pkop, *mapDim); // Sortutako mapa puntu minimo kopurua badauka, informazioa gorde
			free(points); // Beharrezkoa ez den informazioa ezabatu
			points = NULL;
			*pkop = 0;
		}
		else if (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(67, 476, 482, 93, ebentu)) {
			if (*fitxategia != NULL) {
				MapaMarraztu(*fitxategia, burua, *pisuak, mBurua, mapName); // Biltegiaren mapa pantailan marraztu, robotaren mugimendua simulatzeko
				rewind(*fitxategia);
			}
			else printf("#401 Errorea\n");
		}
		break;
	default:
		break;
	}

	return running;
}

int getTextFromUser(char* input, char* windowName, int width, int height, char* image)
{
	int running = IN, menu = -1;
	SDL_Window* window;

	if (!hasieratu(&window, &renderer, width, height, windowName) && TTF_Init() == 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		textuaGaitu(1);

		menu = irudiaSortu(0, 0, image, window); // Fondoaren irudia ezarri
		SDL_StartTextInput();
		while (running == IN) {
			SDL_RenderClear(renderer);
			irudiakMarraztu(); // Irudia pantailan jarri
			running = textuaPantailanIdatzi(input, 50, 255); // Erabiltzaileak emandako textua pantailan idatzi
			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
		closeFont(); // Textua desgaitu
		irudiaKendu(menu);
		SDL_StopTextInput();
	}
	else { printf("#101 Errorea"); running = TERMINATE; }
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
	switch (aukera) // Textu mota desberdinak sartzeko aukera
	{
	case 1:
		font = TTF_OpenFont("Media/Fonts/Courier Prime.ttf", 16);
		break;
	case 2:
		font = TTF_OpenFont("Media/Fonts/Amiko-Regular.ttf", 16);
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

	while (SDL_PollEvent(&ebentu) && running == IN) {
		if (ebentu.type == SDL_QUIT) // Lehiioa itxi
			running = TERMINATE;
		else if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN || ebentu.type == SDL_MOUSEBUTTONDOWN) {
			if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
				*(input + strlen(input) - 1) = '\0'; // Pantailan erabiltzen den textuaren karaktere bat ezabatu
			else if (ebentu.type == SDL_TEXTINPUT && strlen(input) <= MAX_SIZE)
				strcat(input, ebentu.text.text); // Sartutako karaktere bakoitza jaso
			else if (ebentu.key.keysym.sym == SDLK_ESCAPE || ebentu.key.keysym.sym == SDLK_RETURN || ebentu.type == SDL_MOUSEBUTTONDOWN) { // Textua jaso eta gorde
				if (ebentu.key.keysym.sym == SDLK_RETURN || (ebentu.button.button == SDL_BUTTON_LEFT && checkArea(84, 365, 283, 41, ebentu))) running = OUT;
				else if (ebentu.type != SDL_MOUSEBUTTONDOWN) running = TERMINATE; // Escape sakatu bada textua ez da gordetzen
			}
		}
	}
	sprintf(str, "%s_", input); // Pantailaratuko den textua string batean sartu
	textuaIdatzi(x, y, str); // Textua pantailaratu

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