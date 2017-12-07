#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
/* Size of the window */
#define SCREEN_WIDTH  920
#define SCREEN_HEIGHT 620

#define NB_LEVELS     14
#define NB_PIECES     12

typedef struct Piece piece_t;
typedef struct Grill grill_t;
typedef struct Input input_t;
typedef struct Level level_t;

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

struct Level
{
  char level[NB_LEVELS][100];
  char txt[NB_LEVELS][100];
};


void update_events(input_t* in);

void init_level(level_t* lv);

void alter_events_menu(input_t *in, int *gameover, int *chgt_st);

void alter_events_select(input_t *in, int *gameover, int *lv_int,
			 int *mod, int *chgt_mod);

void alter_events_game(input_t* in, int *chgt_st, int *gameover,
		       int *chgt_mod, int *mouse_state, int *take,
		       piece_t* piec);

void alter_events_credit(input_t *in, int *gameover, int *mod);

void alter_events_endgame(input_t* in, int *gameover, int *chgt_mod);

void extract(FILE *txt, grill_t *form, piece_t *piec);

void apply_color(int state, int* red, int* green, int*blue);
