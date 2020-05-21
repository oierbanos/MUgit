#ifndef SAVE_IN_A_FILE
#define SAVE_IN_A_FILE
#include <stdlib.h>

#define MAX_STR 128

void puntuKopurua(int* kop);
void fitxategiaSortu(FILE** fitxategia);
void puntuakIdatzi(FILE* fitxategia, int kop);
void pisuenMatrizeaIdatzi(FILE* fitxategia, int kop);

#endif