#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"
#include "imagen.h"

int erreserbaBurutu(float** bek, int kop)
{
	*bek = (float*)malloc(sizeof(float) * kop);
	if (*bek == NULL) return 0;
	else return 1;
}

void bilatu(ptrPuntua burua, float* x, float* y, int id) {

	ptrPuntua ptrAux = burua;
	
	while (ptrAux->id != id && ptrAux->ptrHurrengoa != NULL) ptrAux = ptrAux->ptrHurrengoa;

	*x = ptrAux->pos.x;
	*y = ptrAux->pos.y;
}

void askatuPuntuak(ptrPuntua* burua)
{
	ptrPuntua aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL)
		{
			*burua = (*burua)->ptrHurrengoa;
			free(aux);
			aux = *burua;
		}
	}
	*burua = NULL;
}

void askatuMugitu(ptrMugi* burua)
{
	ptrMugi aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL)
		{
			*burua = (*burua)->ptrHurrengoa;
			free(aux);
			aux = *burua;
		}
	}
	*burua = NULL;
}

int irudiaSortu(float x, float y, char* name, SDL_Window* window)
{
	int bmpID = -1;

	bmpID = irudiaKargatu(name);
	irudiaMugitu(bmpID, x, y);
	irudiakMarraztu();
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);

	return bmpID;
}

void get_image_size(char* file_name, long* rows, long* cols)
{
	struct bitmapheader bmph;
	int egoera;

	egoera = read_bm_header(file_name, &bmph);
	if (egoera == 1) {
		*rows = bmph.height;
		*cols = bmph.width;
	}
}

int read_bm_header(char* file_name, struct bitmapheader* bmheader)
{
	char buffer[10];
	long ll;
	unsigned long ull;
	FILE* fitxategia;

	fitxategia = fopen(file_name, "rb");
	if (fitxategia != NULL) {
		fseek(fitxategia, 14, SEEK_SET);

		fread(buffer, 1, 4, fitxategia);
		extract_ulong_from_buffer(buffer, 1, 0, &ull);
		bmheader->size = ull;

		fread(buffer, 1, 4, fitxategia);
		extract_long_from_buffer(buffer, 1, 0, &ll);
		bmheader->width = ll;

		fread(buffer, 1, 4, fitxategia);
		extract_long_from_buffer(buffer, 1, 0, &ll);
		bmheader->height = ll;

		return 1;
	}
	else return 0;
}

void extract_long_from_buffer(char* buffer, int lsb, int start, long* number)
{
	union long_char_union lcu = { lcu.l_num = 0 };

	lcu.l_alpha[0] = buffer[start + 0];
	lcu.l_alpha[1] = buffer[start + 1];
	lcu.l_alpha[2] = buffer[start + 2];
	lcu.l_alpha[3] = buffer[start + 3];
	*number = lcu.l_num;
}

void extract_ulong_from_buffer(char* buffer, int  lsb, int start, unsigned long* number)
{
	union ulong_char_union lcu = { lcu.l_num = 0 };

	lcu.l_alpha[0] = buffer[start + 0];
	lcu.l_alpha[1] = buffer[start + 1];
	lcu.l_alpha[2] = buffer[start + 2];
	lcu.l_alpha[3] = buffer[start + 3];
	*number = lcu.l_num;
}
