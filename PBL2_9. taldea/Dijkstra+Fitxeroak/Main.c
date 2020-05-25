#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"
#include "Mapa.h"

int main(int argc, char** argv)
{
	int* Grafo = NULL, aukera;
	FILE* fitxategia = NULL;
	ptrPuntua burua = NULL;
	ptrMugi mBurua = NULL;
	
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
			else MapaMarraztu(fitxategia, &burua, &Grafo);
		default:
			printf("Aukera ez da egokia.\n\n");
			break;
		}
	} while (aukera != 0);
	return 0;
}