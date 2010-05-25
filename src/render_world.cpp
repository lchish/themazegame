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

//temp
int maze[10][10];

int maze_size = 07;

int wid;
int hei;

//temp

int font=(int)GLUT_BITMAP_8_BY_13;

bool turning_left_global;
bool turning_right_global;
bool moving_fowards_global;


int x_position;
int y_position;
int orientation;


int win_x = 5;
int win_y = 4;

int start_x = 0;
int start_y = 1;



//textures
GLuint wall_texture;
GLuint floor_texture;



void renderBitmapCharacter(float x, float y,  void *font,char *string)
{
  
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

double distanceBetween(double xA, double yA, double xB, double yB){

return sqrt((pow(xB-xA, 2)+(pow(yB-yA, 2))));

}


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





void keyboardup(int key, int x, int y)
{
	
	printf("%c\n", key);
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


/*God this should not be in here hahaha*/

/*Using WASD at the moment since I cant be fucked changing them
to the arrow keys*/
void processNormalKeys(int key, int x, int y){

	printf("%c\n", key);
/*	
	if(key == 'a'){
		turning_left_global = true;
		
	}

	else if(key == 'w'){
		moving_fowards_global = true;
	}

	else if(key == 'd'){
		turning_right_global = true;
	}
*/
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

glBindTexture( GL_TEXTURE_2D, floor_texture );
	glBegin(GL_QUADS);	
	glTexCoord3d(0.0 , 0.0, 1.0); glVertex3f(0.0f + i, 0.0f,1.0f + j);

	glTexCoord3d(1.0 , 0.0, 1.0); glVertex3f(1.0f + i, 0.0f,1.0f + j);

	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(1.0f + i,0.0f, 0.0f + j);

	glTexCoord3d(0.0, 0.0, 0.0);glVertex3f(0.0f + i,0.0f, 0.0f + j);
	glEnd();

	/*
glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f + i, 0.0f,1.0f + j);
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex3f(1.0f + i, 0.0f,1.0f + j);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f + i,0.0f, 0.0f + j);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f + i,0.0f, 0.0f + j);
	*/
}
/*Draw a single textured wall*/
void drawWall(int i, int j, int direction){

	//printf("%d %d %d", i, j, direction);
	

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

/*Idalin*/
//void idle(void){
void idle(void){





	if(turning_left_global == true || turning_right_global == true || moving_fowards_global == true){
	move();
	}
	glutPostRedisplay();
}



/*Display function - called from main*/
void display(void){

	//test
//glMatrixMode(GL_MODELVIEW);

	//glViewport (0, 0, (GLsizei)w, (GLsizei)h);

	/*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
	//gluPerspective (80, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Wherp wherp*/

	//gluPerspective(45,ratio,1,1000);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor (0.0,0.0,0.0,1.0);
	glLoadIdentity();

	camera(x_position, y_position, orientation);
//renderBitmapCharacher(0,0,0,(void *)font,"3D Tech");


glDisable(GL_TEXTURE_2D);
	renderBitmapCharacter(100, 120, GLUT_BITMAP_HELVETICA_18, "Sup");
glEnable(GL_TEXTURE_2D);

//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();

	drawFloor(); 
	drawWalls();


	//glFlush();
	glutSwapBuffers();

}


/*Reshape also called from main*/
void reshape (int w, int h) {
wid = w;
hei = h;



	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	/*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
	gluPerspective (80, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Wherp wherp*/
	
	glMatrixMode (GL_MODELVIEW);
	//gluPerspective(45,ratio,1,1000);
}

static void init_textures(){
	wall_texture = genTexture("data/images/textures/wall.bmp");
	floor_texture = genTexture("data/images/textures/floor.bmp");
}
static void free_textures(){
	glDeleteTextures( 1, &wall_texture );
	glDeleteTextures(1, &floor_texture);
}
//move this out sometime people
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