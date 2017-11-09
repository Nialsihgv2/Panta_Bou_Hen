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
#define TIMER_POS_X 630
#define TIMER_POS_Y 5
#define DEBUG_MOD 1


typedef struct Piece piece_t;
typedef struct Grill grill_t;
typedef struct Input input_t;

struct Piece
{
  int posx, posy;
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

void extract(FILE *txt, grill_t *form, piece_t *piec);
