#ifndef ERABILGARRIAK
#define ERABILGARRIAK
#include "SDL.h"
#include "SDL_ttf.h"

#define MAX_SIZE 128
#define INFINITO 9999

#define WIDTH 1109
#define HEIGHT 680

#define IN 0
#define OUT 1
#define TERMINATE -1
SDL_Renderer* renderer;

#define MUGIT_IMAGE "../Media/Images/mugit.bmp"
#define MENU_IMAGE "../Media/Images/Menu.bmp"
#define FILE_IMAGE "../Media/Images/helbidea.bmp"
#define MAP_IMAGE "../Media/Images/irudia.bmp"

typedef struct DE_DIMENTSIOA
{
	long width;
	long height;
} DIM;

typedef struct DE_POSIZIOA
{
	float x;
	float y;
} POS;

typedef struct DE_PUNTUA
{
	int id;
	POS pos;
	int visitado;
	struct DE_PUNTUA* ptrHurrengoa;
} PUNTUA, * ptrPuntua;

typedef struct A_MUGIMENDUA
{
	int moveId;
	struct A_MUGIMENDUA* ptrHurrengoa;
} MUGI, * ptrMugi;

void askatuMugitu(ptrMugi* burua);
void askatuPuntuak(ptrPuntua* burua);
int erreserbaBurutu(float** bek, int kop);
void bilatu(ptrPuntua burua, float* x, float* y, int id);
int irudiaSortu(float x, float y, char* name, SDL_Window* window);

#endif