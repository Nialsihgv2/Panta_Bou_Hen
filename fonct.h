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

struct Piece{
  char** form;
  bool flip;
};

void init_piece(piece_t* p);

void free_piece(piece_t* p);

void create_piece(FILE *txt, char **piece);
