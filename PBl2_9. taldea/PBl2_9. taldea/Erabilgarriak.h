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

typedef struct DE_DIMENTSIOA
{
	int width;
	int height;
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

int menu(void);
int erreserbaBurutu(int** bek, int kop);
void askatuMugitu(ptrMugi* burua);
void askatuPuntuak(ptrPuntua* burua);
void bilatu(ptrPuntua* burua2, float* x, float* y, int id);

#endif