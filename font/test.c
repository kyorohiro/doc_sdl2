//
// Create Window
//
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_ttf.h>

#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

#include <stdio.h>


int _isQuit = 0;
SDL_Surface *screen;
TTF_Font *font;
SDL_Texture *text_tex;
SDL_Window* window;
SDL_Renderer* renderer;

void main_loop(void*args) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        _isQuit = 1;
    }
  }
  SDL_RenderClear(renderer);
  SDL_Rect text_dest = {.x = 50, .y = 175, .w = 0, .h = 0};
  SDL_QueryTexture(text_tex,
          NULL, NULL, &text_dest.w, &text_dest.h);
  SDL_RenderCopy(renderer, text_tex, NULL, &text_dest);
  SDL_RenderPresent(renderer);
}

typedef struct {
  int dummy;
} Context;
Context ctx;

int main( int argc, char* args[] )
{
  printf("main\r\n");
//  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();


  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderClear(renderer);


  //

  font = TTF_OpenFont("./assets/Roboto-Bold.ttf", 30);

  SDL_Color fg = {0,0,0,255};
  SDL_Surface *text_surface = TTF_RenderText_Blended(font, "test test !!", fg);

  text_tex = SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);

  //SDL_RenderPresent(renderer);


#ifdef PLATFORM_EMCC
  emscripten_set_main_loop_arg(main_loop, &ctx, 60, 1);
#else
  do {
    main_loop(&ctx);
  } while(_isQuit == 0);
#endif

  printf("main 3 \r\n");
  return 0;
}
