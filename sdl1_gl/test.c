//
// FONT
// https://github.com/kripken/emscripten/issues/2708
// https://groups.google.com/forum/#!topic/emscripten-discuss/lfXaVdyYztw
// http://www.sdltutorials.com/sdl-ttf
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <stdio.h>
#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

typedef struct {
  int dummy;
} Context;
Context ctx;
SDL_Surface* screen = NULL;

void main_loop(void*args) {
  glClearColor(1.0, 1.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapBuffers();//SDL_Flip( screen );
}

int main( int argc, char* args[] )
{
  printf("main \r\n");
  SDL_Init( SDL_INIT_EVERYTHING );
//  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  screen = SDL_SetVideoMode( 640, 480, 32, SDL_HWSURFACE|SDL_OPENGL| SDL_DOUBLEBUF);
  if(screen == NULL) {
    printf("Failed at SDL_SetVideoMode\r\n");
    return 0;
  }
  SDL_WM_SetCaption( "title", 0 );
  //
  //
  printf("ttf init \r\n");
  glClearColor(1.0, 0.6, 0.6, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapBuffers();//SDL_Flip( screen );

  printf("ttf \r\n");
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
