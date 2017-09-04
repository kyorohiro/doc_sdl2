#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif
#include <unistd.h>
#include <stdlib.h>

int _isQuit = 0;
typedef struct {
  int dummy;
} Context;
Context ctx;

void main_loop(void*args) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        _isQuit = 1;
    }
  }
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  //
  // Draw Image
  SDL_Surface *image = IMG_Load("./image/assets/icon.png");
  if (!image)
  {
     printf("Failed at IMG_Load: %s\n", IMG_GetError());
     return 0;
  }
  SDL_Rect dest = {.x = 0, .y = 0, .w = 100, .h = 100};
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, image);
  SDL_RenderCopy (renderer, tex, NULL, &dest);
//  SDL_DestroyTexture (tex);
//  SDL_FreeSurface (image);


  SDL_RenderPresent(renderer);

  #ifdef PLATFORM_EMCC
    emscripten_set_main_loop_arg(main_loop, &ctx, 60, 1);
  #else
    do {
      main_loop(&ctx);
    } while(_isQuit == 0);
  #endif
  return 0;
}
