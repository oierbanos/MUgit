#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileWriting.h"

int main(int argc, char** argv)
{
	FILE* fitxategia;
	int kop;

	puntuKopurua(&kop);
	fitxategiaSortu(&fitxategia);
	puntuakIdatzi(fitxategia, kop);
	pisuenMatrizeaIdatzi(fitxategia, kop);
	printf("Informazioa gorde da.\n");
	fclose(fitxategia);
}