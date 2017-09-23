//
// Create Window
//
//#define GL_GLEXT_PROTOTYPES 1

#include <SDL.h>
#include <SDL_events.h>

#include <stdio.h>

#ifdef PLATFORM_MINGW
#include <glew.h>
#if defined(GLEW_EGL)
#include <eglew.h>
#elif defined(GLEW_OSMESA)
#define GLAPI extern
#include <osmesa.h>
#elif defined(_WIN32)
#include <wglew.h>
#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
#include <glxew.h>
#endif
#else
#include <SDL_opengl.h>
#endif


//#include <gl/glu.h>

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

#ifdef PLATFORM_MINGW
  glewExperimental = GL_TRUE; 
  GLenum glewError = glewInit();
  if( glewError != GLEW_OK ) {
      printf( "Failed at glewInit! %s\n", glewGetErrorString( glewError ) );
  }
#endif
  glClearColor(1.0, 1.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
//  printf("main 3 \r\n");
  SDL_GL_SwapWindow(window);
  SDL_Delay( 3000 );
  SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}
