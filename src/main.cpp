#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>

#include "render_world.h"
#include "game_state.h"
#include "menu_state.h"
#include "audio.h"

/*The current game state - Menu, main game state etc...*/
int CURRENT_STATE;

/*Initalize all the openGL code*/
void initGl(int argc,char **argv){
	CURRENT_STATE =-1;
	glutInit (&argc, argv);
	//double buffering
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("The Maze Game");

	/*Enable depth testing, and textures. Depth testing means
		objects far away wont get drawn in front of close ones*/
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//CURRENT_STATE =-1;

	//start off in menu state
	set_game_state(MENU_STATE_NUMBER);
	/*No idea what this does?*/
	glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT,GL_FASTEST);

	/*Glut stuff that needs to be defined*/
	//when the window gets redawn
	glutDisplayFunc (gameStateRender);
	//when nothing is happening
	glutIdleFunc(gameStateUpdate);
	//keyboard being pressed down
	glutSpecialFunc(gameStateKeyboardFunc);
	//keyboard being released
	glutSpecialUpFunc(gameStateKeyboardUpFunc);
	//window being reshaped
	glutReshapeFunc (gameStateReshape);
	/*
	glutKeyboardFunc(gameStateKeyboardFunc);
	glutKeyboardUpFunc(gameStateKeyboardUpFunc);
	*/
	//Game code is going into the idle function at the moment..
	//idle function needs to be changed to a timer function
	glutMainLoop ();
}
int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initAudio(&argc,argv);
	initGl(argc,argv);
	return EXIT_SUCCESS;
}