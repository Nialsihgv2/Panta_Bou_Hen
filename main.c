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
  /* initialisation of all variable */
  SDL_Surface *screen, *temp, *bcgr, *title, *sel01, *sel02, *sel03,
    *sel11 , *sel12, *sel13, *cong, **lvsur, *rarrow, **nb_sur, *nb_lev, **cr;
  SDL_Rect position,p_rect;
  int gameover, mod, mouse_state, red, green, blue, chgt_st,
    take, cnt, placed, chgt_mod, lv_int;
  char *t_str;
  TTF_Font *font_title, *font_select, *font_lv;
  SDL_Color black = {0, 0, 0}, bluegen = {0, 0, 127};
  piece_t *p_l;
  Uint32 startT;
  FILE* txt;
  input_t in;
  grill_t form;
  level_t lv;

  /* initialisation of in at 0 for all variable in structure */
  memset(&in,0,sizeof(in));

  /* initialisation of all levels in string */
  init_level(&lv);

  
  /* initialize video system */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Pentomino", "Pentomino");

  /* init TTF */
  TTF_Init();

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* load background */
  temp  = SDL_LoadBMP("backgr.bmp");
  bcgr = SDL_DisplayFormatAlpha(temp);
  SDL_FreeSurface(temp);
  
  /* load all font */
  font_select = TTF_OpenFont("ttf/BlockoBit.ttf",48);
  font_title = TTF_OpenFont("ttf/BlockoBit.ttf",64);
  font_lv = TTF_OpenFont("ttf/PressStart2P.ttf",36);
  
  /* create all text in SDL_Surface */
  t_str=(char *)malloc(sizeof(char)*50);
  sprintf(t_str, "PENTOMINO");
  title = TTF_RenderText_Blended(font_title, t_str, black);
  sprintf(t_str, "New Game");
  sel01 = TTF_RenderText_Blended(font_select, t_str, black);
  sel11 = TTF_RenderText_Blended(font_select, t_str, bluegen);
  sprintf(t_str, "Credits");
  sel02 = TTF_RenderText_Blended(font_select, t_str, black);
  sel12 = TTF_RenderText_Blended(font_select, t_str, bluegen);
  sprintf(t_str, "Quit");
  sel03 = TTF_RenderText_Blended(font_select, t_str, black);
  sel13 = TTF_RenderText_Blended(font_select, t_str, bluegen);
  sprintf(t_str, "CONGRATULATIONS");
  cong = TTF_RenderText_Blended(font_title, t_str, black);
  lvsur = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * NB_LEVELS);
  for(int i=0;i<NB_LEVELS;i++){
    strcpy(t_str, lv.level[i]);
    lvsur[i] = TTF_RenderText_Blended(font_lv, t_str, black);
  }
  sprintf(t_str, ">");
  rarrow = TTF_RenderText_Blended(font_lv, t_str, black);
  nb_sur = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * NB_LEVELS);
  for(int i=0;i<NB_LEVELS;i++){
    sprintf(t_str,"%d%d",(i+1)/10,(i+1)%10);
    nb_sur[i] = TTF_RenderText_Blended(font_lv, t_str, black);
  }
  sprintf(t_str,"/%d",NB_LEVELS);
  nb_lev = TTF_RenderText_Blended(font_lv, t_str, black);
  cr = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4);
  sprintf(t_str,"Game made by :");
  cr[0] = TTF_RenderText_Blended(font_lv, t_str, black);
  sprintf(t_str,"Ghislain Bouriannes");
  cr[1] = TTF_RenderText_Blended(font_lv, t_str, black);
  sprintf(t_str,"(aka Heartwing)");
  cr[2] = TTF_RenderText_Blended(font_lv, t_str, black);
  sprintf(t_str,"Pierre Henry");
  cr[3] = TTF_RenderText_Blended(font_lv, t_str, black);

  /* init other variables*/
  gameover = 0;
  mod = 0;
  mouse_state = 0;
  chgt_st = 0;
  lv_int = 0;

  while (!gameover)
    {
      /* Make the game at 120 FPS */
      startT = SDL_GetTicks();
      if(SDL_GetTicks()-startT < 1000/120){
	SDL_Delay((1000/120)-(SDL_GetTicks()-startT));
      }

      /* uptate all events */
      update_events(&in);

      /* init changement mod at 0 */
      chgt_mod = 0;

      /* Draw background */
      SDL_BlitSurface(bcgr, NULL, screen, NULL);

      switch(mod){
      case 0:
	/* mod Title screen */

	/* Use updates for interaction in title screen */
	alter_events_menu(&in, &gameover, &chgt_st);

	/* place Title */
	position.x = 200;
	position.y = 90;
	SDL_BlitSurface(title, NULL, screen, &position);

	/* place selections */
	position.x = 280;
	position.y = 260;
	if(in.mousex >= 280 && in.mousex <= 640 &&
	   in.mousey >= 260 && in.mousey <= 300){
	  SDL_BlitSurface(sel11, NULL, screen, &position);
	}else{
	  SDL_BlitSurface(sel01, NULL, screen, &position);
	}	  
	position.x = 310;
	position.y = 340;
	if(in.mousex >= 310 && in.mousex <= 625 &&
	   in.mousey >= 340 && in.mousey <= 380){
	  SDL_BlitSurface(sel12, NULL, screen, &position);
	}else{
	  SDL_BlitSurface(sel02, NULL, screen, &position);
	}
	position.x = 370;
	position.y = 425;
	if(in.mousex >= 370 && in.mousex <= 550 &&
	   in.mousey >= 425 && in.mousey <= 460){
	  SDL_BlitSurface(sel13, NULL, screen, &position);
	}else{
	  SDL_BlitSurface(sel03, NULL, screen, &position);
	}
	
	/* If we click on a selection */
	if(chgt_st){
	  if(in.mousex >= 280 && in.mousex <= 640 &&
	     in.mousey >= 260 && in.mousey <= 300){
	    mod = 1;
	  }
	  if(in.mousex >= 310 && in.mousex <= 625 &&
	     in.mousey >= 340 && in.mousey <= 380){
	    mod = 4;
	  }
	  if(in.mousex >= 370 && in.mousex <= 550 &&
	     in.mousey >= 425 && in.mousey <= 460){
	    gameover = 1;
	  }
	}
	chgt_st = 0;
	break;
      case 1:
	/* mod Selection of level */

	alter_events_select(&in, &gameover, &lv_int, &mod, &chgt_mod);

	/* Draw Selection */
	position.x = 250;
	position.y = 250;
	SDL_BlitSurface(lvsur[lv_int], NULL, screen, &position);
	position.x = 650;
	position.y = 250;
	SDL_BlitSurface(rarrow, NULL, screen, &position);
	position.x = 350;
	position.y = 540;
	SDL_BlitSurface(nb_sur[lv_int], NULL, screen, &position);
	position.x = 430;
	position.y = 540;
	SDL_BlitSurface(nb_lev, NULL, screen, &position);
	break;
      case 2:
	/* Game mod */

	alter_events_game(&in, &chgt_st, &gameover, &chgt_mod, &mouse_state,
			  &take, p_l);

	/* Draw shape of level */
	p_rect.w = 20;
	p_rect.h = 20;
	for(int i=0;i<form.hei;i++){
	  p_rect.y=form.TLy + 20 * i;
	  for(int j=0;j<form.len;j++){
	    p_rect.x=form.TLx + 20 * j;
	    if(form.shape[i][j]=='1'){
	      SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,0,0,0));
	    }
	  }
	}

	/* if click */
	if(chgt_st){
	  switch(mouse_state){
	  case 0:
	    /* case pieces not take 
	       verifie if we take a piece */
	    cnt = NB_PIECES - 1;
	    while(!mouse_state && cnt >= 0){
	      if(p_l[cnt].posx + 20<=in.mousex && p_l[cnt].posx+80>=in.mousex &&
		 p_l[cnt].posy + 20<=in.mousey && p_l[cnt].posy+80>=in.mousey){
		take = cnt;
		mouse_state = 1;
	      }
	      cnt--; 
	    }
	    break;
	  case 1:
	    /* case a piece was taken
	       we place piece */
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
	  /* if not piece taken
	     verifie if each piece is in good position */
	  placed = 0;
	  for(int i=0;i < NB_PIECES;i++){
	    if(p_l[i].posx == p_l[i].endx
	       && p_l[i].posy == p_l[i].endy){
	      placed++;
	    }
	  }
	  if(placed == NB_PIECES){
	    mod = 3;
	  }
	  break;
	case 1:
	  /* if piece taken
	     move the piece taken */
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

	/* Draw all piece */
	for(int k=0;k<NB_PIECES;k++){
	  apply_color(k,&red,&green,&blue);
	  for(int i=0;i<5;i++){
	    p_rect.y=p_l[k].posy + 20 * i;
	    for(int j=0;j<5;j++){
	      p_rect.x=p_l[k].posx + 20 * j;
	      if(p_l[k].shape[i][j]=='1'){
		SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,
						       red,green,blue));
	      }
	    }
	  }
	}

	/* Draw piece taken */
	if(mouse_state){
	  apply_color(take,&red,&green,&blue);
	  for(int i=0;i<5;i++){
	    p_rect.y=p_l[take].posy + 20 * i;
	    for(int j=0;j<5;j++){
	      p_rect.x=p_l[take].posx + 20 * j;
	      if(p_l[take].shape[i][j]=='1'){
		SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,
						       red,green,blue));
	      }
	    }
	  }
	}
	break;
      case 3:
	/* Victory mod */

	alter_events_endgame(&in,&gameover,&chgt_mod);

	/* Draw each piece */
	for(int k=0;k<NB_PIECES;k++){
	  apply_color(k,&red,&green,&blue);
	  for(int i=0;i<5;i++){
	    p_rect.y=p_l[k].posy + 20 * i;
	    for(int j=0;j<5;j++){
	      p_rect.x=p_l[k].posx + 20 * j;
	      if(p_l[k].shape[i][j]=='1'){
		SDL_FillRect(screen,&p_rect,SDL_MapRGB(screen->format,
						       red,green,blue));
	      }
	    }
	  }
	}
	
	/* Draw CONGRATULATION */
	position.x = 10;
	position.y = 280;
	SDL_BlitSurface(cong, NULL, screen, &position);	
	break;
      case 4:
	/* Credit mod */
	alter_events_credit(&in,&gameover,&mod);
	position.x = 220;
	position.y = 130;
	SDL_BlitSurface(cr[0], NULL, screen, &position);
	position.x = 120;
	position.y = 210;
	SDL_BlitSurface(cr[1], NULL, screen, &position);
	position.x = 200;
	position.y = 270;
	SDL_BlitSurface(cr[2], NULL, screen, &position);
	position.x = 245;
	position.y = 400;
	SDL_BlitSurface(cr[3], NULL, screen, &position);
	break;
      default:
	break;
      }
      if(chgt_mod){
	switch(mod){
	case 1:
	  /* Select mod to Game mod
	     create pieces and grill */
	  txt = fopen(lv.txt[lv_int],"r");
	  p_l = (piece_t *)malloc(sizeof(piece_t) * NB_PIECES);
	  extract(txt, &form, p_l);
	  fclose(txt);
	  mod = 2;
	  break;
	case 2:
	case 3:
	  /* Game mod or Victory mod to Title screen 
	     free pieces ang grill*/	  
	  for(int i=0;i<NB_PIECES;i++){
	    for(int j=0;j<5;j++){
	      free(p_l[i].shape[j]);
	    }
	    free(p_l[i].shape);
	  }
	  free(p_l);
	  for(int i=0;i<form.hei;i++){
	    free(form.shape[i]);
	  }
	  free(form.shape);
	  mouse_state = 0;
	  mod = 0;
	  break;
	default:
	  break;
	}
      }
      /* update the screen */
      SDL_UpdateRect(screen,0,0,0,0);	
    }
  /* clean up */
  free(t_str);
  SDL_FreeSurface(bcgr);
  SDL_FreeSurface(title);
  SDL_FreeSurface(sel01);
  SDL_FreeSurface(sel02);
  SDL_FreeSurface(sel03);
  SDL_FreeSurface(sel11);
  SDL_FreeSurface(sel12);
  SDL_FreeSurface(sel13);
  for(int i=0;i<NB_LEVELS;i++){
    SDL_FreeSurface(lvsur[i]);
  }
  free(lvsur);
  for(int i=0;i<NB_LEVELS;i++){
    SDL_FreeSurface(nb_sur[i]);
  }
  free(nb_sur);
  SDL_FreeSurface(nb_lev);
  SDL_FreeSurface(cong);
  SDL_FreeSurface(rarrow);
  for(int i=0;i<4;i++){
    SDL_FreeSurface(cr[i]);
  }
  free(cr);
  SDL_FreeSurface(screen);
  TTF_CloseFont(font_select);
  TTF_CloseFont(font_title);
  TTF_CloseFont(font_lv);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
