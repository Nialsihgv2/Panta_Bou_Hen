#include "fonct.h"

void UpdateEvents(input_t* in)
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
  }
  for(i=0;i<form->hei;i++){
    temp = fgets(form->shape[i],length,txt);
  }
  for(i=0;i<1;i++){
    piec->shape = (char**)malloc(sizeof(char*) * 5);
    for(j=0;j<5;j++){
      piec->shape[j] = (char*)malloc(sizeof(char) * 5);
    }
    for(j=0;j<8;j++){
      temp = fgets(line,length,txt);
      switch(j){
      case 0:
	piec->name = line[0];
	break;
      case 1:
	piec->posx = atoi(line);
	break;
      case 2:
	piec->posy = atoi(line);
	break;
      default:
	strcpy(piec->shape[j-3],line);
	break;
      }
    }
  }
}
