#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"

int erreserbaBurutu(int** bek, int kop)
{
	*bek = (int*)malloc(sizeof(int) * kop);
	if (*bek == NULL) return 0;
	else return 1;
}

void pantailaratu(ptrMugi burua)
{
	ptrMugi ptrAux = burua;

	printf("Ibilbidea: ");
	while (ptrAux != NULL) {
		printf("->%d ", ptrAux->moveId);
		ptrAux = ptrAux->ptrHurrengoa;
	}
}

void askatu(ptrMugi* burua)
{
	ptrMugi ptrAux = *burua, aux;

	while (ptrAux != NULL) {
		aux = ptrAux;
		ptrAux = ptrAux->ptrHurrengoa;
		free(aux);
	}
}