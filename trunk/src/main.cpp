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
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("coding on calimocho");
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//CURRENT_STATE =-1;
	//start off in menu state
	set_game_state(GAME_STATE_NUMBER);
	glutDisplayFunc (gameStateRender);
	glutIdleFunc(gameStateUpdate);
	glutKeyboardFunc(gameStateKeyboardFunc);
	glutKeyboardUpFunc(gameStateKeyboardUpFunc);
	glutReshapeFunc (gameStateReshape);
	//Game code is going into the idle function at the moment..
	glutMainLoop ();
}
int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initAudio(&argc,argv);
	initGl(argc,argv);
	return EXIT_SUCCESS;
}