#include <cstdio>
#include <cstdlib>
#include <string>
#include <GL/glut.h>

#include "render_world.h"
#include "texture.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//temp
int maze[10][10];

//temp
int player_X;
int player_Y;
int player_direction;

int turning_left_global;
int turning_right_global;
int moving_fowards_global;

int x_position;
int y_position;
int orientation;

//textures
GLuint wall_texture;

//temporary crap for testing
void setTempMaze(void){
	maze[0][0] = 1;
	maze[0][1] = 1;
	maze[0][2] = 1;
	maze[0][3] = 1;
	maze[0][4] = 1;
	maze[1][4] = 1;
	maze[1][5] = 1;
	maze[2][5] = 1;
	maze[3][5] = 1;
	maze[4][5] = 1;
	maze[5][5] = 1;
	maze[6][5] = 1;
	maze[7][5] = 1;
}

/*After being dragged onto calimocho i couldnt care less move and keyboard
methods r in rendering file*/

/*This method by Kirsten*/


void move(int moving_forwards, int turning_left, int turning_right){
	if(moving_forwards == 1){
		if(orientation == 0){
			if(y_position > 0){
				y_position = y_position -1;
			}
		}else if(orientation == 1){
			x_position = x_position +1;
		}else if(orientation == 2){
			y_position = y_position +1;
		}else {
			if(x_position > 0){
				x_position = x_position -1;
			}
		}

	}else if(turning_left == 1){
		if(orientation == 0){
			orientation = 3;
		}else if(orientation == 1){
			orientation = 0;
		}else if(orientation == 2){
			orientation = 1;
		}else {
			orientation = 2;
		}
	}else if(turning_right == 1){
		if(orientation == 0){
			orientation = 1;
		}else if(orientation == 1){
			orientation = 2;
		}else if(orientation == 2){
			orientation = 3;
		}else {
			orientation = 0;
		}
	}
}

void keyboardup(unsigned char key, int x, int y)
{
	if (key == 'a'){
		turning_left_global = false;
		printf("Left key depressed");
	}
	else if(key == 'd'){
		turning_right_global = false;
	printf("Right key cvdepressed");
	}

	else if(key == 'w'){
		printf("Fowards key depressed");
		moving_fowards_global = false;
	}
}


/*God this should not be in here hahaha*/

/*Using WASD at the moment since I cant be fucked changing them
to the arrow keys*/
void processNormalKeys(unsigned char key, int x, int y){
	printf("Processing");

	if(key == 'a'){
		turning_left_global = true;
		printf("Left key pressed\n");
	}

	else if(key == 'w'){
		moving_fowards_global = true;
		printf("Fowards key pressed\n");
	}

	else if(key == 'd'){
		turning_right_global = true;
		printf("Right key pressed\n");
	}

}

static void camera(int x, int z, int orientation){
	
	if(orientation == NORTH){
gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 0.5, 0.5, z+1, 0, 1, 0); 
	}

	else if(orientation == EAST){
gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 1, 0.5, z + 0.5, 0, 1, 0); 
	}

	else if(orientation == SOUTH){
gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 0.5, 0.5, 0-z, 0, 1, 0); 
	}
	else if(orientation == WEST){
gluLookAt(x + 0.5, 0.5 , z + 0.5,0-x -1, 0.5, z + 0.5, 0, 1, 0); 
	}

	/*
	   double angleRadians = orientation * 3.14159/180;
    gluLookAt(x+0.5,0.5,z+0.5, x + sin(angleRadians), z + cos(angleRadians),orientation, 0,1,0);
	*/
}

