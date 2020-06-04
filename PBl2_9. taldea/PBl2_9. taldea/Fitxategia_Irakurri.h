#ifndef READ_A_FILE
#define READ_A_FILE
#include <stdlib.h>
#include "Erabilgarriak.h"

int puntuakZenbatu(ptrPuntua burua);
void pantailaratuPuntuak(ptrPuntua burua);
void dimentsioakJaso(FILE* fitxategia, DIM* mapDim);
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
int fitxategiaIreki(FILE** fitxategia, char* fileName);
void pisuakJaso(ptrPuntua burua, FILE* fitxategia, float** pisuak);

#endif