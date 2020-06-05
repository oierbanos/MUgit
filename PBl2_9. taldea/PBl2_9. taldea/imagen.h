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

void irudiaKendu(int id);
void irudiakMarraztu(void);
int  irudiaKargatu(char* fileName);
int irudiarenPosizioaAurkitu(int id);
void  irudiaMugitu(int numImg, float x, float y);

#endif
