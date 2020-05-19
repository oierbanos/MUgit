#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 128

typedef struct DE_POSIZIOA
{
	int x;
	int y;
} POS;

typedef struct DE_PUNTUA 
{
	int id;
	POS pos;
	struct DE_PUNTUA* ptrHurrengoa;
} PUNTUA, *ptrPuntua;

int fitxategiaIreki(FILE** fitxategia);
void fitxategiaJaso(FILE** fitxategia);
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
void pantailaratu(ptrPuntua burua);
void askatu(ptrPuntua burua);

// Funtzio orokorra
int main(int argc, char** argv)
{
	FILE* fitxategia;
	ptrPuntua burua = NULL;

	fitxategiaJaso(&fitxategia);
	puntuakJaso(&burua, fitxategia);
	pantailaratu(burua);

	askatu(burua);
	fclose(fitxategia);
}

void fitxategiaJaso(FILE** fitxategia)
{
	char aukera[MAX_STR];
	int egoera;

	do {
		egoera = fitxategiaIreki(fitxategia);

		if (egoera == 0) {
			printf("Helbidea berriz sartu nahi duzu (bai/ez)? ");
			fgets(aukera, MAX_STR, stdin);
			*(aukera + strlen(aukera) - 1) = '\0';
		}
	} while (egoera == 0 && strcmp(aukera, "bai") == 0);
}

int fitxategiaIreki(FILE** fitxategia)
{
	char izena[MAX_STR];

	printf("Fitxategiaren helbidea: ");
	fgets(izena, MAX_STR, stdin);
	*(izena + strlen(izena) - 1) = '\0';

	*fitxategia = fopen(izena, "r");
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
			egoera = fscanf(fitxategia, "%d %d %d\n", &berria->id, &berria->pos.x, &berria->pos.y);
			berria->ptrHurrengoa = NULL;

			if (*burua == NULL && berria->id != -1) {
				*burua = berria;
				ptrAux = berria;
			}
			else {
				if (ptrAux != NULL && berria->id != -1) {
					ptrAux->ptrHurrengoa = berria;
					ptrAux = ptrAux->ptrHurrengoa;
				}
			}
		}
		if (berria != NULL && berria->id == -1) { free(berria); berria = NULL; }
	} while (berria != NULL && berria->id != -1);
}

void pantailaratu(ptrPuntua burua)
{
	ptrPuntua ptrAux = burua;

	while (ptrAux != NULL) {
		printf("%d %d %d\n", ptrAux->id, ptrAux->pos.x, ptrAux->pos.y);
		ptrAux = ptrAux->ptrHurrengoa;
	}
}

void askatu(ptrPuntua burua)
{
	ptrPuntua aux = burua;

	if (burua != NULL) {
		while (burua != NULL)
		{
			burua = burua->ptrHurrengoa;
			free(aux);
			aux = burua;
		}
	}
	burua = NULL;
}