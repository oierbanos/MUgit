#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX 20

typedef struct A_MUGIMENDUA 
{
	int moveId;
	struct A_MUGIMENDUA* ptrHurrengoa;
} MUGI, *ptrMugi;

void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode, ptrMugi* burua);
void movements(int mugimendua, ptrMugi* burua);
void pantailaratu(ptrMugi burua);
void askatu(ptrMugi* burua);

int main(int argc, char** argv)
{
	int G[MAX][MAX];
	int i, j, n, u, v;
	ptrMugi burua = NULL;

	printf("Enter no. of vertices: ");
	scanf("%d", &n);

	// Pisuen matrizea sartu
	printf("\nEnter the adjacency matrix:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			scanf("%d", &G[i][j]);
		printf("============================\n");
	}

	// Bidea Aurkitu
	printf("If you enter -1 as the starting node the program will end.\n");
	do {
		printf("Enter the starting node: ");
		scanf("%d", &u);
		if (u != -1) {
			printf("Enter the final node: ");
			scanf("%d", &v);
			dijkstra(G, n, u - 1, v - 1, &burua);
			printf("\n============================\n");
			pantailaratu(burua);
			askatu(&burua);
			burua = NULL;
			printf("\n============================\n");
		}
		printf("\n");
	} while (u != -1);

	return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode, ptrMugi* burua)
{

	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];

	//initialize pred[],distance[] and visited[]
	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count < n - 1)
	{
		mindistance = INFINITY;

		//nextnode gives the node at minimum distance
		for (i = 0; i < n; i++)
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}

		//check if a better path exists through nextnode			
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}

	//print the path and distance of each node
	for (i = 0; i < n; i++)
		if (i == endnode)
		{
			printf("\nDistance of node %d = %d", i + 1, distance[i]);
			printf("\nPath = %d", i + 1);
			movements(i + 1, burua);

			j = i;
			do {
				j = pred[j];
				printf("<-%d", j + 1);
				movements(j + 1, burua);
			} while (j != startnode);
		}
}

void movements(int mugimendua, ptrMugi* burua)
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