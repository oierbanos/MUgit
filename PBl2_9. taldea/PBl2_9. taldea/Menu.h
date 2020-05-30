#ifndef MENU
#define MENU
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"

int hasieratu(SDL_Window** window, SDL_Renderer** renderer, int width, int height, char* name);
int aukeraMenu(SDL_Event ebentu, FILE** fitxategia, ptrPuntua* burua, ptrMugi* mBurua, int** Grafo, char* fileName, char* mapName, DIM mapDim);
int checkArea(float x, float y, float xDistance, float yDistance, SDL_Event ebentu);
int textuaPantailanIdatzi(char* title, char* input, int x, int y);
int getTextFromUser(char* input, char* title, char* windowName);
void textuaIdatzi(int x, int y, char* str);
SDL_Renderer* getRenderer(void);
void textuaGaitu(int aukera);
void closeFont(void);

#endif