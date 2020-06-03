#ifndef DIJKSTRA
#define DIJKSTRA
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"

void hasieratuDijkstra(int pKop, int org, int* kop, float* distantzia, float* aurrekoa, float* check, float* pisua);
void gorde(int pKop, int org, int dest, float* distantzia, float* aurrekoa, ptrMugi* burua);
void setUp(FILE* fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, int pos1, int pos2);
void dijkstra(float* pisuak, int pKop, int org, int dest, ptrMugi* burua);
void dijkstraTaula(float* pisuak, float* pisua, int pKop);
void mugimenduak(int mugimendua, ptrMugi* burua);

#endif