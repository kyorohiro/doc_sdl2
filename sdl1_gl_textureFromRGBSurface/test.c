//
// FONT
// https://github.com/kripken/emscripten/issues/2708
// https://groups.google.com/forum/#!topic/emscripten-discuss/lfXaVdyYztw
// http://www.sdltutorials.com/sdl-ttf
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

GLfloat vertexBufferData[] = {
  -0.5f, 0.5f, 0.0f,  0.0, 0.0,
  0.5f, 0.5f, 0.0f,   1.0, 0.0,
  0.5f, -0.5f, 0.0f,  1.0, 1.0,
  -0.5f, -0.5f, 0.0f, 0.0, 1.0,

};

GLshort indexData[] = {
  0,1,2,  0,2,3
};

void main_loop(void*args) {
}





void _onInit() {
  printf("## onInit\r\n");

  glEnable(GL_DEPTH_TEST);

  //glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, width, height);
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //

  frgShader = cglu_loadShader(GL_FRAGMENT_SHADER,
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "uniform sampler2D texture;\n"
    "varying vec2 textureCoord;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(texture, textureCoord)* vec4(1.0,1.0,1.0,1.0);\n"
//    "  gl_FragColor = vec4(1.0,1.0,1.0,1.0);\n"
    "}\n");
  verShader = cglu_loadShader(GL_VERTEX_SHADER,
    "attribute vec4 position;\n"
    "attribute vec2 texCoord;\n"
    "varying vec2 textureCoord;\n"
    "void main() {\n"
    "  textureCoord = texCoord;\n"
    "  gl_Position = position;\n"
    "}\n");

  program = glCreateProgram();
  glAttachShader(program, frgShader);
  glAttachShader(program, verShader);
  glLinkProgram(program);

}

void _onDisplay() {
  //
  //
  int texture;


  SDL_Surface* image = SDL_CreateRGBSurface(
//    SDL_SWSURFACE,
    SDL_SRCALPHA,
//    SDL_HWSURFACE, 
//    SDL_SRCCOLORKEY,
    512, 512, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
     0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#else
     0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#endif
   );


  SDL_Surface *textSurface = IMG_Load("./assets/icon.png");
#ifdef PLATFORM_EMCC
  {
      char* m = image->pixels;
      char* n = textSurface->pixels;
      // for argb888 format 
      for(int i=0;i<textSurface->w;i++) {
        for(int j=0;j<textSurface->h;j++) {
          int mt = 4*(j*image->w + i);
          int nt = 4*(j*textSurface->w   + i);
            m[mt+0] = n[nt+0];
            m[mt+1] = n[nt+1];
            m[mt+2] = n[nt+2];
            m[mt+3] = n[nt+3];
        }
      }  
  }
#else
  SDL_Surface *tmp = SDL_DisplayFormat(textSurface);
  SDL_FreeSurface(textSurface);
  SDL_BlitSurface(tmp, NULL, image, NULL);
  textSurface = tmp;
//   SDL_BlitSurface(textSurface, NULL, image, NULL);
#endif
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // buffer
  GLuint vertexBuffer;
  GLuint indexBuffer;
  GLuint textureBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);
  glGenTextures(1, &textureBuffer);

  // texture
  GLenum data_fmt;
  GLint nOfColors = image->format->BytesPerPixel;
  if (nOfColors == 4) {
    if (image->format->Rmask == 0x000000ff) {
      data_fmt = GL_RGBA;
    } else {
      data_fmt = GL_BGRA;
    }
  } else if (nOfColors == 3) {
    if (image->format->Rmask == 0x000000ff){
      data_fmt = GL_RGB;
    } else {
      data_fmt = GL_BGR;
    }
  } else {
    printf("warning: the image is not truecolor..  this will probably break\n");
  }
  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, data_fmt,//GL_RGBA,//data_fmt,
      image->w, image->h, 0, data_fmt, GL_UNSIGNED_BYTE, image->pixels);
  SDL_FreeSurface(textSurface);
  SDL_FreeSurface(image);



  //
  // shader
  glUseProgram(program);
  int positionLoc = glGetAttribLocation(program, "position");
  int texCoordLoc = glGetAttribLocation(program, "texCoord");
  glEnableVertexAttribArray(positionLoc);
  glEnableVertexAttribArray(texCoordLoc);


  //
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*5*4, vertexBufferData, GL_STATIC_DRAW);

  glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3* sizeof(GLfloat)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort)*6, indexData, GL_STATIC_DRAW);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);


}


int main( int argc, char* args[] )
{
  printf("main \r\n");
  SDL_Init( SDL_INIT_EVERYTHING );

  printf("ttf init \r\n");
  if(TTF_Init()< 0) {
    printf("Failed at TTF_Init\r\n");
  }
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





