//
// Create Window
//
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_opengl.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
  printf("main\r\n");
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window;
  SDL_GLContext glContext;
  //SDL_Renderer* renderer;
  //SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);
  window = SDL_CreateWindow("sdlglshader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
  //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  glContext = SDL_GL_CreateContext(window);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
//  SDL_RenderClear(renderer);
//
//  SDL_RenderPresent(renderer);
//  printf("main 2\r\n");
//  emscripten_set_main_loop_arg(main_loop, &ctx, 60, 1);
//  printf("main 3 \r\n");
  SDL_GL_SwapWindow(window);
  SDL_Delay( 20000 );
  SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}
