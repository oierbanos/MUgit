#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileReading.h"

// Funtzio orokorra
int main(int argc, char** argv)
{
	FILE* fitxategia;
	ptrPuntua burua = NULL;
	int* pisuak;

	fitxategiaJaso(&fitxategia);
	if (fitxategia != NULL) {
		puntuakJaso(&burua, fitxategia);
		printf("\nPuntuen koordenatuak:\n"); pantailaratu(burua);
		printf("Puntuen arteko pisua:\n"); pisuakJaso(burua, fitxategia, &pisuak);

		askatu(burua);
		fclose(fitxategia);
	}
}