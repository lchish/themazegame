#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

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

int maze_size = 07;

//temp
/*
int player_X;
int player_Y;
int player_direction;
*/
int turning_left_global;
int turning_right_global;
int moving_fowards_global;


int x_position;
int y_position;
int orientation;



int can_move = true;

//textures
GLuint wall_texture;

//temporary crap for testing
void setTempMaze(void){


	for(int i = 0; i < maze_size; i++){
		for(int j = 0; j < maze_size; j++){
			maze[i][j] = 0;
		}
	}

maze[1][0] = 1;
maze[2][0] = 1;
maze[3][0] = 1;
maze[5][0] = 1;
maze[6][0] = 1;
maze[0][1] = 1;
maze[1][1] = 1;
maze[3][1] = 1;
maze[5][1] = 1;
maze[1][2] = 1;
maze[2][2] = 1;
maze[3][2] = 1;
maze[4][2] = 1;
maze[5][2] = 1;
maze[6][2] = 1;
maze[1][3] = 1;
maze[3][3] = 1;
maze[6][3] = 1;
maze[0][4] = 1;
maze[1][4] = 1;
maze[2][4] = 1;
maze[5][4] = 1;
maze[6][4] = 1;
maze[2][5] = 1;
maze[3][5] = 1;
maze[4][5] = 1;
maze[2][6] = 1;


}

/*After being dragged onto calimocho i couldnt care less move and keyboard
methods r in rendering file*/

/*This method by Kirsten*/
void move(){


	if(moving_fowards_global){
		if(orientation == NORTH){
			if(maze[x_position][y_position+1] != 1){
printf("No");
			}
			else{
y_position++;
			}
		}
		if(orientation == SOUTH){
			if(maze[x_position][y_position-1] != 1){
				printf("No");
			}
			else{
y_position--;
		}
		}
		if(orientation == EAST){
			if(maze[x_position+1][y_position] != 1){
			printf("No");
			}
			else{
x_position++;
		}
		}
		if(orientation == WEST){
			if(maze[x_position-1][y_position] != 1){
				printf("No");
			}
			else{
x_position--;
		}
		}
			
	}


	if(turning_right_global){
		if(orientation == 0){
	orientation = 3;
		}
		else{
orientation--;
		}
	}
	if(turning_left_global){
		if(orientation == 3){
orientation = 0;
		}
		else{
orientation++;
		}

	}



	printf("At: %d, %d Looking at Position:%d \n", x_position, y_position, orientation);

	moving_fowards_global = 0;
	turning_left_global = 0;
	turning_right_global = 0;
}





void keyboardup(unsigned char key, int x, int y)
{
	
	printf("%c\n", key);
	if (key == 'a'){
		turning_left_global = false;
	}
	else if(key == 'd'){
		turning_right_global = false;
	}

	else if(key == 'w'){
		moving_fowards_global = false;
	}

}


/*God this should not be in here hahaha*/

/*Using WASD at the moment since I cant be fucked changing them
to the arrow keys*/
void processNormalKeys(unsigned char key, int x, int y){

	printf("%c\n", key);
	
	if(key == 'a'){
		turning_left_global = true;
		
	}

	else if(key == 'w'){
		moving_fowards_global = true;
	}

	else if(key == 'd'){
		turning_right_global = true;
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


	///change
	else if(orientation == WEST){
		gluLookAt(x + 0.5, 0.5 , z + 0.5,-x-1, 0.5, z + 0.5, 0, 1, 0); 
	}


	/*
	        const double EYE_HEIGHT = 0.5;
        double angleRadians = orientation * (3.14159/2);
        gluLookAt(x + 0.5, EYE_HEIGHT, z + 0.5, x + 0.5 + cos(angleRadians), EYE_HEIGHT -
0.2, z + 0.5 + sin(angleRadians), 0, 1, 0);
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

	for(i = 0; i < maze_size; i++){
		for(j = 0; j < maze_size; j++){

			if(maze[i][j] == 1){
				drawFloorTile(i,j);
			}
		}
	}

}

/*Draw all the walls*/
void drawWalls(void){
	int i, j;

	for(i = 0; i < maze_size; i++){
		for(j = 0; j < maze_size; j++){

			if(maze[i][j] == 1){
				if(maze[i][j+1] != 1){
					drawWall(i,j,NORTH);
				}
			}
		}
	}



	for(i = 0; i < maze_size; i++){
		for(j = 0; j < maze_size; j++){
			if(maze[i][j] == 1){
				if(maze[i-1][j] != 1){
					drawWall(i,j,EAST);
				}
			}
		}
	}
	for(i = 0; i < maze_size; i++){
		for(j = 0; j < maze_size; j++){
			if(maze[i][j] == 1){
				if(maze[i+1][j] != 1){
					drawWall(i, j, WEST);
				}
			}
		}
	}

	for(i = 0; i < maze_size; i++){
		for(j = 0; j < maze_size; j++){
			if(maze[i][j] == 1){
				if(maze[i][j-1] != 1){
					drawWall(i,j, SOUTH);
				}
			}
		}
	}

}




/*Idalin*/
//void idle(void){
void idle(void){
	if(turning_left_global == true || turning_right_global == true || moving_fowards_global == true){

	move();
	}
//printf("%d %d %d\n", turning_left_global, moving_fowards_global, turning_right_global);


	

	glutPostRedisplay();

	//printf("x: %d y: %d orient: %d\n", x_position, y_position, orientation);

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

static void init_textures(){
	wall_texture = genTexture("data/images/textures/wall.bmp");
}
static void free_textures(){
	glDeleteTextures( 1, &wall_texture );
}
//move this out sometime people
int gameInit(){

	x_position = 0;
	y_position = 1;
	orientation = WEST;


	init_textures();
	setTempMaze();
	return 0;


}
int gameDeInit(){
	free_textures();
	return 0;
}