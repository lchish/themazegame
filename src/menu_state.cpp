/**
 * This is the main menu that inits and draws the menu textures
 * and waits for the user to start the game.
 */
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "game_state.h"
#include "menu_state.h"
#include "render_world.h"
#include "texture.h"
#include "audio.h"
#include "defs.h"

GLuint start_button_texture,exit_button_texture,options_button_texture,
  header_texture;
Mix_Music *menu_music;

void menuKeyUp(SDLKey key){
  if(key == SDLK_SPACE){
    set_game_state(GAME_STATE_NUMBER);
  }
}

void menuKeyDown(SDLKey key){
	
}

static void menu_init_textures(){
  header_texture = genMipMapTexture("data/images/menu/title.tga");
  //start_button_texture = genTexture("data/images/menu/start.png");
}

static void menu_free_textures(){
  glDeleteTextures( 1, &header_texture);
  glDeleteTextures( 1, &start_button_texture);
}

void menuUpdate(){

}

void menuRender(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.5f,0.5f,0.5f);
  glBindTexture(GL_TEXTURE_2D,header_texture);
   glBegin(GL_QUADS);
  //x y
  glTexCoord2d(0.0,1.0); glVertex3f(0.0f, 1.0f , 0.0f);
  glTexCoord2d(1.0,1.0); glVertex3f(1.0f, 1.0f , 0.0f);
  glTexCoord2d(1.0,0.0); glVertex3f(1.0f, 0.0f, 0.0f);
  glTexCoord2d(0.0,0.0); glVertex3f(0.0f, 0.0f , 0.0f);
  glEnd();
  SDL_GL_SwapBuffers();
}
static void menuReshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  /*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
  glMatrixMode (GL_MODELVIEW);  
  glOrtho(0, 1, 0, 1, 0, 1);
}
static void menu_init_sounds(){
}
static void menu_free_sounds(){
}
int menuInit(){
  menuReshape(SCREEN_WIDTH,SCREEN_HEIGHT);
  menu_init_textures();
  menu_init_sounds();
  return 0;
}
int menuDeInit(){
  menu_free_textures();
  menu_free_sounds();
  return 0;
}
