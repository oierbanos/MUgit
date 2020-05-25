#ifndef TEXT
#define TEXT
#include "SDL.h"
#include "SDL_ttf.h"

#define IN 0
#define OUT 1
#define TERMINATE -1
SDL_Renderer* renderer;

int hasieratu(SDL_Window** window, SDL_Renderer** renderer, int width, int height, char* name);
int textuaPantailanIdatzi(char* title, char* input, int x, int y);
int getTextFromUser(char* input, char* title, char* windowName);
void textuaIdatzi(int x, int y, char* str);
void textuaGaitu(int aukera);

#endif