#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "FileReading.h"
#include "FileWriting.h"

void setUp(FILE* fitxategia, ptrPuntua* burua, ptrMugi* mBurua, int** Grafo)
{
	int pKop, org, dest;

	puntuakJaso(burua, fitxategia);
	pKop = puntuakZenbatu(*burua);

	if (!erreserbaBurutu(Grafo, pKop * pKop)) printf("302 Errorea\n");
	else {
		// Pisuen matrizea sartu
		pisuakJaso(*burua, fitxategia, Grafo);

		// Bidea Aurkitu
		printf("If you enter -1 as the starting node the program will end.\n");
		do {
			printf("Enter the starting node: ");
			scanf("%d", &org);

			if (org != -1) {
				printf("Enter the final node: ");
				scanf("%d", &dest);

				dijkstra(*Grafo, pKop, org - 1, dest - 1, mBurua);

				printf("\n============================\n");
				pantailaratuBidea(*mBurua);
				askatuMugitu(mBurua);
				printf("\n============================\n");
			}
			printf("\n");
		} while (org != -1);
	}
	askatuPuntuak(burua);
	fclose(fitxategia);
	free(Grafo);
}

void dijkstra(int* Grafo, int pKop, int org, int dest, ptrMugi* burua)
{
	int* pisua = NULL, * distantzia = NULL, * aurrekoa = NULL, * check = NULL;
	int kop, minLuzeera, hurrengoa = 0;

	// Aurrekoa nodo bakoitzaren aurrekoa gordetzen du
	// kop begiratutako nodo kopurua kontrolatzen du
	if (erreserbaBurutu(&pisua, pKop * pKop) && erreserbaBurutu(&distantzia, pKop) && erreserbaBurutu(&aurrekoa, pKop) && erreserbaBurutu(&check, pKop)) {
		// Dijkstraren taula sortu
		dijkstraTaula(Grafo, pisua, pKop);

		// hasieratu aurrekoa, distantzia eta check
		hasieratu(pKop, org, &kop, distantzia, aurrekoa, check, pisua);

		while (kop < pKop - 1) {
			minLuzeera = INFINITY;

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
						*(aurrekoa + i) = hurrengoa;
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

void dijkstraTaula(int* Grafo, int* pisua, int pKop)
{
	for (int i = 0; i < pKop; i++)
		for (int j = 0; j < pKop; j++)
			if (*(Grafo + i * pKop + j) == 0)
				*(pisua + i * pKop + j) = INFINITY;
			else
				*(pisua + i * pKop + j) = *(Grafo + i * pKop + j);
}

void hasieratu(int pKop, int org, int* kop, int* distantzia, int* aurrekoa, int* check, int* pisua)
{
	for (int i = 0; i < pKop; i++) {
		*(distantzia + i) = *(pisua + org * pKop + i);
		*(aurrekoa + i) = org;
		*(check + i) = 0;
	}
	*(distantzia + org) = 0;
	*(check + org) = 1;
	*kop = 1;
}

void gorde(int pKop, int org, int dest, int* distantzia, int* aurrekoa, ptrMugi* burua)
{
	for (int i = 0; i < pKop; i++)
		if (i == dest) {
			printf("\nDistance of node %d = %d", i + 1, *(distantzia + i));
			mugimenduak(i + 1, burua);

			int j = i;
			do {
				j = *(aurrekoa + j);
				mugimenduak(j + 1, burua);
			} while (j != org);
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