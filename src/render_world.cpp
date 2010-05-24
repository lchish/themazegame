#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

#include <GL/glut.h>

#include "render_world.h"
#include "texture.h"

using namespace std;

#define PI 3.141592

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//temp
int maze[20][20];

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

bool moving = false;

/* For transitions. */
double cur_x_position;
double cur_y_position;
double cur_angle;



int can_move = true;

//textures
GLuint wall_texture;

//temporary crap for testing
void setTempMaze(void){

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			maze[i][j] = 1;
		}
	}

maze[5][6] = 0;
maze[5][7] = 0;
maze[4][6] = 0;

}

/*After being dragged onto calimocho i couldnt care less move and keyboard
methods r in rendering file*/

/*This method by Kirsten*/
void move(){


	if(moving_fowards_global){
		if(orientation == NORTH){
			if(y_position == 9 || maze[x_position][y_position+1] != 1){
printf("No");
			}
			else{
y_position++;
			}
		}
		if(orientation == SOUTH){
			if(y_position == 0 || maze[x_position][y_position-1] != 1){
				printf("No");
			}
			else{
y_position--;
		}
		}
		if(orientation == EAST){
			if(x_position == 9 || maze[x_position+1][y_position] != 1){
			printf("No");
			}
			else{
x_position++;
		}
		}
		if(orientation == WEST){
			if(x_position == 0 || maze[x_position-1][y_position] != 1){
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
	if (!moving) {
		moving = true;
		if(!turning_left_global && key == 'a'){
			turning_left_global = true;
			move();
		}

		else if(!moving_fowards_global && key == 'w'){
			moving_fowards_global = true;
			move();
		}

		else if(!turning_right_global && key == 'd'){
			turning_right_global = true;
			move();
		}
	}


	

}

static void camera(double x, double z, double angleRadians){
/*
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
		gluLookAt(x + 0.5, 0.5 , z + 0.5,0-x, 0.5, z + 0.5, 0, 1, 0); 
	}

*/
const double EYE_HEIGHT = 0.5;
//double angleRadians = orientation * (3.14159/2);
gluLookAt(x + 0.5, EYE_HEIGHT, z + 0.5, x + 0.5 + cos(angleRadians), EYE_HEIGHT, z + 0.5 + sin(angleRadians), 0, 1, 0);

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
				if(j == 9 || maze[i][j+1] != 1){
					drawWall(i,j,NORTH);
				}
			}
		}
	}



	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(i == 0 || maze[i-1][j] != 1){
					drawWall(i,j,EAST);
				}
			}
		}
	}
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(i == 9 || maze[i+1][j] != 1){
					drawWall(i, j, WEST);
				}
			}
		}
	}

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(maze[i][j] == 1){
				if(j == 0 || maze[i][j-1] != 1){
					drawWall(i,j, SOUTH);
				}
			}
		}
	}

}


/*Idalin*/
/*
void idle(void){

	if(turning_left_global == true || turning_right_global == true || moving_fowards_global == true){

		move();

		glutPostRedisplay();
	}
//printf("%d %d %d\n", turning_left_global, moving_fowards_global, turning_right_global);


	//printf("x: %d y: %d orient: %d\n", x_position, y_position, orientation);

}
*/
/*Display function - called from main*/
void display(void){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor (0.0,0.0,0.0,1.0);

	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	camera(cur_x_position, cur_y_position, cur_angle);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

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

	x_position = 1;
	y_position = 1;

	/* For transitions. */
	cur_x_position = 1.0;
	cur_y_position = 1.0;
	cur_angle = PI / 2;

	init_textures();
	setTempMaze();
	return 0;
}
int gameDeInit(){
	free_textures();
	return 0;
}


void gameStateTimerFunc(int value) {

	bool needs_render = false;
	double angle;
	switch (orientation) {
		case NORTH:
			angle = PI / 2;
			break;
		case EAST:
			angle = 0.0;
			break;
		case SOUTH:
			angle = 3 * PI / 2;
			break;
		case WEST:
			angle = PI;
			break;
		default:
			angle = 0.0;
	}

	if (abs(cur_x_position - x_position) < 0.1) {
		cur_x_position = x_position;
	}
	if (abs(cur_y_position - y_position) < 0.1) {
		cur_y_position = y_position;
	}
	if (cur_angle >= 2 * PI) cur_angle -= 2*PI;
	if (cur_angle < 0) cur_angle += 2*PI;
	if (abs(cur_angle - angle) < (PI / 2) / 10) {
		cur_angle = angle;
	}

	if(cur_x_position < x_position){
		cur_x_position += 0.1;
		needs_render = true;
	}else if(cur_x_position > x_position){
		cur_x_position -= 0.1;
		needs_render = true;
	}

	if(cur_y_position < y_position){
		cur_y_position += 0.1;
		needs_render = true;
	}else if(cur_y_position > y_position){
		cur_y_position -= 0.1;
		needs_render = true;
	}

	double angle_diff = angle - cur_angle;
	if (angle_diff > PI) {
		angle_diff = -(PI * 2 - angle_diff);
	}else if (angle_diff < -PI) {
		angle_diff = 360 + angle_diff;
	}

	if(angle_diff > 0.0){
		cur_angle += (PI / 2) / 10;
		needs_render = true;
	}else if(angle_diff < 0.0){
		cur_angle -= (PI / 2) / 10;
		needs_render = true;
	}

	if (needs_render) {
		moving = true;
		glutPostRedisplay();
	}else{
		moving = false;
	}
	glutTimerFunc(100, gameStateTimerFunc, value);
}