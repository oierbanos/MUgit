#ifndef ERABILGARRIAK
#define ERABILGARRIAK

#define MAX_SIZE 128
#define INFINITY 9999

typedef struct DE_POSIZIOA
{
	int x;
	int y;
} POS;

typedef struct DE_PUNTUA
{
	int id;
	POS pos;
	struct DE_PUNTUA* ptrHurrengoa;
} PUNTUA, * ptrPuntua;

typedef struct A_MUGIMENDUA
{
	int moveId;
	struct A_MUGIMENDUA* ptrHurrengoa;
} MUGI, * ptrMugi;

int menu(void);
int erreserbaBurutu(int** bek, int kop);
void pantailaratuBidea(ptrMugi burua);
void askatuMugitu(ptrMugi* burua);
void askatuPuntuak(ptrPuntua* burua);

#endif