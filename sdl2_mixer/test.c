//
// Create Window
//
#include <SDL.h>
#include <SDL_events.h>
#include <stdio.h>

#ifdef PLATFORM_EMCC
#include <emscripten.h>
#include <SDL/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
int _isQuit = 0;
int x = 0;
int y = 0;
SDL_Surface *screen;
void main_loop(void*args) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT: x++; break;
            case SDLK_LEFT: x--; break;
            case SDLK_UP: y--; break;
            case SDLK_DOWN: y++; break;
            default: printf("Other key"); break;
        }
      case SDL_QUIT:
        _isQuit = 1;
    }
    printf("loop %d %d %d %f %f %d\r\n", x, y, event.type, event.tfinger.x, event.tfinger.y, event.key.keysym.sym);
  }
}

typedef struct {
  int dummy;
} Context;

Context ctx;

int main( int argc, char* args[] )
{
  printf("main\r\n");
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      printf("Failed to init SDL\n");
      return 0;//exit(1);
  }
  int flags = MIX_INIT_OGG;
  int result = 0;
  if (flags != (result = Mix_Init(flags))) {
      printf("Could not initialize mixer (result: %d).\n", result);
      printf("Mix_Init: %s\n", Mix_GetError());
      return 0;//exit(1);
  }
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
  Mix_OpenAudio(0,0,0,0);//22050, AUDIO_S16SYS, 2, 640);
  Mix_Music *music = Mix_LoadMUS("./assets/se_maoudamashii_element_thunder05.ogg");
  Mix_PlayMusic(music, 1);
  printf("main 2\r\n");

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
