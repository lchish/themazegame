










#include <GL/glut.h>

#include "game_state.h"
#include "menu_state.h"
#include "render_world.h"

GLuint start_button_texture,exit_button_texture,options_button_texture,header_texture;

static void init_textures(){
}
void key_pressed(unsigned char key,int x,int y){
	if(key =='m'){//transition to main game state
		set_game_state(GAME_STATE_NUMBER);
	}
}
static void menu_init_textures(){
	//start_button = genTexture("data/images/menu/start_button.raw");
}

//sets glut to use the menus rendering things
int menu_init(){
	glutDisplayFunc (menu_render);
	glutIdleFunc(menu_update);
	glutKeyboardFunc(key_pressed);

	glEnable (GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	return 0;
}

void menu_update(){
	 
}
void menu_render(){

}}
