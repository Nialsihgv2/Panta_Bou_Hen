#include "fonct.h"

void init_piece(piece_t* p)
{
  p->shape=(char**)malloc(5*sizeof(char*));
  for(int i=0;i<5;i++){
    p->shape[i]=(char*)malloc(5*sizeof(char));
  }
}

void free_piece(piece_t* p)
{
  for(int i=0;i<5;i++){
    free(p->shape[i]);
  }
  free(p->shape);
}

void create_piece(FILE *txt, char **piece)
{
  char * temp;
  for(int i=0;i<49;i++){
    temp = fgets(piece[i],12,txt);
  }
  free(temp);
}

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
