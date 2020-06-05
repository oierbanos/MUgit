#ifndef DIJKSTRA
#define DIJKSTRA
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"

// Puntu batetik bestera mugitzeko zeharkatu behar diren puntuak gorde
void mugimenduak(int mugimendua, ptrMugi* burua);
// Dijkstrak erabiltzen duen taula kalkulatu
void dijkstraTaula(float* pisuak, float* pisua, int pKop);
// Dijkstra kalkulatu
void dijkstra(float* pisuak, int pKop, int org, int dest, ptrMugi* burua);
// Robotak egin behar dituen mugimenduak gorde
void gorde(int pKop, int org, int dest, float* distantzia, float* aurrekoa, ptrMugi* burua);
// Dijkstra aplikatzeko prestatu
void setUp(FILE* fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, int pos1, int pos2);
// Dijkstrak erabili behar dituen hainbat elementu hasieratu
void hasieratuDijkstra(int pKop, int org, int* kop, float* distantzia, float* aurrekoa, float* check, float* pisua);

#endif