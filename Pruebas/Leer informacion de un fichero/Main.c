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
	int* peso;
	int* idKonexioa;
	struct A_PESOS** ptrKonexioa;
} PUNTUA, * ptrPuntua;

int fitxategiaIreki(FILE** fitxategia);
void fitxategiaJaso(FILE** fitxategia);
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
void sartu(int* pisua, int* konexioa, ptrPuntua* berria);
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
	int egoera, i;
	int peso[100], id[100];

	do {
		berria = (ptrPuntua)malloc(sizeof(PUNTUA));

		if (berria == NULL) { printf("Arazo bat eman da memoria alokatzean.\n"); egoera = -1; }
		else {
			egoera = fscanf(fitxategia, "%d %d %d\n", &berria->id, &berria->pos.x, &berria->pos.y);
			i = 0;
			do {
				egoera = fscanf(fitxategia, "%d %d\n", (id + i), (peso + i));
				i++;
			} while (*(id + i - 1) != -1 && egoera == 2);
			sartu(peso, id, &berria);

			/**(berria->ptrKonexioa) = NULL;

			if (*burua == NULL && berria->id != -1) {
				*burua = berria;
				ptrAux = berria;
			}
			else {
				if (ptrAux != NULL && berria->id != -1) {
					ptrAux->ptrKonexioa = berria;
					ptrAux = *(ptrAux->ptrKonexioa);
				}
			}*/
		}
		//if (berria != NULL && berria->id == -1) { free(berria); berria = NULL; }
	} while (berria != NULL && berria->id != -1);
}

void sartu(int* pisua, int* konexioa, ptrPuntua* berria)
{
	int kont = 0, i = 0;

	while (*(konexioa + kont) != -1) kont++;
	(*berria)->peso = (int*)malloc(kont *sizeof(int));
	(*berria)->idKonexioa = (int*)malloc(kont * sizeof(int));

	if ((*berria)->peso == NULL || (*berria)->idKonexioa == NULL) printf("Arazo bat egon da memoria alokatzean.\n");
	else {
		while (*(konexioa + i) != -1) {
			*((*berria + i)->peso) = *(pisua + i);
			printf("%d\n", *((*berria + i)->peso));
			*((*berria + i)->idKonexioa) = *(konexioa + i);
			printf("%d\n", *((*berria + i)->idKonexioa));
			i++;
		}
	}
}

void pantailaratu(ptrPuntua burua)
{
	ptrPuntua ptrAux = burua;

	while (ptrAux != NULL) {
		printf("%d %d %d\n", ptrAux->id, ptrAux->pos.x, ptrAux->pos.y);
		ptrAux = ptrAux->ptrKonexioa;
	}
}

void askatu(ptrPuntua burua)
{
	ptrPuntua aux = burua;

	if (burua != NULL) {
		while (burua != NULL)
		{
			burua = burua->ptrKonexioa;
			free(aux);
			aux = burua;
		}
	}
	burua = NULL;
}