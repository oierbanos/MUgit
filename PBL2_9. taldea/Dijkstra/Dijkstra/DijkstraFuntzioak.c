#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"

void dijkstra(int G[MAX][MAX], int puntuKop, int org, int dest, ptrMugi* burua)
{

	int pisua[MAX][MAX], distantzia[MAX], aurrekoa[MAX];
	int check[MAX], kop, minLuzeera, hurrengoa;

	// Aurrekoa nodo bakoitzaren aurrekoa gordetzen du
	// kop begiratutako nodo kopurua kontrolatzen du

	// Dijkstraren taula sortu
	dijkstraTaula(G, pisua, puntuKop);

	// hasieratu aurrekoa, distantzia eta check
	hasieratu(puntuKop, org, &kop, distantzia, aurrekoa, check, pisua);

	while (kop < puntuKop - 1) {
		minLuzeera = INFINITY;

		// 'hurrengoa'-k gertuen dagoen nodoa ematen du
		for (int i = 0; i < puntuKop; i++)
			if (distantzia[i] < minLuzeera && !check[i]) {
				minLuzeera = distantzia[i];
				hurrengoa = i;
			}

		// beste nodoak erabiliz bide motzen bat dagoen begiratu
		check[hurrengoa] = 1;
		for (int i = 0; i < puntuKop; i++)
			if (!check[i])
				if (minLuzeera + pisua[hurrengoa][i] < distantzia[i]) {
					distantzia[i] = minLuzeera + pisua[hurrengoa][i];
					aurrekoa[i] = hurrengoa;
				}
		kop++;
	}

	// Nodo batetik besterako distantziak kate batean gorde
	gorde(puntuKop, org, dest, distantzia, aurrekoa, burua);
}

void dijkstraTaula(int G[MAX][MAX], int pisua[MAX][MAX], int puntuKop)
{
	for (int i = 0; i < puntuKop; i++)
		for (int j = 0; j < puntuKop; j++)
			if (G[i][j] == 0)
				pisua[i][j] = INFINITY;
			else
				pisua[i][j] = G[i][j];
}

void hasieratu(int puntuKop, int org, int* kop, int distantzia[MAX], int aurrekoa[MAX], int check[MAX], int pisua[MAX][MAX])
{
	for (int i = 0; i < puntuKop; i++) {
		distantzia[i] = pisua[org][i];
		aurrekoa[i] = org;
		check[i] = 0;
	}
	distantzia[org] = 0;
	check[org] = 1;
	*kop = 1;
}

void gorde(int puntuKop, int org, int dest, int distantzia[MAX], int aurrekoa[MAX], ptrMugi* burua)
{
	for (int i = 0; i < puntuKop; i++)
		if (i == dest) {
			printf("\nDistance of node %d = %d", i + 1, distantzia[i]);
			mugimenduak(i + 1, burua);

			int j = i;
			do {
				j = aurrekoa[j];
				mugimenduak(j + 1, burua);
			} while (j != org);
		}
}

void mugimenduak(int mugimendua, ptrMugi* burua)
{
	ptrMugi ptrAux = *burua, berria;

	berria = (ptrMugi)malloc(sizeof(MUGI));
	if (berria == NULL) printf("Arazo bat egon da memoria alokatzerakoan.\n");
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