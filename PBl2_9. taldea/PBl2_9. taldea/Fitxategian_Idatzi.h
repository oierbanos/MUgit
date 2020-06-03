#ifndef SAVE_IN_A_FILE
#define SAVE_IN_A_FILE
#include <stdlib.h>
#include "bitMap.h"

void fitxategiaSortu(FILE** fitxategia);
void fitxategiBatSortu(MP* points, int pkop);
float pitagoras(MP* points, int zutabea, int lerroa);
void kalkulatuDistantzia(float* distantzia, MP* points, int kop);
void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak);
void puntuakIdatzi(FILE* fitxategia, MP* points, int kop, float* distantzia);

#endif