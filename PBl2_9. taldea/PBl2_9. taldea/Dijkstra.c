#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategia_Irakurri.h"
#include "Fitxategian_Idatzi.h"

void setUp(FILE* fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, int pos1, int pos2)
{
	int pKop, org, dest;

	//puntuakJaso(burua, fitxategia);
	pKop = puntuakZenbatu(*burua);

	// Bidea Aurkitu
	org = pos1;
	dest = pos2;

	dijkstra(*pisuak, pKop, org - 1, dest - 1, mBurua);
}

void dijkstra(float* pisuak, int pKop, int org, int dest, ptrMugi* burua)
{
	float* pisua = NULL, * distantzia = NULL, * aurrekoa = NULL, * check = NULL, minLuzeera;
	int kop, hurrengoa = 0;

	// Aurrekoa nodo bakoitzaren aurrekoa gordetzen du
	// kop begiratutako nodo kopurua kontrolatzen du
	if (erreserbaBurutu(&pisua, pKop * pKop) && erreserbaBurutu(&distantzia, pKop) && erreserbaBurutu(&aurrekoa, pKop) && erreserbaBurutu(&check, pKop)) {
		// Dijkstraren taula sortu
		dijkstraTaula(pisuak, pisua, pKop);

		// hasieratu aurrekoa, distantzia eta check
		hasieratuDijkstra(pKop, org, &kop, distantzia, aurrekoa, check, pisua);

		while (kop < pKop - 1) {
			minLuzeera = INFINITO;
			// 'hurrengoa'-k gertuen dagoen nodoa ematen du
			for (int i = 0; i < pKop; i++)
				if (*(distantzia + i) < minLuzeera && !*(check + i)) {
					minLuzeera = *(distantzia + i);
					hurrengoa = i;
				}

			// beste nodoak erabiliz bide motzen bat dagoen begiratu
			*(check + hurrengoa) = 1;
			for (int i = 0; i < pKop; i++)
				if (!*(check + i))
					if (minLuzeera + *(pisua + hurrengoa * pKop + i) < *(distantzia + i)) {
						*(distantzia + i) = minLuzeera + *(pisua + hurrengoa * pKop + i);
						*(aurrekoa + i) = (float)(hurrengoa);
					}
			kop++;
		}
		// Nodo batetik besterako distantziak kate batean gorde
		gorde(pKop, org, dest, distantzia, aurrekoa, burua);
		free(distantzia);
		free(aurrekoa);
		free(pisua);
		free(check);
	}
	else printf("303 Errorea\n");
}

void dijkstraTaula(float* pisuak, float* pisua, int pKop)
{
	for (int i = 0; i < pKop; i++)
		for (int j = 0; j < pKop; j++)
			if (*(pisuak + i * pKop + j) == 0)
				*(pisua + i * pKop + j) = INFINITO;
			else
				*(pisua + i * pKop + j) = *(pisuak + i * pKop + j);
}

void hasieratuDijkstra(int pKop, int org, int* kop, float* distantzia, float* aurrekoa, float* check, float* pisua)
{
	for (int i = 0; i < pKop; i++) {
		*(distantzia + i) = *(pisua + org * pKop + i);
		*(aurrekoa + i) = (float)(org);
		*(check + i) = 0;
	}
	*(distantzia + org) = 0;
	*(check + org) = 1;
	*kop = 1;
}

void gorde(int pKop, int org, int dest, float* distantzia, float* aurrekoa, ptrMugi* burua)
{
	for (int i = 0; i < pKop; i++)
		if (i == dest) {
			printf("\nDistance of node %d = %.2f\n", i + 1, *(distantzia + i));
			mugimenduak(i + 1, burua);

			int j = i;
			do {
				j = (int)(*(aurrekoa + j));
				mugimenduak(j + 1, burua);
			} while (j != org);
		}
	ptrMugi ptrAux = *burua;
	while (ptrAux != NULL) { 
		printf("%d\n", ptrAux->moveId); 
		ptrAux = ptrAux->ptrHurrengoa; 
	}
}

void mugimenduak(int mugimendua, ptrMugi* burua)
{
	ptrMugi ptrAux = *burua, berria;

	berria = (ptrMugi)malloc(sizeof(MUGI));
	if (berria == NULL) printf("304 Errorea\n");
	else {
		berria->moveId = mugimendua;
		berria->ptrHurrengoa = NULL;

		if (*burua == NULL) *burua = berria;
		else {
			*burua = berria;
			(*burua)->ptrHurrengoa = ptrAux;
		}
	}
}