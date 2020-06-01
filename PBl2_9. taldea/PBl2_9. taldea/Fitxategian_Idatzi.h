#ifndef SAVE_IN_A_FILE
#define SAVE_IN_A_FILE
#include <stdlib.h>

void puntuKopurua(int* kop);
void fitxategiBatSortu(void);
int konexioa(int puntua1, int puntua2);
void fitxategiaSortu(FILE** fitxategia);
float pitagoras(POS* pPos, int zutabea, int lerroa);
void kalkulatuDistantzia(float* distantzia, POS* pPos, int kop);
void puntuakIdatzi(FILE* fitxategia, int kop, float* distantzia);
void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak);

#endif