#ifndef DIJKSTRA
#define DIJKSTRA

#define INFINITY 9999
#define MAX 20

typedef struct A_MUGIMENDUA
{
	int moveId;
	struct A_MUGIMENDUA* ptrHurrengoa;
} MUGI, * ptrMugi;

void hasieratu(int puntuKop, int org, int* kop, int distantzia[MAX], int aurrekoa[MAX], int check[MAX], int pisua[MAX][MAX]);
void gorde(int puntuKop, int org, int dest, int distantzia[MAX], int aurrekoa[MAX], ptrMugi* burua);
void dijkstra(int G[MAX][MAX], int puntuKop, int org, int dest, ptrMugi* burua);
void dijkstraTaula(int G[MAX][MAX], int pisua[MAX][MAX], int puntuKop);
void mugimenduak(int mugimendua, ptrMugi* burua);

#endif