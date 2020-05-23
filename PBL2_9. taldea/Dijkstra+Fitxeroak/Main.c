#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"

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
			if(fitxategia == NULL) printf("Arazo bat eman da");
			else setUp(fitxategia, &burua, &mBurua, &Grafo);
			break;
		default:
			printf("Aukera ez da egokia.\n\n");
			break;
		}
	} while (aukera != 0);
}