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
  SDL_Surface *screen, *temp, *bcgr, *title;
  SDL_Rect position,p_rect;
  int gameover, mod, mouse_state, red, green, blue, chgt_st,
    take, cnt, placed;
  char *t_str;
  TTF_Font *font_timer, *font_title;
  SDL_Color black = {0, 0, 0};
  piece_t *p_l;
  Uint32 startT;
  FILE* txt;
  input_t in;
  grill_t form;

  memset(&in,0,sizeof(in));

  txt = fopen("txt/butterfly.txt","r");
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
  sprintf(t_str, "Pentomino");
  title = TTF_RenderText_Blended(font_title, t_str, black);
  mod = 1;
  mouse_state = 0;
  chgt_st = 0;
  position.x = 200;
  position.y = 157;

  while (!gameover)
    {
      startT = SDL_GetTicks();
      if(SDL_GetTicks()-startT < 1000/120){
	SDL_Delay((1000/120)-(SDL_GetTicks()-startT));
      }
      update_events(&in);
      /* Draw the background */

      SDL_BlitSurface(bcgr, NULL, screen, NULL);
      switch(mod){
      case 1:
	alter_events_game(&in, &chgt_st, &gameover, &mod, &mouse_state, &take);
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
	if(chgt_st){
	  switch(mouse_state){
	  case 0:
	    cnt = 0;
	    while(!mouse_state && cnt<12){
	      if(p_l[cnt].posx<=in.mousex && p_l[cnt].posx+100>=in.mousex
		 && p_l[cnt].posy<=in.mousey && p_l[cnt].posy+100>=in.mousey){
		take = cnt;
		mouse_state = 1;
	      }
	      cnt++; 
	    }
	    break;
	  case 1:
	    mouse_state = 0;
	    p_l[take].posx -= ((p_l[take].posx + 10) % 20) - 10;
	    p_l[take].posy -= ((p_l[take].posy + 10) % 20) - 10;
	    break;
	  default:
	    break;
	  }
	  chgt_st = 0;
	}
	switch(mouse_state){
	case 0:
	  placed = 0;
	  for(int i=0; i < 12;i++){
	    if(p_l[i].posx == p_l[i].endx
	       && p_l[i].posy == p_l[i].endy){
	      placed++;
	    }
	  }
	  if(placed == 12){
	    gameover = 1;
	  }
	  break;
	case 1:
	  p_l[take].posx = in.mousex - 50;
	  if(p_l[take].posx < 0){
	    p_l[take].posx = 0;
	  }
	  if(p_l[take].posx > SCREEN_WIDTH - 100){
	    p_l[take].posx = SCREEN_WIDTH - 100;
	  }
	  p_l[take].posy = in.mousey - 50;
	  if(p_l[take].posy < 0){
	    p_l[take].posy = 0;
	  }
	  if(p_l[take].posy > SCREEN_HEIGHT - 100){
	    p_l[take].posy = SCREEN_HEIGHT - 100;
	  }
	  break;
	default:
	  break;
	}
	for(int k=0;k<12;k++){
	  apply_color(k,&red,&green,&blue);
	  for(int i=0;i<5;i++){
	    p_rect.y=p_l[k].posy + 20 * i;
	    for(int j=0;j<5;j++){
	      p_rect.x=p_l[k].posx + 20 * j;
	      if(p_l[k].shape[i][j]=='1'){
		SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,red,green,blue));
	      }
	    }
	  }
	}
	break;
      case 0:
	alter_events_menu(&in, &gameover, &mod);
	SDL_BlitSurface(title, NULL, screen, &position);
	break;
      }
      /* update the screen */
      SDL_UpdateRect(screen,0,0,0,0);	
    }
  /* clean up */
  for(int i=0;i<12;i++){
    printf("%d;%d\n",p_l[i].posx,p_l[i].posy);
  }
  for(int i=0;i<12;i++){
    for(int j=0;j<5;j++){
      free(p_l[i].shape[j]);
    }
    free(p_l[i].shape);
  }
  free(p_l);
  free(t_str);
  SDL_FreeSurface(bcgr);
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
