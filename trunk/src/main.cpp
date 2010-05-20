#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>

#include "render_world.h"
#include "game_state.h"
#include "menu_state.h"
#include "audio.h"
int CURRENT_STATE;
void initGl(int argc,char **argv){
	CURRENT_STATE =-1;
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("coding on calimocho");
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//CURRENT_STATE =-1;
	//start off in menu state
	set_game_state(MENU_STATE_NUMBER);

	glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT,GL_FASTEST);

	glutDisplayFunc (gameStateRender);
	glutIdleFunc(gameStateUpdate);
	glutSpecialFunc(gameStateKeyboardFunc);
	glutSpecialUpFunc(gameStateKeyboardUpFunc);
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