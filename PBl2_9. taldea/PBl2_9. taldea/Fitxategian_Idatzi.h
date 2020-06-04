#ifndef SAVE_IN_A_FILE
#define SAVE_IN_A_FILE
#include <stdlib.h>
#include "bitMap.h"

void fitxategiaSortu(FILE** fitxategia);
void dimentsioakIdatzi(FILE* fitxategia, DIM mapDim);
float pitagoras(MP* points, int zutabea, int lerroa);
void fitxategiBatSortu(MP* points, int pkop, DIM mapDim);
void kalkulatuDistantzia(float* distantzia, MP* points, int kop);
void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak);
void puntuakIdatzi(FILE* fitxategia, MP* points, int kop, float* distantzia);

#endif