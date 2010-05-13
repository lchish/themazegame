#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>

#include "render_world.h"
#include "game_state.h"
#include "menu_state.h"
#include "audio.h"

void initGl(int argc,char **argv){
	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("coding on calimocho");
	
	//start off in menu state
	set_game_state(MENU_STATE_NUMBER);
	//menu_init();
	init_textures();
	setTempMaze();

	//Game code is going into the idle function at the moment..
	glutDisplayFunc (display);
	glutIdleFunc(idle);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(keyboardup);
	glutReshapeFunc (reshape);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    glutMainLoop ();
	//when we exit loop consider deleting textures to make andrew happy about mememory leaks.
}
int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initAudio(&argc,argv);
	initGl(argc,argv);
	return EXIT_SUCCESS;
}