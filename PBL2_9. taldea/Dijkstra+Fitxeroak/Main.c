#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"
#include "Mapa.h"
#include "ClickDetect.h"

int main(int argc, char** argv)
{
	int* Grafo = NULL, aukera;
	FILE* fitxategia = NULL;
	ptrPuntua burua = NULL;
	ptrMugi mBurua = NULL;
	int running = 0;
	int id = 0;
	SDL_Event ebentu;
	
	do {
		aukera = menu();
		switch (aukera)
		{
		case 0:
			break;
		case 1: // Error desde 100
			//Mapa bat sortu
			fitxategiBatSortu();
			break;
		case 2: // Error desde 200
			//Mapa bat kargatu
			fitxategiaJaso(&fitxategia);
			break;
		case 3: // Error desde 300
			//Dijkstra
			if(fitxategia == NULL) printf("301 Errorea\n");
			else setUp(fitxategia, &burua, &mBurua, &Grafo);
			break;
		case 4:
			//Mapa marraztu
			if (fitxategia == NULL) printf("301 Errorea\n");
			else
			{
				MapaMarraztu(fitxategia, &burua, &Grafo);
				while (running == 0)
				{ // Loop infinito para mantener la pantalla
					
					while (SDL_PollEvent(&ebentu) == 1 && ebentu.type == SDL_MOUSEBUTTONDOWN && ebentu.button.button == SDL_BUTTON_LEFT && running == 0)
					{
						id = clickID(burua, ebentu);
						if (id != 0)
						{
							running = 1;
						}
					}					
				}
			}
		default:
			printf("Aukera ez da egokia.\n\n");
			break;
		}
	} while (aukera != 0);
	return 0;
}