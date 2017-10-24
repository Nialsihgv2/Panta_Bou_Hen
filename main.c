#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "fonct.h"

typedef struct Event event_t;

struct Event
{
  char key[SDLK_LAST];
  int mousex,mousey;
  int mousexrel,mouseyrel;
  char mousebuttons[8];
  char quit;
};

void UpdateEvents(event_t* in)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_KEYDOWN:
      in->key[event.key.keysym.sym]=1;
      break;
    case SDL_KEYUP:
      in->key[event.key.keysym.sym]=0;
      break;
    case SDL_MOUSEMOTION:
      in->mousex=event.motion.x;
      in->mousey=event.motion.y;
      in->mousexrel=event.motion.xrel;
      in->mouseyrel=event.motion.yrel;
      break;
    case SDL_MOUSEBUTTONDOWN:
      in->mousebuttons[event.button.button]=1;
      break;
    case SDL_MOUSEBUTTONUP:
      in->mousebuttons[event.button.button]=0;
      break;
    case SDL_QUIT:
      in->quit=1;
      break;
    default:
      break;
    }
  }
}

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *bcgr, *text, *title;
  SDL_Rect position,p_chrono,p_rect;
  int gameover, mod, mouse_state;
  time_t start, in_time, t_temp;
  int t_int, min, sec;
  char *t_str;
  TTF_Font *font_timer, *font_title;
  SDL_Color black = {0, 0, 0};
  piece_t* p_l;
  Uint32 startT;
  FILE* txt = NULL;
  char **t_rect;
  event_t in;

  memset(&in,0,sizeof(in));

  txt = fopen("pentomino.txt","r");
  t_rect = (char**)malloc(49*sizeof(char*));
  for(int i=0;i<49;i++){
    t_rect[i]=(char*)malloc(11*sizeof(char));
  }
  create_piece(txt,t_rect);
  p_l=(piece_t*)malloc(sizeof(piece_t));
  init_piece(p_l);

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
  mod = DEBUG_MOD;
  mouse_state = 0;
  position.x = (938 - 63 * 9)/2;
  position.y = (621 - 63)/2;

  while (!gameover)
    {
      UpdateEvents(&in);
      if(in.mousebuttons[SDL_BUTTON_LEFT]){
	in.mousebuttons[SDL_BUTTON_LEFT] = 0;
	mouse_state = (mouse_state + 1) % 2;
      }
      if(in.key[SDLK_ESCAPE] || in.quit){
	gameover=1;
      }
      if(in.key[SDLK_p]){
	in.key[SDLK_p]=0;
	mod = (mod + 1)%2;
      }
      /* Draw the background */

      SDL_BlitSurface(bcgr, NULL, screen, NULL);
      
      if(mod==1){
	startT = SDL_GetTicks();
	if(SDL_GetTicks()-startT < 1000/60){
	  SDL_Delay((1000/60)-(SDL_GetTicks()-startT));
	}
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
	
	
	p_rect.w = 12;
	p_rect.h = 12;
	for(int i=0;i<49;i++){
	  p_rect.y=12*i;
	  for(int j=0;j<11;j++){
	    p_rect.x=12*j;
	    if(t_rect[i][j]=='#'){
	      SDL_FillRect(screen,&p_rect,i<7?SDL_MapRGB(screen->format,0,0,255)
			   :SDL_MapRGB(screen->format,0,255,0));}
	  }
	}
	if(mouse_state){
	  position.x = in.mousex;
	  position.y = in.mousey;
	}
	SDL_BlitSurface(title, NULL, screen, &position);
	
      }
      /* update the screen */
      SDL_UpdateRect(screen,0,0,0,0);	
    }
  
  /* clean up */
  free_piece(p_l);
  free(p_l);
  free(t_str);
  SDL_FreeSurface(bcgr);
  SDL_FreeSurface(text);
  SDL_FreeSurface(title);
  SDL_FreeSurface(screen);
  TTF_CloseFont(font_timer);
  TTF_CloseFont(font_title);
  TTF_Quit();
  SDL_Quit();
  for(int i=0;i<49;i++){
    free(t_rect[i]);
  }
  free(t_rect);
  fclose(txt);
  
  return 0;
}
