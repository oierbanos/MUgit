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

void bitmap(MP** points, int* pkop, DIM* mapDim) 
{
	SDL_Event ebentu;
	SDL_Window* window;
	POS org = { org.x = -1 }, dest;
	char aukera[MAX_SIZE], img[MAX_SIZE];
	int running = 0, check = -1, tmp, mapImg = -1;

	*mapDim = eskatuDimentzioak(aukera);
	if (strcmp(aukera, "bai") == 0) eskatuIrudia(img);

	if (!hasieratu(&window, &renderer, (*mapDim).width, (*mapDim).height, "Create map") && TTF_Init() == 0 && mapDim->height > 0 && mapDim->width > 0) {
		atexit(TTF_Quit);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderClear(renderer);
		if (strcmp(aukera, "bai") == 0) mapImg = irudiaSortu(0, 0, img, window);
		textuaIdatzi(10, 5, "Ezkerreko klick-a: puntua sortu");
		textuaIdatzi(10, 25, "Eskuineko klick-a: Bi puntu konektatu");
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);

		while (running == 0) {
			while (SDL_PollEvent(&ebentu)) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				if (ebentu.type == SDL_QUIT) running = 1;
				else if (ebentu.type == SDL_KEYDOWN && (ebentu.key.keysym.sym == SDLK_ESCAPE || ebentu.key.keysym.sym == SDLK_RETURN)) 
					running = 1;
				else if (ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_LEFT) {
					zirkuluaMarraztu((float)(ebentu.button.x), (float)(ebentu.button.y), 5);
					koordenatuakGorde(points, pkop, (float)(ebentu.button.x), (float)(ebentu.button.y));
					SDL_RenderPresent(renderer);
					SDL_UpdateWindowSurface(window);
				}
				else if ((ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_RIGHT) && *points != NULL) {
					check = checkPlace(*points, *pkop, ebentu);
					if (check != -1 && org.x == -1) {
						org = (*points + check)->pos;
						tmp = check;
					}
					else if (check != -1 && org.x != -1) { 
						dest = (*points + check)->pos;
						if (org.x != dest.x && org.y != dest.y) {
							SDL_SetRenderDrawColor(renderer, 255, 145, 50, 255);
							SDL_RenderDrawLine(renderer, org.x, org.y, dest.x, dest.y);
							SDL_RenderPresent(renderer);
							SDL_UpdateWindowSurface(window);
							konektatu(points, tmp, check);
							org.x = -1;
						}
					}
					check = -1;
				}
			}
		}
		if (mapImg != -1) irudiaKendu(mapImg);
		ordenatu(*points, *pkop);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
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

DIM eskatuDimentzioak(char* aukera)
{
	char width[MAX_SIZE] = { "" }, height[MAX_SIZE] = { "" }, str1[MAX_SIZE], str2[MAX_SIZE];
	int running = IN, option = 1, img = -1;
	DIM dim = { -1, -1 };
	SDL_Window* window;
	SDL_Event ebentu;

	if (!hasieratu(&window, &renderer, 450, 563, "Create map") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		textuaGaitu(1);
		img = irudiaSortu(0, 0, DIM_IMAGE, window);

		while (running == IN) {
			SDL_RenderClear(renderer);
			irudiakMarraztu();
			while (SDL_PollEvent(&ebentu) && running == IN) {
				if (option == 1)
					aukeraJaso(ebentu, &option, width);
				else if (option == 2)
					aukeraJaso(ebentu, &option, height);
				if (ebentu.type == SDL_MOUSEBUTTONDOWN) {
					if (checkArea(93, 401, 102, 44, ebentu)) { strcpy(aukera, "bai"); running = OUT; }
					else if (checkArea(256, 401, 102, 44, ebentu)) { strcpy(aukera, "ez"); running = OUT; }
				}
				else if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_ESCAPE)
					running = OUT;
			}
			sprintf(str1, "%s_", width);
			textuaIdatzi(52, 195, str1);

			sprintf(str2, "%s_", height);
			textuaIdatzi(52, 288, str2);

			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
		sscanf(str1, "%d", &dim.width);
		sscanf(str2, "%d", &dim.height);

		irudiaKendu(img);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	return dim;
}

void aukeraJaso(SDL_Event ebentu, int* option, char* input)
{
	if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN) {
		if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
			*(input + strlen(input) - 1) = '\0';
		else if (ebentu.type == SDL_TEXTINPUT && strlen(input) <= MAX_SIZE)
			strcat(input, ebentu.text.text);
		else if (ebentu.key.keysym.sym == SDLK_RETURN)
			if (ebentu.key.keysym.sym == SDLK_RETURN) (*option)++;
	}
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

void ordenatu(MP* points, int pkop)
{
	int j, k, txiki, txikiPos, tmp;

	for (int i = 0; i < pkop; i++) {
		j = 0;
		while ((points + i)->konexioak[j] != -1) {
			txiki = (points + i)->konexioak[j];
			k = j;
			txikiPos = k;
			while ((points + i)->konexioak[k] != -1) {
				if ((points + i)->konexioak[k] < txiki) { txiki = (points + i)->konexioak[k]; txikiPos = k; }
				k++;
			}
			if (txikiPos != j) {
				tmp = (points + i)->konexioak[txikiPos];
				(points + i)->konexioak[txikiPos] = (points + i)->konexioak[j];
				(points + i)->konexioak[j] = tmp;
			}
			j++;
		}
	}
}

void eskatuIrudia(char* img)
{
	int egoera;

	strcpy(img, "");
	egoera = getTextFromUser(img, "Get Map", 450, 563, MAP_IMAGE);
}