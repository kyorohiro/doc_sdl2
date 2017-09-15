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

GLuint cglu_loadShader(GLenum type, const char *shaderSrc);

typedef struct {
  int dummy;
} Context;

Context ctx;
SDL_Surface* screen = NULL;

int frgShader;
int verShader;
int program;
int width = 400;
int height = 300;

void main_loop(void*args) {
}



GLfloat vertexBufferData[] = {
  0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f
};

GLshort indexData[] = {
  0,1,2
};

void _onInit() {
  printf("## onInit\r\n");

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, width, height);
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //

  frgShader = cglu_loadShader(GL_FRAGMENT_SHADER,
    "void main() {\n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n");
  verShader = cglu_loadShader(GL_VERTEX_SHADER,
    "attribute vec4 position;\n"
    "void main() {\n"
    "  gl_Position = position;\n"
    "}\n");

  program = glCreateProgram();
  glAttachShader(program, frgShader);
  glAttachShader(program, verShader);
  glLinkProgram(program);

}

void _onDisplay() {

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  GLuint vertexBuffer;
  GLuint indexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);

  glUseProgram(program);
  int positionLoc = glGetAttribLocation(program, "position");

  //
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*3, vertexBufferData, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort)*3, indexData, GL_STATIC_DRAW);


  glEnableVertexAttribArray(positionLoc);
  glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);


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
  _onInit();
  _onDisplay();
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




GLuint cglu_loadShader(GLenum type, const char *shaderSrc) {
  GLuint shader;
  GLint compiled;
  shader = glCreateShader(type);
  if(shader == 0) {
    return 0;
  }

  glShaderSource(shader, 1, &shaderSrc, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if(!compiled) {
    printf("Error compiling shader:\n");
    printf("src:\n%s\n", shaderSrc);
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen > 0) {
      char* infoLog = malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      printf("infolog:\n%s\n", infoLog);
      free(infoLog);
    }
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}



