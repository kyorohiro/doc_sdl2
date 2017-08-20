//
// Create Window
//
#include <SDL2/SDL.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
  SDL_Init( SDL_INIT_VIDEO );
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);

  SDL_Delay( 2000 );
  SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}