/*Draw a single floor tile*/
void drawFloorTile(int i, int j){

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f + i, 0.0f,1.0f + j);
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex3f(1.0f + i, 0.0f,1.0f + j);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f + i,0.0f, 0.0f + j);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f + i,0.0f, 0.0f + j);
	glEnd();
}
/*Draw a single textured wall*/
void drawWall(int i, int j, int direction){
	glBindTexture(GL_TEXTURE_2D,wall_texture);
	glColor3f(1.0f,1.0f,1.0f);//reset the colour or everything is to dark

	if(direction == SOUTH){

		glBegin(GL_QUADS);
		glTexCoord2d(0.0,1.0); glVertex3f(0.0f + i, 1.0f , 0.0f+j);
		glTexCoord2d(1.0,1.0); glVertex3f(1.0f + i, 1.0f , 0.0f+j);
		glTexCoord2d(1.0,0.0); glVertex3f(1.0f + i, 0.0f, 0.0f+j);
		glTexCoord2d(0.0,0.0); glVertex3f(0.0f + i, 0.0f , 0.0f+j);
		glEnd();
	}


	else if(direction == NORTH){

		glBegin(GL_QUADS);
		glTexCoord2d(0.0,1.0); glVertex3f(0.0f + i, 1.0f , 1.0f+j);
		glTexCoord2d(1.0,1.0); glVertex3f(1.0f + i, 1.0f , 1.0f+j);
		glTexCoord2d(1.0,0.0); glVertex3f(1.0f + i, 0.0f, 1.0f+j);
		glTexCoord2d(0.0,0.0); glVertex3f(0.0f + i, 0.0f , 1.0f+j);
		glEnd();
	}


	else if(direction == EAST){

		glBegin(GL_QUADS);
		glTexCoord2d(0.0,1.0);glVertex3f(0.0f + i, 1.0f , 0.0f + j);
		glTexCoord2d(1.0,1.0);glVertex3f(0.0f + i, 1.0f , 1.0f + j);
		glTexCoord2d(1.0,0.0);glVertex3f(0.0f + i, 0.0f , 1.0f + j);
		glTexCoord2d(0.0,0.0);glVertex3f(0.0f+ i, 0.0f , 0.0f + j);
		glEnd();
	}

	else if(direction == WEST){
		glBegin(GL_QUADS);
		glTexCoord2d(0.0,1.0);glVertex3f(1.0f + i, 1.0f, 0.0f + j);
		glTexCoord2d(1.0,1.0);glVertex3f(1.0f + i, 1.0f , 1.0f + j);
		glTexCoord2d(1.0,0.0);glVertex3f(1.0f + i, 0.0f , 1.0f + j);
		glTexCoord2d(0.0,0.0);glVertex3f(1.0f + i, 0.0f , 0.0f + j);
		glEnd();
	}

}


/*Draw all the floor*/
void drawFloor(void){

	int i, j;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){

			if(maze[i][j] == 1){
				drawFloorTile(i,j);
			}
		}
	}

}

/*Draw all the walls*/
void drawWalls(void){
	int i, j;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){

			if(maze[i][j] == 1){
				if(maze[i][j+1] != 1){
					drawWall(i,j,NORTH);
				}
			}
		}
	}



	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(maze[i-1][j] != 1){
					drawWall(i,j,EAST);
				}
			}
		}
	}
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(maze[i+1][j] != 1){
					drawWall(i, j, WEST);
				}
			}
		}
	}

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(maze[i][j-1] != 1){
					drawWall(i,j, SOUTH);
				}
			}
		}
	}

}


/*Idalin*/
void idle(void){
	move(turning_left_global, moving_fowards_global, turning_right_global);

	glutPostRedisplay();
}

/*Display function - called from main*/
void display(void){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor (0.0,0.0,0.0,1.0);
	glLoadIdentity();

	camera(x_position, y_position, orientation);
	//gluLookAt (0.5, 0.5, 0.5,0.5, 0.5, 5, 0, 1.0, 0);


	/*Waiting for camera function from ARUN*/
	//camera(0, 0, NORTH);

	drawFloor(); 
	drawWalls();

	/*
	glutPostRedisplay();
	glFlush();
	*/


	glutSwapBuffers();


}


/*Reshape also called from main*/
void reshape (int w, int h) {

	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void init_textures(){
	wall_texture = genTexture("data/images/textures/wall.bmp");
}
void free_textures(){
	glDeleteTextures( 1, &wall_texture );
}