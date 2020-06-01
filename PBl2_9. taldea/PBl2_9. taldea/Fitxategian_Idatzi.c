#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategian_Idatzi.h"
#include "Fitxategia_Irakurri.h"

void fitxategiBatSortu(void)
{
	FILE* fitxategia;
	int kop;
	float *distantzia;

	puntuKopurua(&kop);
	distantzia = (float*)malloc(sizeof(float) * kop * kop);

	if (kop <= 0 || distantzia == NULL) printf("101 Errorea");
	else {
		fitxategiaSortu(&fitxategia);
		puntuakIdatzi(fitxategia, kop, distantzia);
		distantziakIdatzi(fitxategia, kop, distantzia);
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
	fgets(fitxIzena, MAX_SIZE - 4, stdin);
	*(fitxIzena + strlen(fitxIzena) - 1) = '\0';
	sprintf(fitxIzena, "%s.map", fitxIzena);

	*fitxategia = fopen(fitxIzena, "wb");
}

void puntuakIdatzi(FILE* fitxategia, int kop, float* distantzia)
{
	char str[MAX_SIZE];
	int aux, egoera, i = 0, stop = -1;
	POS* posAux = (POS*)malloc(sizeof(POS) * kop);

	do {
		printf("%d. puntua:\n", i + 1);
		aux = i + 1;

		egoera = fwrite(&aux, sizeof(int), 1, fitxategia);
		if (egoera != 1) printf("102 Errorea\n");
		else {
			printf("Puntuaren koordenatua (X): ");
			fgets(str, MAX_SIZE, stdin);
			sscanf(str, "%f", &(posAux + i)->x);

			egoera = fwrite(&(posAux + i)->x, sizeof(float), 1, fitxategia);
			if (egoera != 1) printf("103 Errorea\n");
			else {
				printf("Puntuaren koordenatua (Y): ");
				fgets(str, MAX_SIZE, stdin);
				sscanf(str, "%f", &(posAux + i)->y);

				egoera = fwrite(&(posAux + i)->y, sizeof(float), 1, fitxategia);
				if (egoera != 1) printf("104 Errorea\n");
			}
		}
		i++;
	} while (egoera == 1 && i < kop);
	fwrite(&stop, sizeof(int), 1, fitxategia);
	kalkulatuDistantzia(distantzia, posAux, kop);
}

void kalkulatuDistantzia(float* distantzia, POS* pPos, int kop) 
{
	for(int i = 0; i < kop; i++)
		for (int j = 0; j < kop; j++) {
			if (i == j) *(distantzia + i * kop + j) = 0;
			else if (konexioa(i, j)) *(distantzia + i * kop + j) = pitagoras(pPos, i, j);
			else *(distantzia + i * kop + j) = 0;
		}
}

float pitagoras(POS* pPos, int zutabea, int lerroa)
{
	return (float)(sqrt((double)(((pPos + zutabea)->x - (pPos + lerroa)->x) * ((pPos + zutabea)->x - (pPos + lerroa)->x) + ((pPos + zutabea)->y - (pPos + lerroa)->y) * ((pPos + zutabea)->y - (pPos + lerroa)->y))));
}

int konexioa(int puntua1, int puntua2)
{
	char str[MAX_SIZE];
	int aux;

	printf("%d puntuaren eta %d puntuak konektatuta daude (0/1)? ", puntua1 + 1, puntua2 + 1);
	fgets(str, MAX_SIZE, stdin);
	sscanf(str, "%d", &aux);

	return aux;
}

void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak)
{
	int i = 0, j, egoera;

	do {
		j = 0;
		do {
			egoera = fwrite((distantziak + i * kop + j), sizeof(float), 1, fitxategia);
			printf("Idatzi da(%d): %f\n", i * kop + j, *(distantziak + i * kop + j));
			j++;
		} while (j < kop && egoera == 1);
		i++;
	} while (i < kop && egoera == 1);
}