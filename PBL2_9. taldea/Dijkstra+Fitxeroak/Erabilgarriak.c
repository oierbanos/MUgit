#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "FileReading.h"
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

int erreserbaBurutu(int** bek, int kop)
{
	*bek = (int*)malloc(sizeof(int) * kop);
	if (*bek == NULL) return 0;
	else return 1;
}

void pantailaratuBidea(ptrMugi burua)
{
	ptrMugi ptrAux = burua;

	printf("Ibilbidea: ");
	while (ptrAux != NULL) {
		printf("->%d ", ptrAux->moveId);
		ptrAux = ptrAux->ptrHurrengoa;
	}
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