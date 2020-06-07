#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Menu.h"
#include "bitMap.h"
#include "Dijkstra.h"
#include "Erabilgarriak.h"
#include "Fitxategian_Idatzi.h"
#include "Fitxategia_Irakurri.h"

void fitxategiBatSortu(MP* points, int pkop, DIM mapDim)
{
	FILE* fitxategia;
	float *distantzia;
	int egoera;

	distantzia = (float*)malloc(sizeof(float) * pkop * pkop);
	if (distantzia == NULL) printf("#202 Errorea\n");

	// Jasotako puntu kopurua 0 baino txikiagoa bada ez da mapa gordeko
	if (pkop < 2 || distantzia == NULL) printf("#203 Errorea\n");
	else {
		fitxategiaSortu(&fitxategia);
		egoera = dimentsioakIdatzi(fitxategia, mapDim); // Maparen dimentsioak gorde
		if (egoera == 1) egoera = puntuakIdatzi(fitxategia, points, pkop, distantzia); // Puntuen id-a eta koordenatuak gorde
		if (egoera == 1) distantziakIdatzi(fitxategia, pkop, distantzia); // Puntuen arteko distantzien matrizea gorde
		fclose(fitxategia);
	}
}

void fitxategiaSortu(FILE** fitxategia)
{
	char fitxIzena[MAX_SIZE] = "", konprobaketa[MAX_SIZE];

	getTextFromUser(fitxIzena, "Get File", 450, 563, FILE_IMAGE);
	if (strlen(fitxIzena) >= 4) { // Konprobatu fitxategia ".map" batekin amaitzen den, horrela amaitzen ez bada ".map" amaiera bat jarri
		sprintf(konprobaketa, "%s", (fitxIzena + strlen(fitxIzena) - 4)); // Konprobatu ".map" jarrita dagoen
		if (strcmp(konprobaketa, ".map") != 0 && strlen(fitxIzena) <= MAX_SIZE - strlen(".map")) sprintf(fitxIzena, "%s.map", fitxIzena);
		else if (strcmp(konprobaketa, ".map") != 0) printf("#204 Errorea\n");
	}
	else sprintf(fitxIzena, "%s.map", fitxIzena); // Txikiegia baldin bada ".map" bat izateko, ".map"-a jarri

	*fitxategia = fopen(fitxIzena, "wb");
}

int dimentsioakIdatzi(FILE* fitxategia, DIM mapDim)
{
	int egoera;

	egoera = fwrite(&mapDim, sizeof(DIM), 1, fitxategia);
	if (egoera != 1) printf("#205. Errorea\n");

	return egoera;
}


int puntuakIdatzi(FILE* fitxategia, MP* points, int kop, float* distantzia)
{
	int egoera, i = 1, stop = -1;

	do {
		egoera = fwrite(&i, sizeof(int), 1, fitxategia);
		if (egoera != 1) printf("#206 Errorea\n");
		else {
			egoera = fwrite(&(points + i - 1)->pos.x, sizeof(float), 1, fitxategia);
			if (egoera != 1) printf("#207 Errorea\n");
			else {
				egoera = fwrite(&(points + i - 1)->pos.y, sizeof(float), 1, fitxategia);
				if (egoera != 1) printf("#208 Errorea\n");
			}
		}
		i++;
	} while (egoera == 1 && i <= kop);

	if (egoera == 1) { // Puntuak amaitu direla konprobatzeko "-1" bat sartuko da fitxategian
		fwrite(&stop, sizeof(int), 1, fitxategia);
		kalkulatuDistantzia(distantzia, points, kop);
	}
	else printf("#209 Errorea\n");

	return egoera;
}

void kalkulatuDistantzia(float* distantzia, MP* points, int kop) 
{
	int j, i;

	for (i = 0; i < kop; i++) // Matrize osoa "0"-ra jarri
		for (j = 0; j < kop; j++)
			*(distantzia + i * kop + j) = 0;

	for (i = 0; i < kop; i++) {
		j = 0;
		while ((points + i)->konexioak[j] != -1) { // konektatuta dauden puntuen artean pitagoras aplikatu, distantziak jakiteko
			*(distantzia + i * kop + (points + i)->konexioak[j]) = pitagoras(points, i, (points + i)->konexioak[j]);
			j++;
		}
	}
}

float pitagoras(MP* points, int zutabea, int lerroa)
{
	return (float)(sqrt((double)(((points + zutabea)->pos.x - (points + lerroa)->pos.x) * ((points + zutabea)->pos.x - (points + lerroa)->pos.x) + ((points + zutabea)->pos.y - (points + lerroa)->pos.y) * ((points + zutabea)->pos.y - (points + lerroa)->pos.y))));
}

void distantziakIdatzi(FILE* fitxategia, int kop, float* distantziak)
{
	int i = 0, j, egoera;

	do {
		j = 0;
		do {
			egoera = fwrite((distantziak + i * kop + j), sizeof(float), 1, fitxategia);
			j++;
		} while (j < kop && egoera == 1);
		i++;
	} while (i < kop && egoera == 1);
	if (egoera != 1) printf("#Error 210\n");
}