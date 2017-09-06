//
// Create Window
//
#include <SDL.h>
#include <stdio.h>
#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

typedef struct {
  int dummy;
} Context;
Context ctx;

int fpsCount = 0;
int debugCount = 0;
double debugTime = 0.0;
int isQuit = 0;
int fps;

double capp_currentMilliSecound() {
  #ifdef PLATFORM_EMCC
    return emscripten_get_now();
  #else
    return SDL_GetTicks();
  #endif
}

void main_loop(void*args) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        isQuit = 1;
      case SDL_MOUSEMOTION:
        printf("mouse motion : %d %d\r\n", event.motion.x, event.motion.y);
        break;
      case SDL_MOUSEBUTTONDOWN:
        printf("mouse down\r\n");
        break;
      case SDL_MOUSEBUTTONUP:
        printf("mouse up\r\n");
        break;
    }
  }

  //
  // fps
  //
  if(debugCount > 100) {
    debugCount = 0;
    double t = capp_currentMilliSecound();
    double v = t - debugTime;
    double x = v/1000.0;
    fps = (int)100/x;
    debugTime = t;
    printf("FPS = %d\r\n", fps);
  }
  debugCount++;


}

int main( int argc, char* args[] )
{
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = NULL;
  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  SDL_WM_SetCaption( "title", 0 );
  SDL_Flip( screen );
#ifdef PLATFORM_EMCC
  emscripten_set_main_loop_arg(main_loop, &ctx, 60, 1);
#else
  int prevTime = SDL_GetTicks();
  int currentTime = SDL_GetTicks();
  int interval = 1000/60;

  while(isQuit == 0) {
    main_loop(&ctx);
    if((currentTime-prevTime) < interval) {
      SDL_Delay(interval-(currentTime-prevTime));
    } else {
      SDL_Delay(1);
    }
  }
  SDL_Quit();
#endif
  return 0;
}
