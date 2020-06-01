#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"

int menu(void)
{
	char str[MAX_SIZE];
	int aukera;

	printf("==========================\n");
	printf("           MENU           \n");
	printf("==========================\n");
	printf("1.- Mapa bat sortu.\n");
	printf("2.- Mapa bat kargatu.\n");
	printf("3.- Dijkstra aplikatu.\n");
	printf("4.- Mapa marraztu\n");
	printf("Sartu 0 programa amaitzeko.\n");
	printf("\nAukera: ");
	fgets(str, MAX_SIZE, stdin);
	sscanf(str, "%d", &aukera);

	return aukera;
}

int erreserbaBurutu(float** bek, int kop)
{
	*bek = (float*)malloc(sizeof(float) * kop);
	if (*bek == NULL) return 0;
	else return 1;
}

void bilatu(ptrPuntua burua, float* x, float* y, int id) {

	ptrPuntua ptrAux = burua;
	
	while (ptrAux->id != id && ptrAux->ptrHurrengoa != NULL) ptrAux = ptrAux->ptrHurrengoa;

	*x = ptrAux->pos.x;
	*y = ptrAux->pos.y;
}

void askatuPuntuak(ptrPuntua* burua)
{
	ptrPuntua aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL)
		{
			*burua = (*burua)->ptrHurrengoa;
			free(aux);
			aux = *burua;
		}
	}
	*burua = NULL;
}

void askatuMugitu(ptrMugi* burua)
{
	ptrMugi aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL)
		{
			*burua = (*burua)->ptrHurrengoa;
			free(aux);
			aux = *burua;
		}
	}
	*burua = NULL;
}