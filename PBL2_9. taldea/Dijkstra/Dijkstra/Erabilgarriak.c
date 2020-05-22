#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"

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