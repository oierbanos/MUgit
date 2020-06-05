#ifndef READ_A_FILE
#define READ_A_FILE
#include <stdlib.h>
#include "Erabilgarriak.h"

// Puntu kopurua kalkulatu
int puntuakZenbatu(ptrPuntua burua);
// Maparen dimentsioak fitxategitik irakurri
void dimentsioakJaso(FILE* fitxategia, DIM* mapDim);
// Maparen puntuak fitxategitik irakurri
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
// Fitxategi bat eskatu eta hau ireki
int fitxategiaIreki(FILE** fitxategia, char* fileName);
// Puntuen arteko distantziak jaso
void pisuakJaso(ptrPuntua burua, FILE* fitxategia, float** pisuak);

#endif