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

#define MUGIT_IMAGE "../Media/Images/mugit.bmp" // Robota
#define MENU_IMAGE "../Media/Images/Menu.bmp" // Menu nagusiaren irudia
#define FILE_IMAGE "../Media/Images/helbidea.bmp" // Fitxategia eskatzeko menuaren irudia
#define MAP_IMAGE "../Media/Images/irudia.bmp" // Maparen irudia eskatzeko menuaren irudia
#define DIM_IMAGE "../Media/Images/MapaSortu.bmp" // Dimentsioak eskatzeko menuaren irudia

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

// ptrMugi motako aldagaiak
void askatuMugitu(ptrMugi* burua);
// ptrPuntua motako aldagaiak askatu
void askatuPuntuak(ptrPuntua* burua);
// Matriz baten memoria erreserba egin
int erreserbaBurutu(float** bek, int kop);
// Puntu bat bilatu eta haren koordenatuak jaso
void bilatu(ptrPuntua burua, float* x, float* y, int id);
// Irudi bat sortu
int irudiaSortu(float x, float y, char* name, SDL_Window* window);

#endif