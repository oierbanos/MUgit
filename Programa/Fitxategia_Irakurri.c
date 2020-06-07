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
		printf("#301 Errorea\n");
		return 0;
	}
	else return 1;
}

int dimentsioakJaso(FILE* fitxategia, DIM* mapDim)
{
	int egoera;

	egoera = fread(mapDim, sizeof(DIM), 1, fitxategia);
	if (egoera != 1) printf("#302 Errorea\n");

	return egoera;
}

int puntuakJaso(ptrPuntua* burua, FILE* fitxategia)
{
	ptrPuntua berria = NULL, ptrAux = NULL;
	int egoera;

	do {
		berria = (ptrPuntua)malloc(sizeof(PUNTUA));

		if (berria == NULL) { printf("#303 Errorea\n"); egoera = -1; }
		else {
			egoera = fread(&berria->id, sizeof(int), 1, fitxategia);
			if (berria->id != -1 && egoera == 1) {
				egoera = fread(&berria->pos.x, sizeof(float), 1, fitxategia);
				if (egoera == 1) egoera = fread(&berria->pos.y, sizeof(float), 1, fitxategia);
			}
			if (egoera != 1) printf("#304 Errorea\n");
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

	return egoera;
}

int pisuakJaso(ptrPuntua burua, FILE* fitxategia, float** pisuak)
{
	int kont = puntuakZenbatu(burua);
	int egoera = 0, i = 0;

	*pisuak = (float*)malloc(kont * kont * sizeof(float));
	if (*pisuak == NULL) printf("#305 Errorea\n");
	else {
		do {
			egoera = fread((*pisuak + i), sizeof(float), 1, fitxategia);
			if (egoera != 1 && egoera != EOF) printf("#306 Errorea\n");
			i++;
		} while (egoera == 1 && i < kont * kont);
	}

	return egoera;
}

int puntuakZenbatu(ptrPuntua burua)
{
	ptrPuntua ptrAux = burua;
	int kont = 0;

	while (ptrAux != NULL) { 
		ptrAux = ptrAux->ptrHurrengoa; 
		kont++; 
	}
	if (kont == 0) printf("#307 Errorea\n");

	return kont;
}