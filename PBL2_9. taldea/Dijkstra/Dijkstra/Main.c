#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"

int main(int argc, char** argv)
{
	ptrMugi burua = NULL;
	int pKop, org, dest;
	int* Grafo = NULL;

	printf("Enter no. of vertices: ");
	scanf("%d", &pKop);

	if (!erreserbaBurutu(&Grafo, pKop * pKop)) printf("Arazo bat eman da memoria alokatzean.\n");
	else {
		// Pisuen matrizea sartu
		printf("\nEnter the adjacency matrix:\n");
		for (int i = 0; i < pKop; i++) {
			for (int j = 0; j < pKop; j++)
				scanf("%d", (Grafo + i * pKop + j));
			printf("============================\n");
		}

		// Bidea Aurkitu
		printf("If you enter -1 as the starting node the program will end.\n");
		do {
			printf("Enter the starting node: ");
			scanf("%d", &org);

			if (org != -1) {
				printf("Enter the final node: ");
				scanf("%d", &dest);

				dijkstra(Grafo, pKop, org - 1, dest - 1, &burua);

				printf("\n============================\n");
				pantailaratu(burua);
				askatu(&burua);
				burua = NULL;
				printf("\n============================\n");
			}
			printf("\n");
		} while (org != -1);
	}
}