#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"

void fitxategiBatSortu(void)
{
	FILE* fitxategia;
	int kop;

	puntuKopurua(&kop);
	if (kop <= 0) printf("101 Errorea");
	else {
		fitxategiaSortu(&fitxategia);
		puntuakIdatzi(fitxategia, kop);
		pisuenMatrizeaIdatzi(fitxategia, kop);
		fclose(fitxategia);
	}
}

void puntuKopurua(int* kop)
{
	char str[MAX_SIZE];

	printf("Mapan egongo diren puntu kopurua: ");
	fgets(str, MAX_SIZE, stdin);
	sscanf(str, "%d", kop);

	
}

void fitxategiaSortu(FILE** fitxategia)
{
	char fitxIzena[MAX_SIZE];

	printf("Fitxategiaren izena: ");
	fgets(fitxIzena, MAX_SIZE, stdin);
	*(fitxIzena + strlen(fitxIzena) - 1) = '\0';
	sprintf(fitxIzena, "%s.map", fitxIzena);

	*fitxategia = fopen(fitxIzena, "wb");
}

void puntuakIdatzi(FILE* fitxategia, int kop)
{
	char str[MAX_SIZE];
	int aux, egoera, i = 0, stop = -1;

	do {
		printf("%d. puntua:\n", i + 1);

		printf("Puntuaren id-a: ");
		fgets(str, MAX_SIZE, stdin);
		sscanf(str, "%d", &aux);

		egoera = fwrite(&aux, sizeof(int), 1, fitxategia);
		if (egoera != 1) printf("Arazo bat eman da informazioa gordetzerakoan\n");
		else {
			printf("Puntuaren koordenatua (X): ");
			fgets(str, MAX_SIZE, stdin);
			sscanf(str, "%d", &aux);

			egoera = fwrite(&aux, sizeof(int), 1, fitxategia);
			if (egoera != 1) printf("Arazo bat eman da informazioa gordetzerakoan\n");
			else {
				printf("Puntuaren koordenatua (Y): ");
				fgets(str, MAX_SIZE, stdin);
				sscanf(str, "%d", &aux);

				egoera = fwrite(&aux, sizeof(int), 1, fitxategia);
				if (egoera != 1) printf("Arazo bat eman da informazioa gordetzerakoan\n");
			}
		}
		i++;
	} while (egoera == 1 && i < kop);
	fwrite(&stop, sizeof(int), 1, fitxategia);
}

void pisuenMatrizeaIdatzi(FILE* fitxategia, int kop)
{
	char str[MAX_SIZE];
	int aux, egoera, i = 0, j;

	do {
		j = 0;
		do {
			printf("%d puntuaren eta %d puntuaren arteko distantzia (metro): ", i + 1, j + 1);
			fgets(str, MAX_SIZE, stdin);
			sscanf(str, "%d", &aux);

			egoera = fwrite(&aux, sizeof(int), 1, fitxategia);
			if (egoera != 1) printf("Arazo bat eman da informazioa gordetzerakoan\n");
			j++;
		} while (j < kop && egoera == 1);
		i++;
	} while (i < kop && egoera == 1);
}