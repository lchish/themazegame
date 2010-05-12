#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>

#include "render_world.h"
#include "game_state.h"
#include "audio.h"

void initGl(int argc,char **argv){
	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("coding on calimocho");
	
	setTempMaze();

	//Game code is going into the idle function at the moment..
	glutDisplayFunc (display);
	glutIdleFunc(idle);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(keyboardup);
	glutReshapeFunc (reshape);
	glEnable (GL_DEPTH_TEST);
    glutMainLoop ();
}
int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initAudio(argc,argv);
	initGl(argc,argv);
	return EXIT_SUCCESS;
}