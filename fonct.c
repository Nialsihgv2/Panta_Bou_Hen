#include "fonct.h"

void init_piece(piece_t* p)
{
  p->form=(char**)malloc(5*sizeof(char*));
  for(int i=0;i<5;i++){
    p->form[i]=(char*)malloc(5*sizeof(char));
    sprintf(p->form[i],"12345");
  }
  p->flip = false;
}

void free_piece(piece_t* p)
{
  for(int i=0;i<5;i++){
    free(p->form[i]);
  }
  free(p->form);
}
