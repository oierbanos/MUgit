#ifndef READ_A_FILE
#define READ_A_FILE
#include <stdlib.h>
#include "Erabilgarriak.h"

int fitxategiaIreki(FILE** fitxategia);
void fitxategiaJaso(FILE** fitxategia);
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
void pisuakJaso(ptrPuntua burua, FILE* fitxategia, int** pisuak);
int puntuakZenbatu(ptrPuntua burua);
void pantailaratuPuntuak(ptrPuntua burua);

#endif