#include <SDL.h>

/* Size of the window */
#define SCREEN_WIDTH  938
#define SCREEN_HEIGHT 621
/* Size of the sprite; this is a square */
#define SPRITE_SIZE   100
/* NB of each piece with != shape */
#define NB_PIECES     12

int main(int argc, char* argv[])
{
  SDL_Surface** sprite;
  SDL_Surface *screen, *temp, *bcgr;
  SDL_Rect spritePosition;
  int colorkey, gameover;
  int defsp = 0;
  int defim = 0;
  
  /* initialize video system */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Pentamino", "Pentamino");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* setup colorkey */
    colorkey = SDL_MapRGB(screen->format, 153, 153, 153);
  /* load sprites */
    sprite = (SDL_Surface**)malloc(NB_PIECES*sizeof(SDL_Surface*));
    for(int i=0;i<NB_PIECES;i++){
      switch(i){
      case 0:
	temp   = SDL_LoadBMP("Projet_F.bmp");
	break;
      case 1:
	temp   = SDL_LoadBMP("Projet_I.bmp");
	break;
      case 2:
	temp   = SDL_LoadBMP("Projet_L.bmp");
	break;
      case 3:
	temp   = SDL_LoadBMP("Projet_N.bmp");
	break;
      case 4:
	temp   = SDL_LoadBMP("Projet_P.bmp");
	break;
      case 5:
	temp   = SDL_LoadBMP("Projet_T.bmp");
	break;
      case 6:
	temp   = SDL_LoadBMP("Projet_U.bmp");
	break;
      case 7:
	temp   = SDL_LoadBMP("Projet_V.bmp");
	break;
      case 8:
	temp   = SDL_LoadBMP("Projet_W.bmp");
	break;
      case 9:
	temp   = SDL_LoadBMP("Projet_X.bmp");
	break;
      case 10:
	temp   = SDL_LoadBMP("Projet_Y.bmp");
	break;
      case 11:
	temp   = SDL_LoadBMP("Projet_Z.bmp");
	break;
      default:
	break;}
      *(sprite + i) = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);

    /* turn on RLE */
      SDL_SetColorKey(*(sprite + i), SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);}

    /* load background */
    temp  = SDL_LoadBMP("backgr.bmp");
    bcgr = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* set sprite position */
    spritePosition.x = 0;
    spritePosition.y = 0;

    gameover = 0;

    /* main loop: check events and re-draw the window until the end */
    while (!gameover)
    {
        SDL_Event event;

        /* look for an event */
        if (SDL_PollEvent(&event)) {
            /* an event was found */
            switch (event.type) {
                /* close button clicked */
                case SDL_QUIT:
                    gameover = 1;
                    break;

                /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
		    case SDLK_ESCAPE:
		    case SDLK_q:
		      gameover = 1;
		      break;
		    case SDLK_RIGHT:
		      defsp++;
		      if(defsp>=16)
			defsp = 15;
		      break;
		    case SDLK_LEFT:
		      defsp--;
		      if(defsp<0)
			defsp = 0;
		      break;
		    case SDLK_UP:
		      defim--;
		      if(defim<0)
			defim = 0;
		      break;
		    case SDLK_DOWN:
		      defim++;
		      if(defim>=NB_PIECES)
			defim = NB_PIECES-1;
		      break;
		    default:
		      break;
                    }
                    break;
            }
        }

        /* Draw the background */
	SDL_BlitSurface(bcgr, NULL, screen, NULL);

	/* Dimension of one sprite */
	SDL_Rect dimsprite;
	dimsprite.y = 0;
	dimsprite.w = SPRITE_SIZE;
	dimsprite.h = SPRITE_SIZE;
	
	/* Position on bmp of sprite to chosse the right one */
	dimsprite.x = defsp*100;

        /* draw the sprite */
        SDL_BlitSurface(*(sprite + defim), &dimsprite, screen, &spritePosition);

        /* update the screen */
        SDL_UpdateRect(screen,0,0,0,0);
    }

    /* clean up */
    for(int i=0;i<NB_PIECES;i++){
      SDL_FreeSurface(*(sprite+i));}
    free(sprite);
    SDL_FreeSurface(bcgr);
    SDL_Quit();

    return 0;
}
