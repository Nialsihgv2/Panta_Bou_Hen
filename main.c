#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "fonct.h"


int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *bcgr, *text, *title;
  SDL_Rect position,p_chrono,p_rect;
  int gameover, mod, mouse_state, chgt_st = 0;
  time_t start, in_time, t_temp;
  int t_int, min, sec;
  char *t_str;
  TTF_Font *font_timer, *font_title;
  SDL_Color black = {0, 0, 0};
  piece_t *p_l;
  Uint32 startT;
  FILE* txt = NULL;
  input_t in;
  grill_t form;

  memset(&in,0,sizeof(in));

  txt = fopen("airplane.txt","r");
  p_l = (piece_t *)malloc(sizeof(piece_t) * 12);
  extract(txt, &form, p_l);

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
  
  font_timer = TTF_OpenFont("BlockoBit.ttf",32);
  font_title = TTF_OpenFont("BlockoBit.ttf",64);
  
  gameover = 0;
  /* main loop: check events and re-draw the window until the end */
  start = time(NULL);
  in_time = time(NULL);
  sprintf(t_str, "Pentomino");
  title = TTF_RenderText_Blended(font_title, t_str, black);
  mod = 1;
  mouse_state = 0;
  position.x = 200;
  position.y = 157;

  while (!gameover)
    {
      startT = SDL_GetTicks();
      if(SDL_GetTicks()-startT < 1000/120){
	SDL_Delay((1000/120)-(SDL_GetTicks()-startT));
      }
      UpdateEvents(&in);
      if(in.mousebuttons[SDL_BUTTON_LEFT]){
	in.mousebuttons[SDL_BUTTON_LEFT] = 0;
	mouse_state = (mouse_state + 1) % 2;
      }
      if(in.key[SDLK_ESCAPE] || in.quit){
	gameover=1;
      }
      if(in.key[SDLK_p] && DEBUG_MOD){
	in.key[SDLK_p]=0;
	mod = (mod + 1)%2;
	chgt_st = 1;
	mouse_state = 0;
      }
      /* Draw the background */

      SDL_BlitSurface(bcgr, NULL, screen, NULL);
      switch(mod){
      case 1:
	if(mod==1){
	  t_temp = time(NULL);
	  if(t_temp!=in_time){
	    t_int = difftime(in_time, start);
	    min = (t_int / 60) % 100;
	    sec = t_int % 60;
	    sprintf(t_str, "%d%d:%d%d",min/10,min%10,sec/10,sec%10);
	    text = TTF_RenderText_Blended(font_timer, t_str,
					  black);
	    in_time = time(NULL);
	  }
	  
	  p_chrono.x = 938 - 31 * 5;
	  p_chrono.y = 5;
	  SDL_BlitSurface(text, NULL, screen, &p_chrono);
	  
	  p_rect.w = 20;
	  p_rect.h = 20;
	  for(int i=0;i<form.hei;i++){
	    p_rect.y=form.TLy + 20 * i;
	    for(int j=0;j<16;j++){
	      p_rect.x=form.TLx + 20 * j;
	      if(form.shape[i][j]=='1'){
		SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,0,0,0));
	      }
	    }
	  }
	  for(int k=0;k<12;k++){
	    for(int i=0;i<5;i++){
	      p_rect.y=p_l[k].posy + 20 * i;
	      for(int j=0;j<5;j++){
		p_rect.x=p_l[k].posx + 20 * j;
		if(p_l[k].shape[i][j]=='1'){
		  SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,0,0,255));
		}
	      }
	    }
	  }
	}
	break;
      default:
	if(mouse_state){
	  position.x = in.mousex - 268;
	  position.y = in.mousey - 30;
	}
	SDL_BlitSurface(title, NULL, screen, &position);
	break;
      }
	/* update the screen */
	SDL_UpdateRect(screen,0,0,0,0);	
    }
  /* clean up */
  for(int i=0;i<12;i++){
    for(int j=0;j<5;j++){
      free(p_l[i].shape[j]);
    }
    free(p_l[i].shape);
  }
  free(p_l);
  free(t_str);
  SDL_FreeSurface(bcgr);
  if(chgt_st){
    SDL_FreeSurface(text);
  }
  for(int i=0;i<form.hei;i++){
    free(form.shape[i]);
  }
  free(form.shape);
  SDL_FreeSurface(title);
  SDL_FreeSurface(screen);
  TTF_CloseFont(font_timer);
  TTF_CloseFont(font_title);
  TTF_Quit();
  SDL_Quit();
  fclose(txt);
  
  return 0;
}
