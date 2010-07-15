#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "main_game.h"
#include "game_state.h"
#include "menu_state.h"
#include "globals.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/*The current game state - Menu, main game state etc...*/
int CURRENT_STATE;
bool quit = false;

/* Initialise the sdl surface */
int initSDL(){
  if(SDL_Init(SDL_INIT_VIDEO) !=0){
    fprintf(stderr,"Unable to init sdl: %s\n",SDL_GetError());
    return false;
  }
  atexit(SDL_Quit);
  //To use OpenGL, you need to get some information first,
  const SDL_VideoInfo *info = SDL_GetVideoInfo();
  if(!info) {
    /* This should never happen, if it does PANIC! */
    fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
    return false;
  }
  int bpp = info->vfmt->BitsPerPixel;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, bpp,
		       SDL_OPENGL | SDL_SWSURFACE) == 0) {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
  SDL_WM_SetCaption("The maze game",0);
  return true;
}

/*Initalize all the openGL code*/
void initGl(){
	CURRENT_STATE =-1;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//check for anistropic filtering options
	if(!strstr((char*)glGetString(GL_EXTENSIONS),
		   "GL_EXT_texture_filter_anisotropic")){
	  anisotropic_filtering = false;
	}else{
	  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anistropy);
	  anisotropic_filtering = true;
	}
	//start off in menu state
	set_game_state(MENU_STATE_NUMBER);
	/*No idea what this does?*/
	glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT,GL_FASTEST);
}

void handleInput(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_KEYDOWN:
      //for debugging
      printf("The %s key was pressed!\n",SDL_GetKeyName(event.key.keysym.sym));

      if(event.key.keysym.sym == SDLK_ESCAPE){
	quit=true;
	break;
      }
      gameStateKeyboardDown(event.key.keysym.sym);
      break;
    case SDL_KEYUP:
      gameStateKeyboardUp(event.key.keysym.sym);
      break;
    case SDL_QUIT:
      quit = true;
      break;
      /** mouse stuff if we ever need it
    case SDL_MOUSEMOTION:
      MouseMoved(
		 event.button.button, 
		 event.motion.x, 
		 event.motion.y, 
		 event.motion.xrel, 
		 event.motion.yrel);
      break;
      
    case SDL_MOUSEBUTTONUP:
      MouseButtonUp(
		    event.button.button, 
		    event.motion.x, 
		    event.motion.y, 
		    event.motion.xrel, 
		    event.motion.yrel);
      break;
      
    case SDL_MOUSEBUTTONDOWN:
      MouseButtonDown(
		      event.button.button, 
		      event.motion.x, 
		      event.motion.y, 
		      event.motion.xrel, 
		      event.motion.yrel);
      break;
      */
    }
  }
}

void update(){
  handleInput();
  gameStateUpdate();
}

void render(){
  gameStateRender();
}

void gameMainLoop(){
  while(!quit){
    update();
    render();
  }
}

int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initSDL();



	initGl();
	gameMainLoop();
	return EXIT_SUCCESS;
}
