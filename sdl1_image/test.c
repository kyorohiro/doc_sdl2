//
// Create Window
//
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
  printf("main \r\n");
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = NULL;
//  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
  SDL_WM_SetCaption( "title", 0 );

  SDL_Surface* loadedImage = IMG_Load( "assets/icon.png" );
  SDL_Rect clip;
  clip.x = 0;
  clip.y = 0;
  clip.w = 400;
  clip.h = 400;
  SDL_Rect offset;
  offset.x = 0;
  offset.y = 0;
  SDL_BlitSurface( loadedImage, &clip, screen, &offset  );
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
