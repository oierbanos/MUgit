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
	MP* points = NULL;
	SDL_Window* window;
	POS org = { org.x = -1 }, dest;
	int running = 0, pkop = 0, ckop = 0, check = -1, tmp;

	mapDim = eskatuDimentzioak();
	if (!hasieratu(&window, &renderer, mapDim.width, mapDim.height, "Create map") && TTF_Init() == 0) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		textuaGaitu(1);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		textuaIdatzi(10, 5, "Ezkerreko klick-a: puntua sortu");
		textuaIdatzi(10, 25, "Eskuineko klick-a: Bi puntu konektatu");
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);

		while (running == 0) {
			while (SDL_PollEvent(&ebentu)) {
				if (ebentu.type == SDL_QUIT) running = 1;
				else if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_ESCAPE) running = 1;
				else if (ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_LEFT) {
					zirkuluaMarraztu((float)(ebentu.button.x), (float)(ebentu.button.y), 5);
					koordenatuakGorde(&points, &pkop, (float)(ebentu.button.x), (float)(ebentu.button.y));
					SDL_RenderPresent(renderer);
					SDL_UpdateWindowSurface(window);
				}
				else if ((ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_RIGHT) && points != NULL) {
					check = checkPlace(points, pkop, ebentu);
					if (check != -1 && org.x == -1) {
						org = (points + check)->pos;
						tmp = check;
					}
					else if (check != -1 && org.x != -1) { 
						dest = (points + check)->pos;
						if (org.x != dest.x && org.y != dest.y) {
							SDL_SetRenderDrawColor(renderer, 255, 145, 50, 255);
							SDL_RenderDrawLine(renderer, org.x, org.y, dest.x, dest.y);
							SDL_RenderPresent(renderer);
							SDL_UpdateWindowSurface(window);
							konektatu(&points, tmp, check);
							org.x = -1;
						}
					}
					check = -1;
				}
			}
		}
		for (int i = 0; i < pkop; i++) {
			printf("Koordenatuak: %.2f, %.2f\n", (points + i)->pos.x, (points + i)->pos.y);
			int j = 0;
			while ((points + i)->konexioak[j] != -1) { printf("Konexioa: %d\n", (points + i)->konexioak[j]); j++; }
		}
		free(points);
	}
}

void koordenatuakGorde(MP** points, int* kont, float mouseX, float mouseY)
{
	if (*points == NULL) *points = (MP*)malloc(sizeof(MP));
	else *points = (MP*)realloc(*points, sizeof(MP) * (*kont + 1));

	if (*points != NULL) {
		(*points + *kont)->pos.x = mouseX;
		(*points + *kont)->pos.y = mouseY;
		(*points + *kont)->konexioak = NULL;
		(*kont)++;
	}
	else printf("Error\n");
}

int checkPlace(MP* points, int kont, SDL_Event ebentu)
{
	int check = 0, i = 0;

	while (i < kont && check == 0) {
		check = checkArea((points + i)->pos.x - 5, (points + i)->pos.y - 5, 10, 10, ebentu);
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

void konektatu(MP** points, int org, int dest)
{
	int kont = 0;

	if ((*points + org)->konexioak == NULL) {
		(*points + org)->konexioak = (int*)malloc(sizeof(int) * 2);
		if ((*points + org)->konexioak != NULL) {
			(*points + org)->konexioak[0] = dest;
			(*points + org)->konexioak[1] = -1;
		}
	}
	else {
		while ((*points + org)->konexioak[kont] != -1) kont++;
		(*points + org)->konexioak = (int*)realloc((*points + org)->konexioak, sizeof(int) * (kont + 2));
		if ((*points + org)->konexioak != NULL) {
			(*points + org)->konexioak[kont] = dest;
			(*points + org)->konexioak[kont + 1] = -1;
		}
	}

	if ((*points + dest)->konexioak == NULL) {
		(*points + dest)->konexioak = (int*)malloc(sizeof(int) * 2);
		if ((*points + dest)->konexioak != NULL) {
			(*points + dest)->konexioak[0] = org;
			(*points + dest)->konexioak[1] = -1;
		}
	}
	else {
		while ((*points + dest)->konexioak[kont] != -1) kont++;
		(*points + dest)->konexioak = (int*)realloc((*points + dest)->konexioak, sizeof(int) * (kont + 2));
		if ((*points + dest)->konexioak != NULL) {
			(*points + dest)->konexioak[kont] = org;
			(*points + dest)->konexioak[kont + 1] = -1;
		}
	}
}