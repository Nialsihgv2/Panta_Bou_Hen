#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
/* Size of the window */
#define SCREEN_WIDTH  938
#define SCREEN_HEIGHT 621


typedef struct Piece piece_t;

struct Piece{
  char** form;
  bool flip;
};

void init_piece(piece_t* p);

void free_piece(piece_t* p);
