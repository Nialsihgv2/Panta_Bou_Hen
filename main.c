#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "fonct.h"

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *bcgr, *texte;
  SDL_Rect position;
  int gameover;
  time_t start, in_time;
  int t_int, min, sec;
  char *t_str;
  TTF_Font *police;
  SDL_Color couleurNoire = {0, 0, 0};
  piece_t* p_l;
  SDL_Event event;
  Uint32 startT;
  p_l=(piece_t*)malloc(sizeof(piece_t));
  init_piece(p_l);
  p_l->flip = false;

  t_str=(char *)malloc(sizeof(char)*50);
  
  /* initialize video system */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Pentomino", "Pentomino");

  TTF_Init();
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* load background */
  temp  = SDL_LoadBMP("backgr.bmp");
  bcgr = SDL_DisplayFormatAlpha(temp);
  SDL_FreeSurface(temp);
  
  police = TTF_OpenFont("BlockoBit.ttf",65);
  
  gameover = 0;
  /* main loop: check events and re-draw the window until the end */
  start = time(NULL);
  while (!gameover)
    {
      startT = SDL_GetTicks();
      if(SDL_GetTicks()-startT < 1000/60){
	SDL_Delay((1000/60)-(SDL_GetTicks()-startT));
      }
      in_time = time(NULL);
      t_int = difftime(in_time, start);
      min = (t_int / 60) % 100;
      sec = t_int % 60;
      sprintf(t_str, "%d%d:%d%d",min/10,min%10,sec/10,sec%10);
      texte = TTF_RenderText_Blended(police, t_str,
				     couleurNoire);

      
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
      
      position.x = TIMER_POS_X;
      position.y = TIMER_POS_Y;
      SDL_BlitSurface(texte, NULL, screen, &position);
      
      /* update the screen */
      SDL_UpdateRect(screen,0,0,0,0);
      SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    }
  
  /* clean up */
  free_piece(p_l);
  free(p_l);
  SDL_FreeSurface(bcgr);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_Quit();
  
  return 0;
}
