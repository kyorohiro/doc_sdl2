//
// Create Window
//
#include <SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = NULL;
  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  SDL_WM_SetCaption( "title", 0 );
  SDL_Flip( screen );
#ifdef PLATFORM_EMCC
#else
  SDL_Event event;
  int isQuit = 0;
  while(isQuit == 0) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isQuit = 1;
      }
    }
  }
  SDL_Quit();
#endif
  return 0;
}
