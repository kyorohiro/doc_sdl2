//
// Create Window
//
#include <SDL.h>
#include <SDL_events.h>
#include <emscripten.h>
#include <stdio.h>

int x = 0;
int y = 0;
SDL_Surface *screen;
void main_loop(void*args) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
//  while (SDL_WaitEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT: x++; break;
            case SDLK_LEFT: x--; break;
            case SDLK_UP: y--; break;
            case SDLK_DOWN: y++; break;
            default: printf("Other key"); break;
        }
      //default: printf("Event %d", event.type); break;
    }
    printf("loop %d %d %d %f %f\r\n", x, y, event.type, event.tfinger.x, event.tfinger.y);
  }
/*
  // Clears the screen
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

  // fill stuff
  SDL_Rect rect = { x, y, 175, 125 };
  SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 0x22, 0x22, 0xff, 0xff));
*/
}

typedef struct {
  int dummy;
} Context;

Context ctx;

int main( int argc, char* args[] )
{
  printf("main\r\n");
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
  printf("main 2\r\n");
  emscripten_set_main_loop_arg(main_loop, &ctx, -1, 1);
  printf("main 3 \r\n");
  return 0;
}
