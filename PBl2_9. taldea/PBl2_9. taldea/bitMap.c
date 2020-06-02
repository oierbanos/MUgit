#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "Fitxategia_Irakurri.h"
#include "Mapa.h"
#include "Menu.h"
#include "Erabilgarriak.h"
#include "bitMap.h"
#include "SDL_ttf.h"
#include "imagen.h"

void bitmap(void) 
{
	DIM mapDim;
	SDL_Event ebentu;
	CONECT* konexioak;
	SDL_Window* window;
	POS* points = NULL, org = { org.x = -1 }, dest;
	int running = 0, kont = 0, conectKont = 0, check = -1, tmp;

	mapDim = eskatuDimentzioak();
	if (!hasieratu(&window, &renderer, mapDim.width, mapDim.height, "Create map") && TTF_Init() == 0) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);

		while (running == 0) {
			while (SDL_PollEvent(&ebentu)) {
				if (ebentu.type == SDL_QUIT) running = 1;
				else if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_ESCAPE) running = 1;
				else if (ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_LEFT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					zirkuluaMarraztu((float)(ebentu.button.x), (float)(ebentu.button.y), 5);
					koordenatuakGorde(&points, &kont, (float)(ebentu.button.x), (float)(ebentu.button.y));
					SDL_RenderPresent(renderer);
					SDL_UpdateWindowSurface(window);
				}
				else if ((ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_RIGHT) && points != NULL) {
					check = checkPlace(points, kont, ebentu);
					if (check != -1 && org.x == -1) {
						org = *(points + check);
						tmp = check;
					}
					else if (check != -1 && org.x != -1) { 
						dest = *(points + check);
						konexioBerria(org, dest, &konexioak, &kont);
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
						SDL_RenderDrawLine(renderer, org.x, org.y, dest.x, dest.y);
						SDL_RenderPresent(renderer);
						SDL_UpdateWindowSurface(window);
						org.x = -1;
					}
					check = -1;
				}
			}
		}
		for (int i = 0; i < kont; i++) printf("Koordenatuak: %.2f, %.2f\n", (points + i)->x, (points + i)->y);
		free(points);
	}
}

void koordenatuakGorde(POS** points, int* kont, float mouseX, float mouseY)
{
	if (*points == NULL) *points = (POS*)malloc(sizeof(POS));
	else *points = (POS*)realloc(*points, sizeof(POS) * (*kont + 1));

	if (*points != NULL) {
		(*points + *kont)->x = mouseX;
		(*points + *kont)->y = mouseY;
		(*kont)++;
	}
	else printf("Error\n");
}

int checkPlace(POS* points, int kont, SDL_Event ebentu)
{
	int check = 0, i = 0;

	while (i < kont && check == 0) {
		check = checkArea((points + i)->x - 5, (points + i)->y - 5, 10, 10, ebentu);
		i++;
	}
	if (check == 1) return i - 1;
	else return -1;
}

DIM eskatuDimentzioak(void)
{
	char str[MAX_SIZE];
	DIM dim;

	printf("Maparen zabalera: ");
	fgets(str, MAX_SIZE, stdin);
	sscanf(str, "%d", &dim.width);

	printf("Maparen luzeera: ");
	fgets(str, MAX_SIZE, stdin);
	sscanf(str, "%d", &dim.height);

	return dim;
}

void konexioBerria(POS org, POS dest, CONECT** konexioak, int* kont)
{

}