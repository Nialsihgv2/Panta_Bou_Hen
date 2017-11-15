#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
/* Size of the window */
#define SCREEN_WIDTH  938
#define SCREEN_HEIGHT 621
#define DEBUG_MOD 1


typedef struct Piece piece_t;
typedef struct Grill grill_t;
typedef struct Input input_t;

struct Piece
{
  int posx, posy;
  int stx, sty;
  int endx, endy;
  char name;
  char** shape;
};

struct Grill
{
  int TLx,TLy;
  int len,hei;
  char ** shape;
  int ** val;
};

struct Input
{
  char key[SDLK_LAST];
  int mousex,mousey;
  int mousexrel,mouseyrel;
  char mousebuttons[8];
  char quit;
};


void UpdateEvents(input_t* in);
void AlterEvents(input_t* in,int *chgt_st, int *gameover,
		 int *mod, int *mouse_state);

void extract(FILE *txt, grill_t *form, piece_t *piec);

void apply_color(int state, int* red, int* green, int*blue);
