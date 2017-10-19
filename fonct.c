#include "fonct.h"

void init_piece(piece_t* p)
{
  p->form=(char**)malloc(5*sizeof(char*));
  for(int i=0;i<5;i++){
    p->form[i]=(char*)malloc(5*sizeof(char));
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

void create_piece(FILE *txt, char **piece)
{
  for(int i=0;i<49;i++){
    fgets(piece[i],12,txt);
  }
}
