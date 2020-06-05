#ifndef BITMAP
#define BITMAP
#include "Erabilgarriak.h"

typedef struct DE_MAP_POINTS 
{
	POS pos;
	int* konexioak;
} MP;

// Irudiaren helbidea eskatu
void eskatuIrudia(char* img);
// Maparen dimentsioak eskatu eta irudi bat sartu nahi den galdetu
DIM eskatuDimentsioak(char* aukera);
// Puntu bat beste puntuekin dituen konexioak ID-aren bitartez txikitik handira ordenatu
void ordenatu(MP* points, int pkop);
// Konexio guztiak "-1"-era jarri
void hasieratuKonexioak(MP* points, int pkop);
// Bi puntuen arteko konexioa sorut
void konektatu(MP** points, int org, int dest);
// Maparen grafoa irudikatu
void bitmap(MP** points, int* pkop, DIM* mapDim);
// Puntu batean klikatu den konprobatu (puntu guztietan zehar puntu bat bilatuz)
int checkPlace(MP* points, int kont, SDL_Event ebentu);
// Irudiaren dimentsioak eskatzerakoan erabiltzaileak idazten duena pantailan idatzi
void aukeraJaso(SDL_Event ebentu, int* option, char* input);
// Puntu berri baten koordenatuak gorde
void koordenatuakGorde(MP** points, int* kont, float mouseX, float mouseY);

#endif