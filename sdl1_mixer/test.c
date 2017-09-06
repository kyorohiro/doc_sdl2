//
// Create Window
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <stdio.h>

typedef struct {
  int dummy;
} Context;
Context ctx;

void main_loop(void*args) {
}

int main( int argc, char* args[] )
{
  printf("main \r\n");
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = NULL;
//  screen = SDL_SetVideoMode( 640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
  SDL_WM_SetCaption( "title", 0 );
  SDL_Flip( screen );
  //
  //
  printf("mixer init \r\n");
  int flags = MIX_INIT_OGG;
  int result = 0;
  if (flags != (result = Mix_Init(flags))) {
      printf("Could not initialize mixer (result: %d).\n", result);
      printf("Mix_Init: %s\n", Mix_GetError());
      SDL_Quit();
      return 0;
  }
  printf("mixer play a\r\n");
  Mix_OpenAudio(0,0,0,0);//22050, AUDIO_S16SYS, 2, 640);
  Mix_Music *music = Mix_LoadMUS("./assets/se_maoudamashii_element_thunder05.ogg");
  Mix_PlayMusic(music, 1);
  printf("mixer play b\r\n");
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
