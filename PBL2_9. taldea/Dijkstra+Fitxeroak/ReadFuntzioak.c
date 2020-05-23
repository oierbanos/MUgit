#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"

void fitxategiaJaso(FILE** fitxategia)
{
	char aukera[MAX_SIZE];
	int egoera;

	do {
		egoera = fitxategiaIreki(fitxategia);

		if (egoera == 0) {
			printf("Helbidea berriz sartu nahi duzu (bai/ez)? ");
			fgets(aukera, MAX_SIZE, stdin);
			*(aukera + strlen(aukera) - 1) = '\0';
		}
	} while (egoera == 0 && strcmp(aukera, "bai") == 0);
}

int fitxategiaIreki(FILE** fitxategia)
{
	char izena[MAX_SIZE];

	printf("Fitxategiaren helbidea: ");
	fgets(izena, MAX_SIZE, stdin);
	*(izena + strlen(izena) - 1) = '\0';

	*fitxategia = fopen(izena, "rb");
	if (*fitxategia == NULL) {
		printf("Arazo bat eman da fitxategia irakurtzerakoan.\n");
		return 0;
	}
	else return 1;
}

void puntuakJaso(ptrPuntua* burua, FILE* fitxategia)
{
	ptrPuntua berria = NULL, ptrAux = NULL;
	int egoera;

	do {
		berria = (ptrPuntua)malloc(sizeof(PUNTUA));

		if (berria == NULL) { printf("Arazo bat eman da memoria alokatzean.\n"); egoera = -1; }
		else {
			egoera = fread(&berria->id, sizeof(int), 1, fitxategia);
			if (berria->id != -1 && egoera == 1) {
				egoera = fread(&berria->pos.x, sizeof(int), 1, fitxategia);
				if (egoera == 1) egoera = fread(&berria->pos.y, sizeof(int), 1, fitxategia);
			}
			else if (egoera != 1) printf("Arazo bat egon da fitxategia irakurtzerakoan.\n");
			berria->ptrHurrengoa = NULL;

			if (*burua == NULL && berria->id != -1 && egoera == 1) {
				*burua = berria;
				ptrAux = berria;
			}
			else {
				if (ptrAux != NULL && berria->id != -1 && egoera == 1) {
					ptrAux->ptrHurrengoa = berria;
					ptrAux = ptrAux->ptrHurrengoa;
				}
			}
		}
		if (berria != NULL && berria->id == -1) { free(berria); berria = NULL; }
	} while (berria != NULL && berria->id != -1 && egoera == 1);
}

void pisuakJaso(ptrPuntua burua, FILE* fitxategia, int** pisuak)
{
	int kont = puntuakZenbatu(burua);
	int egoera, i = 0;

	*pisuak = (int*)malloc(kont * kont * sizeof(int));
	if (*pisuak == NULL) printf("Arazo bat eman da memoria alokatzean.\n");
	else {
		do {
			egoera = fread((*pisuak + i), sizeof(int), 1, fitxategia);
			printf("%d ", *(*pisuak + i));
			i++;
			if (i % kont == 0) printf("\n");
		} while (egoera == 1 && i < kont * kont);
	}
}

int puntuakZenbatu(ptrPuntua burua)
{
	ptrPuntua ptrAux = burua;
	int kont = 0;

	while (ptrAux != NULL) { ptrAux = ptrAux->ptrHurrengoa; kont++; }

	return kont;
}

void pantailaratuPuntuak(ptrPuntua burua)
{
	ptrPuntua ptrAux = burua;

	while (ptrAux != NULL) {
		printf("%d %d %d\n", ptrAux->id, ptrAux->pos.x, ptrAux->pos.y);
		ptrAux = ptrAux->ptrHurrengoa;
	}
}