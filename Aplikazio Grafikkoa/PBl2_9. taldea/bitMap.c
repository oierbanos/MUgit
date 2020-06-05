#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "Mapa.h"
#include "Menu.h"
#include "bitMap.h"
#include "imagen.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"

void bitmap(MP** points, int* pkop, DIM* mapDim) 
{
	SDL_Event ebentu;
	SDL_Window* window;
	POS org = { org.x = -1 }, dest;
	char aukera[MAX_SIZE], img[MAX_SIZE];
	int running = 0, check = -1, tmp, mapImg = -1;

	*mapDim = eskatuDimentsioak(aukera); // Maparen dimentsioak eta irudi bat sartu nahi den galdetu
	if (strcmp(aukera, "bai") == 0) eskatuIrudia(img);

	if (!hasieratu(&window, &renderer, (*mapDim).width, (*mapDim).height, "Create map") && TTF_Init() == 0 && mapDim->height > 0 && mapDim->width > 0) {
		atexit(TTF_Quit);
		textuaGaitu(1);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderClear(renderer);
		if (strcmp(aukera, "bai") == 0) mapImg = irudiaSortu(0, 0, img, window); // Atzeko irudia badago, sortu
		textuaIdatzi(10, 5, "Ezkerreko klick-a: puntua sortu"); // Instrukzioak
		textuaIdatzi(10, 25, "Eskuineko klick-a: Bi puntu konektatu");
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);

		hasieratuKonexioak(*points, *pkop); // Konexio guztiak "-1"-era jarri
		while (running == 0) {
			while (SDL_PollEvent(&ebentu)) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				if (ebentu.type == SDL_QUIT) running = 1; // Lehioa itxi
				else if (ebentu.type == SDL_KEYDOWN && (ebentu.key.keysym.sym == SDLK_ESCAPE || ebentu.key.keysym.sym == SDLK_RETURN))
					running = 1; // Lehioa itxi
				else if (ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_LEFT) {
					zirkuluaMarraztu((float)(ebentu.button.x), (float)(ebentu.button.y), 5); // Puntuak sortu
					koordenatuakGorde(points, pkop, (float)(ebentu.button.x), (float)(ebentu.button.y)); // Puntuen koordenatuak gorde
					SDL_RenderPresent(renderer);
					SDL_UpdateWindowSurface(window);
				}
				else if ((ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_RIGHT) && *points != NULL) {
					check = checkPlace(*points, *pkop, ebentu); // Puntu batean klikatu den konprobatu
					if (check != -1 && org.x == -1) { // Lehenengo aldian hasierako puntua gorde
						org = (*points + check)->pos;
						tmp = check;
					}
					else if (check != -1 && org.x != -1) {
						dest = (*points + check)->pos; // Bigarren aldian amaierako puntua gorde
						if (org.x != dest.x && org.y != dest.y) {
							SDL_SetRenderDrawColor(renderer, 255, 145, 50, 255); // Puntuen arteko konexioa irudikatu
							SDL_RenderDrawLine(renderer, org.x, org.y, dest.x, dest.y);
							SDL_RenderPresent(renderer);
							SDL_UpdateWindowSurface(window);
							konektatu(points, tmp, check); // Konexioa gorde
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
	else printf("#101. Errorea\n");
}

void koordenatuakGorde(MP** points, int* kont, float mouseX, float mouseY)
{
	if (*points == NULL) *points = (MP*)malloc(sizeof(MP));
	else *points = (MP*)realloc(*points, sizeof(MP) * (*kont + 1));

	if (*points != NULL) { // Puntu berri bat sortu
		(*points + *kont)->pos.x = mouseX;
		(*points + *kont)->pos.y = mouseY;
		(*points + *kont)->konexioak = NULL;
		(*kont)++;
	}
	else printf("#201 Errorea\n");
}

int checkPlace(MP* points, int kont, SDL_Event ebentu)
{
	int check = 0, i = 0;

	while (i < kont && check == 0) { // Begiratu zein puntun klikatu den
		check = checkArea((points + i)->pos.x - 5, (points + i)->pos.y - 5, 10, 10, ebentu);
		i++;
	}
	if (check == 1) return i - 1;
	else return -1;
}

DIM eskatuDimentsioak(char* aukera)
{
	char width[MAX_SIZE] = { "" }, height[MAX_SIZE] = { "" }, str1[MAX_SIZE + 1], str2[MAX_SIZE + 1];
	int running = IN, option = 1, img = -1;
	DIM dim = { -1, -1 };
	SDL_Window* window;
	SDL_Event ebentu;

	if (!hasieratu(&window, &renderer, 450, 563, "Create map") && TTF_Init() == 0) {
		atexit(TTF_Quit);
		textuaGaitu(1);
		img = irudiaSortu(0, 0, DIM_IMAGE, window); // Atzeko aldea irudikatu

		while (running == IN) {
			SDL_RenderClear(renderer);
			irudiakMarraztu();
			while (SDL_PollEvent(&ebentu) && running == IN) {
				if (option == 1)
					aukeraJaso(ebentu, &option, height); // Lehenengo aukera jaso
				else if (option == 2)
					aukeraJaso(ebentu, &option, width); // Bigarren aukera jaso
				if (ebentu.type == SDL_MOUSEBUTTONDOWN) {
					if (checkArea(93, 401, 102, 44, ebentu)) { strcpy(aukera, "bai"); running = OUT; }
					else if (checkArea(256, 401, 102, 44, ebentu)) { strcpy(aukera, "ez"); running = OUT; } // "Bai/Ez" botoi batean klikatu den konprobatu
				}
				else if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_ESCAPE)
					running = TERMINATE; // Lehioa itxi
			}
			sprintf(str1, "%s_", height); // Lehen aukeraren textua idatzi
			textuaIdatzi(52, 195, str1);

			sprintf(str2, "%s_", width); // Bigarren aukeraren textua idatzi
			textuaIdatzi(52, 288, str2);

			SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}
		if (running != TERMINATE) { // dimentsioak jaso
			sscanf(str1, "%d", &dim.height);
			sscanf(str2, "%d", &dim.width);
		}

		closeFont(); // Textua desgaitu
		irudiaKendu(img);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	else printf("#101. Errorea\n");

	return dim;
}

void aukeraJaso(SDL_Event ebentu, int* option, char* input)
{
	if (ebentu.type == SDL_TEXTINPUT || ebentu.type == SDL_KEYDOWN) {
		if (ebentu.type == SDL_KEYDOWN && ebentu.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
			*(input + strlen(input) - 1) = '\0'; // Textuko azken karakterea ezabatu
		else if (ebentu.type == SDL_TEXTINPUT && strlen(input) <= MAX_SIZE)
			strcat(input, ebentu.text.text); // Textua jaso
		else if (ebentu.key.keysym.sym == SDLK_RETURN)
			if (ebentu.key.keysym.sym == SDLK_RETURN) (*option)++; // Aukera aldatu
	}
}

void konektatu(MP** points, int org, int dest)
{
	int kont = 0;

	if ((*points + org)->konexioak == NULL) { // Lehenengo konexioa jaso (hasiera)
		(*points + org)->konexioak = (int*)malloc(sizeof(int) * 2);
		if ((*points + org)->konexioak != NULL) {
			(*points + org)->konexioak[0] = dest;
			(*points + org)->konexioak[1] = -1;
		}
	}
	else {
		while ((*points + org)->konexioak[kont] != -1) kont++; // Hurrengo konexioa jaso (hasiera)
		(*points + org)->konexioak = (int*)realloc((*points + org)->konexioak, sizeof(int) * (kont + 2));
		if ((*points + org)->konexioak != NULL) {
			(*points + org)->konexioak[kont] = dest;
			(*points + org)->konexioak[kont + 1] = -1;
		}
	}

	if ((*points + dest)->konexioak == NULL) { // Lehenengo konexioa jaso (amaiera)
		(*points + dest)->konexioak = (int*)malloc(sizeof(int) * 2);
		if ((*points + dest)->konexioak != NULL) {
			(*points + dest)->konexioak[0] = org;
			(*points + dest)->konexioak[1] = -1;
		}
	}
	else {
		while ((*points + dest)->konexioak[kont] != -1) kont++; // Hurrengo konexioak jaso (amaiera)
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
		while ((points + i)->konexioak[j] != -1) { // Konexioen amaiera "-1" batekin adierazten da
			txiki = (points + i)->konexioak[j];
			k = j;
			txikiPos = k;
			while ((points + i)->konexioak[k] != -1) { // Puntuak txikitik handira ordenatu (ID-a kontuan hartuta)
				if ((points + i)->konexioak[k] < txiki) { txiki = (points + i)->konexioak[k]; txikiPos = k; }
				k++;
			}
			if (txikiPos != j) { // Puntuen aldaketa egin
				tmp = (points + i)->konexioak[txikiPos];
				(points + i)->konexioak[txikiPos] = (points + i)->konexioak[j];
				(points + i)->konexioak[j] = tmp;
			}
			j++;
		}
	}
}

void hasieratuKonexioak(MP* points, int pkop)
{
	for (int i = 0; i < pkop; i++)
		*(points + i)->konexioak = -1;
}

void eskatuIrudia(char* img)
{
	strcpy(img, "");
	getTextFromUser(img, "Get Map", 450, 563, MAP_IMAGE);
}