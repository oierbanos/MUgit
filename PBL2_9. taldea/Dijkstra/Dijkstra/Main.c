#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Erabilgarriak.h"

int main(int argc, char** argv)
{
	int G[MAX][MAX];
	int puntuKop, org, dest;
	ptrMugi burua = NULL;

	printf("Enter no. of vertices: ");
	scanf("%d", &puntuKop);

	// Pisuen matrizea sartu
	printf("\nEnter the adjacency matrix:\n");
	for (int i = 0; i < puntuKop; i++) {
		for (int j = 0; j < puntuKop; j++)
			scanf("%d", &G[i][j]);
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

			dijkstra(G, puntuKop, org - 1, dest - 1, &burua);

			printf("\n============================\n");
			pantailaratu(burua);
			askatu(&burua);
			burua = NULL;
			printf("\n============================\n");
		}
		printf("\n");
	} while (org != -1);

	return 0;
}