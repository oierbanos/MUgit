#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"
#include "SDL.h"
#include "SDL_ttf.h"

// Funtzio orokorra
int main(int argc, char** argv)
{
	char input[128] = "";
	int egoera;

	egoera = getTextFromUser(input, "Fitxategiaren Helbidea", "Get File");
	if (egoera == OUT) printf("Helbidea: %s\n", input);
	strcat(input, "");
	egoera = getTextFromUser(input, "Irudiaren Helbidea", "Get Map");
	if (egoera == OUT) printf("Helbidea: %s\n", input);

	return 0;
}