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
  SDL_Rect position,testt;
  int gameover;
  time_t start, in_time, t_temp;
  int t_int, min, sec;
  char *t_str;
  TTF_Font *font_timer, *font_title;
  SDL_Color black = {0, 0, 0};
  piece_t* p_l;
  SDL_Event event;
  Uint32 startT;
  FILE* txt = NULL;
  char **test;

  txt = fopen("pentomino.txt","r");
  test = (char**)malloc(54*sizeof(char*));
  create_piece(txt,test);
  for(int i=0;i<54;i++){
    printf("%s",test[i]);
  }
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
  sprintf(t_str, "Pantomino");
  title = TTF_RenderText_Blended(font_title, t_str, black);
  while (!gameover)
    {
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
      
      position.x = 938 - 31 * 5;
      position.y = 5;
      SDL_BlitSurface(text, NULL, screen, &position);

      position.x = (938 - 63 * 9)/2;
      position.y = (621 - 63)/2;
      SDL_BlitSurface(title, NULL, screen, &position);
      
      /* update the screen */
      testt.w = 10;
      testt.h = 10;
      for(int i=0;i<54;i++){
	testt.y=10*i;
	for(int j=0;j<11;j++){
	  testt.x=10*j;
	  if(test[i][j]=='#'){
	    SDL_FillRect(screen,&testt,SDL_MapRGB(screen->format,0,0,255));}
	}
      }
      testt.x = 10;
      testt.y = 10;
      SDL_UpdateRect(screen,0,0,0,0);
      SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
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
  for(int i=0;i<54;i++){
    free(test[i]);
  }
  free(test);
  fclose(txt);
  
  return 0;
}
