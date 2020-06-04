#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Menu.h"
#include "bitMap.h"
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategian_Idatzi.h"
#include "Fitxategia_Irakurri.h"

void fitxategiBatSortu(MP* points, int pkop, DIM mapDim)
{
	FILE* fitxategia;
	float *distantzia;

	distantzia = (float*)malloc(sizeof(float) * pkop * pkop);

	if (pkop <= 0 || distantzia == NULL) printf("101 Errorea");
	else {
		fitxategiaSortu(&fitxategia);
		dimentsioakIdatzi(fitxategia, mapDim);
		puntuakIdatzi(fitxategia, points, pkop, distantzia);
		distantziakIdatzi(fitxategia, pkop, distantzia);
		fclose(fitxategia);
	}
}

void fitxategiaSortu(FILE** fitxategia)
{
	char fitxIzena[MAX_SIZE] = "", konprobaketa[MAX_SIZE];
	int egoera;

	egoera = getTextFromUser(fitxIzena, "Get File", 450, 563, FILE_IMAGE);
	if (strlen(fitxIzena) >= 4) {
		sprintf(konprobaketa, "%s", (fitxIzena + strlen(fitxIzena) - 4));
		if (strcmp(konprobaketa, ".map") != 0) sprintf(fitxIzena, "%s.map", fitxIzena);
	}
	else sprintf(fitxIzena, "%s.map", fitxIzena);

	*fitxategia = fopen(fitxIzena, "wb");
}

void dimentsioakIdatzi(FILE* fitxategia, DIM mapDim)
{
	int egoera;

	egoera = fwrite(&mapDim, sizeof(DIM), 1, fitxategia);
	if (egoera != 1) printf("Error\n");
}


void puntuakIdatzi(FILE* fitxategia, MP* points, int kop, float* distantzia)
{
	int egoera, i = 1, stop = -1;

	do {
		egoera = fwrite(&i, sizeof(int), 1, fitxategia);
		if (egoera != 1) printf("102 Errorea\n");
		else {
			egoera = fwrite(&(points + i - 1)->pos.x, sizeof(float), 1, fitxategia);
			if (egoera != 1) printf("103 Errorea\n");
			else {
				egoera = fwrite(&(points + i - 1)->pos.y, sizeof(float), 1, fitxategia);
				if (egoera != 1) printf("104 Errorea\n");
			}
		}
		i++;
	} while (egoera == 1 && i <= kop);

	if (egoera == 1) {
		fwrite(&stop, sizeof(int), 1, fitxategia);
		kalkulatuDistantzia(distantzia, points, kop);
	}
	else printf("Error\n");
}

void kalkulatuDistantzia(float* distantzia, MP* points, int kop) 
{
	int j, i;

	for (i = 0; i < kop; i++)
		for (j = 0; j < kop; j++)
			*(distantzia + i * kop + j) = 0;

	for (int i = 0; i < kop; i++) {
		j = 0;
		while ((points + i)->konexioak[j] != -1) {
			*(distantzia + i * kop + (points + i)->konexioak[j]) = pitagoras(points, i, (points + i)->konexioak[j]);
			j++;
		}
	}
}

float pitagoras(MP* points, int zutabea, int lerroa)
{
	return (float)(sqrt((double)(((points + zutabea)->pos.x - (points + lerroa)->pos.x) * ((points + zutabea)->pos.x - (points + lerroa)->pos.x) + ((points + zutabea)->pos.y - (points + lerroa)->pos.y) * ((points + zutabea)->pos.y - (points + lerroa)->pos.y))));
}

void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak)
{
	int i = 0, j, egoera;

	do {
		j = 0;
		do {
			egoera = fwrite((distantziak + i * kop + j), sizeof(float), 1, fitxategia);
			j++;
		} while (j < kop && egoera == 1);
		i++;
	} while (i < kop && egoera == 1);
	if (egoera != 1) printf("Error\n");
}