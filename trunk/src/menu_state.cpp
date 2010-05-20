#include <GL/glut.h>

#include "game_state.h"
#include "menu_state.h"
#include "render_world.h"
#include "texture.h"

GLuint start_button_texture,exit_button_texture,options_button_texture,header_texture;

static void init_textures(){
}
void menuKeyPressed(unsigned char key,int x,int y){
	if(key =='m'){//transition to main game state
		set_game_state(GAME_STATE_NUMBER);
	}
}
static void menu_init_textures(){
	//start_button = genTexture("data/images/menu/start_button.raw");
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
		glutSwapBuffers();
}
//sets glut to use the menus rendering things
int menuInit(){
	menu_init_textures();
	return 0;
}
int menuDeInit(){
	menu_free_textures();
	return 0;
}