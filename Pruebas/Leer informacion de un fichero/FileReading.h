#ifndef READ_A_FILE
#define READ_A_FILE
#include <stdlib.h>

#define MAX_SIZE 128

typedef struct DE_POSIZIOA
{
	int x;
	int y;
} POS;

typedef struct DE_PUNTUA
{
	int id;
	POS pos;
	struct A_PESOS* ptrHurrengoa;
} PUNTUA, * ptrPuntua;

int fitxategiaIreki(FILE** fitxategia);
void fitxategiaJaso(FILE** fitxategia);
void puntuakJaso(ptrPuntua* burua, FILE* fitxategia);
void pisuakJaso(ptrPuntua burua, FILE* fitxategia, int** pisuak);
int puntuakZenbatu(ptrPuntua burua);
void pantailaratu(ptrPuntua burua);
void askatu(ptrPuntua burua);

#endif