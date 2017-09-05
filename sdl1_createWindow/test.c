//
// Create Window
//
#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = NULL;
  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
  SDL_Flip( screen );
#ifdef PLATFORM_EMCC
#else
  SDL_Delay( 2000 );
  SDL_Quit();
#endif
  return 0;
}
