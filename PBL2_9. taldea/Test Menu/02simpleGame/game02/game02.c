#include "game02.h"
#include "imagen.h"
#include "graphics.h"
#include "ebentoak.h"
#include "text.h"
#include "soinua.h"
#include <stdio.h>
#include <windows.h>

#define BACKGROUND_IMAGE "img/Mapas/Mapa_Nivel_1.bmp"
#define FONDO_INCIO ".\\img\\Pantallas\\inicio.bmp"


int jokoaAurkeztu(void)
{
    // Hasierako menuaren argazkia jarri
    int ebentu = 0, idFONDOINICIO;
    idFONDOINICIO = HASIERA_irudiaBistaratu();
    // Ebentu baten zain egon
    do
    {
        ebentu = ebentuaJasoGertatuBada();
    } while (ebentu != SAGU_BOTOIA_EZKERRA && ebentu != TECLA_ESCAPE && ebentu != GERTAERA_IRTEN);
    // Hasierako menuaren irudia kendu
    pantailaGarbitu();
    irudiaKendu(idFONDOINICIO);
    pantailaBerriztu();
    return ebentu;
}

int HASIERA_irudiaBistaratu()
{
    int id = -1;
    id = irudiaKargatu(FONDO_INCIO);
    irudiaMugitu(id, 0, 0);
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}
//Maparen irudia bistaratzen duen funtzioa
int FONDOA_irudiaBistaratu()
{
    int fondo = -1;
    fondo = irudiaKargatu(BACKGROUND_IMAGE);
    irudiaMugitu(fondo, 0, 0);
    pantailaGarbitu();
    irudiakMarraztu();
    pantailaBerriztu();
    return fondo;
}