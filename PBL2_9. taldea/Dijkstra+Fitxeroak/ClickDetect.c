#include "Erabilgarriak.h"
#include "ebentoak.h"
#include "ClickDetect.h"

int clickID(ptrPuntua burua, SDL_Event ebentu)
{
    ptrPuntua ptrAux = burua;
    int ret = 0;
 
    while (ptrAux != NULL)
    {
        if (checkArea(ptrAux->pos.x - 50, ptrAux->pos.y - 50, 50, 50, ebentu))
        {
            ret = ptrAux->id;
        }
        ptrAux = ptrAux->ptrHurrengoa;
    }
    return ret;
}

int checkArea(int x, int y, int xDistance, int yDistance, SDL_Event ebentu)
{
    int egoera = 0;

    if (ebentu.button.x >= x && ebentu.button.x <= x + xDistance && ebentu.button.y >= y && ebentu.button.y <= y + yDistance)
        egoera = 1;

    return egoera;
}