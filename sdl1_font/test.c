//
// FONT
// https://github.com/kripken/emscripten/issues/2708
// https://groups.google.com/forum/#!topic/emscripten-discuss/lfXaVdyYztw
// http://www.sdltutorials.com/sdl-ttf
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

typedef struct {
  int dummy;
} Context;
Context ctx;
SDL_Surface* screen = NULL;
SDL_Surface *text_surface;

void main_loop(void*args) {
  SDL_Rect clip;
  clip.x = 0;
  clip.y = 0;
  clip.w = 400;
  clip.h = 100;
  SDL_Rect offset;
  offset.x = 40;
  offset.y = 40;
  SDL_BlitSurface( text_surface, &clip, screen, &offset  );
  SDL_Flip( screen );
}

int main( int argc, char* args[] )
{
  printf("main \r\n");
  SDL_Init( SDL_INIT_EVERYTHING );
//  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
  SDL_WM_SetCaption( "title", 0 );
  //
  //
  printf("ttf init \r\n");
  if(TTF_Init()< 0) {
    printf("Failed at TTF_Init\r\n");
  }
  SDL_WM_SetCaption( "TTF Test", NULL );

  TTF_Font *font = TTF_OpenFont("./assets/Roboto-Bold.ttf", 28);
  SDL_Color fg = {255, 255, 255,255};
  text_surface = TTF_RenderText_Solid(font, "test test !!", fg);
  SDL_Flip( screen );

  printf("ttf %d %d\r\n",  text_surface->w, text_surface->h);
  //
  //
#ifdef PLATFORM_EMCC
  emscripten_set_main_loop_arg(main_loop, &ctx, 60, 1);
#else
  SDL_Event event;
  int isQuit = 0;
  while(isQuit == 0) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isQuit = 1;
      }
    }
    main_loop(&ctx);
    SDL_Delay(10);
  }
  SDL_Quit();
#endif
  return 0;
}
