#ifndef SAVE_IN_A_FILE
#define SAVE_IN_A_FILE
#include <stdlib.h>
#include "bitMap.h"

// Mapa gordeko duen fitxategia sortu
void fitxategiaSortu(FILE** fitxategia);
// Maparen dimentsioak fitxategian gorde
int dimentsioakIdatzi(FILE* fitxategia, DIM mapDim);
// Pitagoras kalkulatu
float pitagoras(MP* points, int zutabea, int lerroa);
// Fitxategiko pauso guztiak aurrera eraman
void fitxategiBatSortu(MP* points, int pkop, DIM mapDim);
// Puntuen arteko distantziak kalkulatu (Puntuak lotuta badaude)
void kalkulatuDistantzia(float* distantzia, MP* points, int kop);
// Puntuen arteko distantziak fitxategian idatzi
void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak);
// Puntuen koordenatuak eta ID-a fitxategian gorde
int puntuakIdatzi(FILE* fitxategia, MP* points, int kop, float* distantzia);

#endif