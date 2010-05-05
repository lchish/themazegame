

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>



#include "game_state.h"
#include "audio.h"


int main (int argc,char **argv){
	std::cout << "Starting Game" << std::endl;
	//game code goes here
	initAudio(argc,argv);
	return EXIT_SUCCESS;
}