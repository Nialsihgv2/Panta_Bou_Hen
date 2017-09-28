#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <time.h>
#include "fonct.h"

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *bcgr, *texte;
  SDL_Rect position;
  int gameover;
  time_t debut, progress;
  int temps;
  char *t_str;
  TTF_Font *police;
  SDL_Color couleurNoire = {0, 0, 0};

  t_str=(char *)malloc(sizeof(char)*50);
  
  /* initialize video system */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Pentamino", "Pentamino");

  TTF_Init();


  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* load background */
  temp  = SDL_LoadBMP("backgr.bmp");
  bcgr = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  police = TTF_OpenFont("Colleged.ttf",65);
  
  gameover = 0;
  debut = time(NULL);
  /* main loop: check events and re-draw the window until the end */
  while (!gameover)
    {
      progress = time(NULL);
      temps = difftime(progress, debut);
      sprintf(t_str, "%d:%d", temps/60, temps%60);
      texte = TTF_RenderText_Blended(police, t_str,
				     couleurNoire);

      SDL_Event event;
      
      /* look for an event */
      if (SDL_PollEvent(&event)) {
	/* an event was found */
	switch (event.type) {
	  /* close button clicked */
	case SDL_QUIT:
	  gameover = 1;
	  break;
	  
	  /* handle the keyboard */
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    gameover = 1;
	    break;
	  default:
	    break;
	  }
	  break;
	}
      }
      
      /* Draw the background */
      SDL_BlitSurface(bcgr, NULL, screen, NULL);
      
      position.x = 0;
      position.y = 0;
      SDL_BlitSurface(texte, NULL, screen, &position);
      
      /* update the screen */
      SDL_UpdateRect(screen,0,0,0,0);
    }
  
  /* clean up */
  SDL_FreeSurface(bcgr);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_Quit();
  
  return 0;
}
