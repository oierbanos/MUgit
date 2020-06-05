#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Fitxategia_Irakurri.h"
#include "Erabilgarriak.h"
#include "imagen.h"

int erreserbaBurutu(float** bek, int kop) // Bektore baten erreserba egin
{
	*bek = (float*)malloc(sizeof(float) * kop);
	if (*bek == NULL) {
		printf("#103 Errorea\n");
		return 0;
	}
	else return 1;
}

void bilatu(ptrPuntua burua, float* x, float* y, int id) { // Puntu bat bilatu eta haren koordenatuak jaso

	ptrPuntua ptrAux = burua;
	
	while (ptrAux->id != id && ptrAux->ptrHurrengoa != NULL) 
		ptrAux = ptrAux->ptrHurrengoa;
	*x = ptrAux->pos.x;
	*y = ptrAux->pos.y;
}

void askatuPuntuak(ptrPuntua* burua) // ptrPuntua motako aldagaiak askatu
{
	ptrPuntua aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL) {
			*burua = (*burua)->ptrHurrengoa;
			free(aux);
			aux = *burua;
		}
	}
	*burua = NULL;
}

void askatuMugitu(ptrMugi* burua) // ptrMugi motako aldagaiak askatu
{
	ptrMugi aux = *burua;

	if (*burua != NULL) {
		while (*burua != NULL) {
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
	if (bmpID != -1) {
		irudiaMugitu(bmpID, x, y);
		irudiakMarraztu();
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}
	else printf("#102 Errorea\n");

	return bmpID;
}