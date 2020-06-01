#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

int fitxategiaIreki(FILE** fitxategia, char* fileName)
{
	if (*fitxategia != NULL) fclose(*fitxategia);
	*fitxategia = fopen(fileName, "rb");
	if (*fitxategia == NULL) {
		printf("201 Errorea\n");
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

		if (berria == NULL) { printf("202 Errorea\n"); egoera = -1; }
		else {
			egoera = fread(&berria->id, sizeof(int), 1, fitxategia);
			if (berria->id != -1 && egoera == 1) {
				egoera = fread(&berria->pos.x, sizeof(float), 1, fitxategia);
				if (egoera == 1) egoera = fread(&berria->pos.y, sizeof(float), 1, fitxategia);
			}
			if (egoera != 1) printf("203 Errorea\n");
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

void pisuakJaso(ptrPuntua burua, FILE* fitxategia, float** pisuak)
{
	int kont = puntuakZenbatu(burua);
	int egoera, i = 0;

	*pisuak = (float*)malloc(kont * kont * sizeof(float));
	if (*pisuak == NULL) printf("204 Errorea\n");
	else {
		do {
			egoera = fread((*pisuak + i), sizeof(float), 1, fitxategia);
			printf("Jaso da(%d): %f\n", i, *(*pisuak + i));
			i++;
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
		printf("%d %f %f\n", ptrAux->id, ptrAux->pos.x, ptrAux->pos.y);
		ptrAux = ptrAux->ptrHurrengoa;
	}
}