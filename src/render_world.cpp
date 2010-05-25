#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

#include <GL/glut.h>

#include "render_world.h"
#include "texture.h"
#include "defs.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


/*The maze floor is on the X-Z axis, and the walls get drawn on the Y axis*/
int maze[10][10];
int maze_size = 07;

/* For move function */
bool turning_left_global;
bool turning_right_global;
bool moving_fowards_global;


/*Our player data structure - Where we are in the world */
int x_position;
int y_position;
int orientation;

/*Where we start*/
int start_x = 0;
int start_y = 1;


/*Textures*/
GLuint wall_texture;
GLuint floor_texture;


/*Set temporary maze only for beta  TO be removed later*/
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




/*Modifies the players position/orientation based
	on input variables such as moving_fowards_global*/
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


	/*If these aren't reset the player races off at the speed of light*/
	moving_fowards_global = 0;
	turning_left_global = 0;
	turning_right_global = 0;
}




/*Called when a key is released*/
void keyboardup(int key, int x, int y)
{

	if (key == GLUT_KEY_LEFT){
		turning_left_global = false;
	}
	else if(key == GLUT_KEY_RIGHT){
		turning_right_global = false;
	}

	else if(key == GLUT_KEY_UP){
		moving_fowards_global = false;
	}

}


/*Called when a key is pressed*/
void processNormalKeys(int key, int x, int y){

	if(key == GLUT_KEY_LEFT){
		turning_left_global = true;
		
	}

	else if(key == GLUT_KEY_UP){
		moving_fowards_global = true;
	}

	else if(key == GLUT_KEY_RIGHT){
		turning_right_global = true;
	}
	

}

/*Temporary camera function - called before redrawing the graphics*/
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

}





/*Draw a single floor tile*/
void drawFloorTile(int i, int j){

glBindTexture( GL_TEXTURE_2D, floor_texture );
	glBegin(GL_QUADS);	
	glTexCoord3d(0.0 , 0.0, 1.0); glVertex3f(0.0f + i, 0.0f,1.0f + j);

	glTexCoord3d(1.0 , 0.0, 1.0); glVertex3f(1.0f + i, 0.0f,1.0f + j);

	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(1.0f + i,0.0f, 0.0f + j);

	glTexCoord3d(0.0, 0.0, 0.0);glVertex3f(0.0f + i,0.0f, 0.0f + j);
	glEnd();

}
/*Draw a single textured wall*/
void drawWall(int i, int j, int direction){

  glBindTexture( GL_TEXTURE_2D, wall_texture );

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
					//drawWall(i, j, WEST);
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


/*Our main game function.. checks for input, moves and redraws the screen.

Needs to be changed to a timer function later so it dosen't hog 100%cpu, and
also needs to be moved to main_game*/

void idle(void){

	if(turning_left_global == true || turning_right_global == true || moving_fowards_global == true){
	move();
	}
	glutPostRedisplay();
}



/*Display function - called from main - This function is called as often as possible - Whenever the idle loop
	finishes*/
void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera(x_position, y_position, orientation);

	drawFloor(); 
	drawWalls();

	glutSwapBuffers();

}


/*Reshape also called from main - This gets called once at the start of the game
	and then whenever the window gets resized*/
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	/*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
	gluPerspective (80, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode (GL_MODELVIEW);	
}


/*Leslies code*/
static void init_textures(){
	wall_texture = genTexture("data/images/textures/wall.bmp");
	floor_texture = genTexture("data/images/textures/floor.bmp");
}

static void free_textures(){
	glDeleteTextures( 1, &wall_texture );
	glDeleteTextures(1, &floor_texture);
}


//This code will need to be moved to main_game later.
/*Initialization of the game*/
int gameInit(){

	x_position = start_x;
	y_position = start_y;
	orientation = WEST;


	init_textures();
	setTempMaze();


reshape(800, 600);

//reshape(wid, hei);

	return 0;


}
int gameDeInit(){
	free_textures();
	return 0;
}