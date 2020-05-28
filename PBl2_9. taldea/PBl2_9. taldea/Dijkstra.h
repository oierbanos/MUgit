#ifndef DIJKSTRA
#define DIJKSTRA
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"

void hasieratuDijkstra(int pKop, int org, int* kop, int* distantzia, int* aurrekoa, int* check, int* pisua);
void gorde(int pKop, int org, int dest, int* distantzia, int* aurrekoa, ptrMugi* burua);
void setUp(FILE* fitxategia, ptrPuntua* burua, ptrMugi* mBurua, int** Grafo);
void dijkstra(int* Grafo, int pKop, int org, int dest, ptrMugi* burua);
void dijkstraTaula(int* Grafo, int* pisua, int pKop);
void mugimenduak(int mugimendua, ptrMugi* burua);

#endif