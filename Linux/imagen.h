#ifndef IMAGEN_H
#define IMAGEN_H

#define MAX_IMG 10

typedef struct Img
{
	int id;
	SDL_Surface* imagen;
	SDL_Texture* texture;
	SDL_Rect dest;
}IMG;

// Kargatuta dagoen irudi bat ezabatu
void irudiaKendu(int id);
// Irudia pantaila marraztu
void irudiakMarraztu(void);
// Irudi bat kargatu
int  irudiaKargatu(char* fileName);
// Irudi batek ezarrita duen ID-a aurkitu
int irudiarenPosizioaAurkitu(int id);
// Irudi bat posizio berri batera mugitu
void  irudiaMugitu(int numImg, float x, float y);

#endif
