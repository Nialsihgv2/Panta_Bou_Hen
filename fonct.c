#include "fonct.h"

void update_events(input_t* in)
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

void alter_events_menu(input_t* in, int *gameover, int *mod)
{
  if(in->key[SDLK_ESCAPE] || in->quit){
    *gameover = 1;
  }
  if(in->key[SDLK_m] && DEBUG_MOD){
    in->key[SDLK_m] = 0;
    *mod = 1;
  }
}

void alter_events_game(input_t* in,int *chgt_st, int *gameover,
		 int *mod, int *mouse_state, int *take)
{
  if(in->mousebuttons[SDL_BUTTON_LEFT]){
    in->mousebuttons[SDL_BUTTON_LEFT] = 0;
    *chgt_st = 1;
  }
  if(in->key[SDLK_ESCAPE] || in->quit){
    *gameover=1;
  }
  if(in->key[SDLK_m] && DEBUG_MOD){
    in->key[SDLK_m]=0;
    *mod = 0;
    *mouse_state = 0;
  }
  if(!*mouse_state){
    if(in->key[SDLK_f]){
      in->key[SDLK_f] = 0;
      *mouse_state = 1;
      *take = 0;
    }
    if(in->key[SDLK_i]){
      in->key[SDLK_i] = 0;
      *mouse_state = 1;
      *take = 1;
    }
    if(in->key[SDLK_l]){
      in->key[SDLK_l] = 0;
      *mouse_state = 1;
      *take = 2;
    }
    if(in->key[SDLK_n]){
      in->key[SDLK_n] = 0;
      *mouse_state = 1;
      *take = 3;
    }
    if(in->key[SDLK_p]){
      in->key[SDLK_p] = 0;
      *mouse_state = 1;
      *take = 4;
    }
    if(in->key[SDLK_t]){
      in->key[SDLK_t] = 0;
      *mouse_state = 1;
      *take = 5;
    }
    if(in->key[SDLK_u]){
      in->key[SDLK_u] = 0;
      *mouse_state = 1;
      *take = 6;
    }
    if(in->key[SDLK_v]){
      in->key[SDLK_v] = 0;
      *mouse_state = 1;
      *take = 7;
    }
    if(in->key[SDLK_w]){
      in->key[SDLK_w] = 0;
      *mouse_state = 1;
      *take = 8;
    }
    if(in->key[SDLK_x]){
      in->key[SDLK_x] = 0;
      *mouse_state = 1;
      *take = 9;
    }
    if(in->key[SDLK_y]){
      in->key[SDLK_y] = 0;
      *mouse_state = 1;
      *take = 10;
    }
    if(in->key[SDLK_z]){
      in->key[SDLK_z] = 0;
      *mouse_state = 1;
      *take = 11;
    }
  }
}


void extract(FILE *txt, grill_t *form, piece_t *piec)
{
  char *temp, line[100];
  int length = 6;
  int i,j;
  for(i=0;i<4;i++){
    temp = fgets(line,length,txt);
    switch(i){
    case 0:
      form->len = atoi(line);
      if(form->len > 5){
	length = form->len + 1;
      }
      break;
    case 1:
      form->hei = atoi(line);
      break;
    case 2:
      form->TLx = atoi(line);
      break;
    case 3:
      form->TLy = atoi(line);
      break;
    default:
      break;
    }
  }
  form->shape = (char **)malloc(sizeof(char *) * form->hei);
  for(i=0;i<form->hei;i++){
    form->shape[i] = (char *)malloc(sizeof(char) * form->len);
    temp = fgets(form->shape[i],length,txt);
  }
  for(i=0;i<12;i++){
    piec[i].shape = (char**)malloc(sizeof(char*) * 5);
    for(j=0;j<5;j++){
      piec[i].shape[j] = (char*)malloc(sizeof(char) * 5);
    }
    for(j=0;j<10;j++){
      temp = fgets(line,length,txt);
      switch(j){
      case 0:
	piec[i].name = line[0];
	break;
      case 1:
	piec[i].posx = atoi(line);
	piec[i].stx = piec[i].posx;
	break;
      case 2:
	piec[i].posy = atoi(line);
	piec[i].sty = piec[i].posy;
	break;
      case 3:
	piec[i].endx = atoi(line);
	break;
      case 4:
	piec[i].endy = atoi(line);
	break;
      default:
	strcpy(piec[i].shape[j-5],line);
	break;
      }
    }
  }
  temp = fgets(temp,2,txt);
  free(temp);
}

void apply_color(int state, int* red, int* green, int *blue)
{
  switch(state){
  case 0:
  case 1:
  case 2:
  case 10:
  case 11:
    *red = 255;
    break;
  case 3:
  case 9:
    *red = 127;
    break;
  default:
    *red = 0;
    break;
  }
  switch(state){
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    *green = 255;
    break;
  case 1:
  case 7:
    *green = 127;
    break;
  default:
    *green = 0;
    break;
  }
  switch(state){
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    *blue = 255;
    break;
  case 5:
  case 11:
    *blue = 127;
    break;
  default:
    *blue = 0;
    break;
  }
}
