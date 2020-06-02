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

union ulong_char_union {
	long l_num;
	char l_alpha[4];
};

struct bitmapheader {
	unsigned long size;
	long width;
	long height;
};

struct tiff_header_struct {
	short lsb;
	long bits_per_pixel;
	long image_length;
	long image_width;
	long strip_offset;
};

union long_char_union {
	long l_num;
	char l_alpha[4];
};

void askatuMugitu(ptrMugi* burua);
void askatuPuntuak(ptrPuntua* burua);
int erreserbaBurutu(float** bek, int kop);
void bilatu(ptrPuntua burua, float* x, float* y, int id);
void get_image_size(char* file_name, long* rows, long* cols);
int irudiaSortu(float x, float y, char* name, SDL_Window* window);
void read_bm_header(char* file_name, struct bitmapheader* bmheader);
void extract_long_from_buffer(char* buffer, int lsb, int start, long* number);
void extract_ulong_from_buffer(char* buffer, int lsb, int start, unsigned long* number);

#endif