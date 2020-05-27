#ifndef MENU
#define MENU
#include "SDL.h"
#include "SDL_ttf.h"

int hasieratu(SDL_Window** window, SDL_Renderer** renderer, int width, int height, char* name);
int aukeraMenu(SDL_Event ebentu, char* fileName, char* mapName, DIM mapDim);
int checkArea(int x, int y, int xDistance, int yDistance, SDL_Event ebentu);
int textuaPantailanIdatzi(char* title, char* input, int x, int y);
int getTextFromUser(char* input, char* title, char* windowName);
void textuaIdatzi(int x, int y, char* str);
void textuaGaitu(int aukera);

#endif