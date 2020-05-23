//---------------------------------------------------------------------------------
#include "imagen.h"
#include "graphics.h"
#include "ebentoak.h"
#include "text.h"
#include "soinua.h"
//---------------------------------------------------------------------------------

#include <stdio.h>
#include "ourTypes.h"
#include "game02.h"

#define LOAD "img/Pantallas/logo.bmp"
#define WIDTH 1109  
#define HEIGHT 680

 int main(int argc, char * str[]) 
 {
  int jarraitu = 0, id = -1, ebentu = 0;
  POSIZIOA sagupos;
  //EGOERA egoera;
 
  if (sgHasieratu() == -1) 
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    return 1;
  }
  textuaGaitu(); 

  id = irudiaKargatu(LOAD);
  irudiaMugitu(id, 0, 0);
  irudiakMarraztu();
  pantailaBerriztu();
  // 800 milisegundu itxaron
  SDL_Delay(8000);
  // Loading pantailaren irudia kendu
  irudiaKendu(id);
  pantailaBerriztu();

  do
  {    
      ebentu = jokoaAurkeztu();
      // Saguaren posizioa detektatu
      sagupos = saguarenPosizioa();
      // Jolastu botoia
      if ((sagupos.x > 180) && (sagupos.x < 440) && (sagupos.y > 340) && (sagupos.y < 380) && (ebentu == SAGU_BOTOIA_EZKERRA))
      {
          //NADA
      }
      else
      {
          // Kredituen pantailan sartu
          if ((sagupos.x > 700) && (sagupos.x < 900) && (sagupos.y > 400) && (sagupos.y < 450) && (ebentu == SAGU_BOTOIA_EZKERRA))
          {
            //  kredituak();
          }
          // Jokoari buruzko pantailetan sartu
          else if ((sagupos.x > 660) && (sagupos.x < 960) && (sagupos.y > 290) && (sagupos.y < 350) && (ebentu == SAGU_BOTOIA_EZKERRA))
          {
              //howto();
          }
      }
  } while (ebentu != GERTAERA_IRTEN && ebentu != TECLA_ESCAPE);
  sgItxi();
  /*do
  {




    jokoaAurkeztu();
    egoera = jokatu();
    jarraitu = jokoAmaierakoa(egoera);
  } while (jarraitu);
  sgItxi();*/
  return 0;
}



