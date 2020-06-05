#ifndef MENU
#define MENU
#include "SDL.h"
#include "SDL_ttf.h"
#include "Erabilgarriak.h"
#include "bitMap.h"

// Letra mota ezabatu
void closeFont(void);
// Letra mota bat jaso
void textuaGaitu(int aukera);
// Renderer bat jaso
SDL_Renderer* getRenderer(void);
// Textua pantailan idatzi
void textuaIdatzi(int x, int y, char* str);
// Erabiltzaileak idazten duen textua pantailan jarri
int textuaPantailanIdatzi(char* input, int x, int y);
//Toki zehatz batean klik egin den konprobatu
int checkArea(float x, float y, float xDistance, float yDistance, SDL_Event ebentu);
// Erabiltzaileak sartzen duen textua jaso
int getTextFromUser(char* input, char* windowName, int width, int height, char* image);
// Lehio berri bat sortu
int hasieratu(SDL_Window** window, SDL_Renderer** renderer, int width, int height, char* name);
// Menu nagusiaren aukera desberdinak
int aukeraMenu(SDL_Event ebentu, FILE** fitxategia, ptrPuntua* burua, ptrMugi* mBurua, float** pisuak, char* fileName, char* mapName, DIM* mapDim, MP* points, int* pkop);

#endif