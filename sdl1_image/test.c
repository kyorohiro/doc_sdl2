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
  printf("main 1\r\n");
  SDL_Surface* loadedImage = IMG_Load( "assets/icon.png" );
  printf("main 2\r\n");
  SDL_Rect clip;
  clip.x = 0;
  clip.y = 0;
  clip.w = 400;
  clip.h = 400;
  SDL_Rect offset;
  offset.x = 0;
  offset.y = 0;
  SDL_BlitSurface( loadedImage, &clip, screen, &offset  );
  printf("main 3\r\n");
/*  SDL_BlitSurface( loadedImage, NULL, screen, NULL );

  SDL_Surface* optimizedImage = SDL_DisplayFormat( loadedImage );
  SDL_FreeSurface( loadedImage );
  printf("main 2\r\n");
  SDL_Rect clip;
  clip.x = 0;
  clip.y = 0;
  clip.w = 400;
  clip.h = 400;
  SDL_Rect offset;
  offset.x = 0;
  offset.y = 0;
  printf("fillRect \r\n");
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0x00, 0x00 ) );

  SDL_BlitSurface( optimizedImage, &clip, screen, &offset );
  */
  SDL_Flip( screen );

  printf("loop \r\n");
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
