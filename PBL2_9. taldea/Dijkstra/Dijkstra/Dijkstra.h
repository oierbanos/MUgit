#ifndef DIJKSTRA
#define DIJKSTRA

#define INFINITY 9999
#define MAX 10

typedef struct A_MUGIMENDUA
{
	int moveId;
	struct A_MUGIMENDUA* ptrHurrengoa;
} MUGI, * ptrMugi;

void hasieratu(int pKop, int org, int* kop, int* distantzia, int* aurrekoa, int* check, int* pisua);
void gorde(int pKop, int org, int dest, int* distantzia, int* aurrekoa, ptrMugi* burua);
void dijkstra(int* Grafo, int pKop, int org, int dest, ptrMugi* burua);
void dijkstraTaula(int* Grafo, int* pisua, int pKop);
void mugimenduak(int mugimendua, ptrMugi* burua);

#endif