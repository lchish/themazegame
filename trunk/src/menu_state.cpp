//put some comments in here les
// the menu
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "game_state.h"
#include "menu_state.h"
#include "render_world.h"
#include "texture.h"
#include "audio.h"

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
  header_texture = genTexture("data/images/menu/title.png");
  start_button_texture = genTexture("data/images/menu/start.png");
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
  glTexCoord2d(0.0,0.0); glVertex2f(-0.75,-0.75);
  glTexCoord2d(1.0,0.0); glVertex2f(0.75, -0.75);
  glTexCoord2d(1.0,1.0); glVertex2f(0.75, 0.75);
  glTexCoord2d(0.0,1.0); glVertex2f(-0.75, 0.75);
  glEnd();
  glBindTexture(GL_TEXTURE_2D,start_button_texture);
  SDL_GL_SwapBuffers();
}

static void menu_init_sounds(){
  //when I create a music file will put it in here
  //we'll also need to start it here I think
}
static void menu_free_sounds(){
  //ditto also stop it
}
int menuInit(){
  menu_init_textures();
  menu_init_sounds();
  return 0;
}
int menuDeInit(){
  menu_free_textures();
  menu_free_sounds();
  return 0;
}