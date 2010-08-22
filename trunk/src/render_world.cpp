#include <cstdio>
#include <cstdlib>
#include <iostream> //added by arun
#include <string>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_mixer.h>

#include "defs.h"
#include "render_world.h"
#include "texture.h"
#include "main_game.h"
#include "maze.h"



using namespace std;

Maze maze_render;

/*Textures*/
GLuint wall_texture;
GLuint floor_texture;

//for finish tile. Floor only.
GLuint finish_texture;

/*************ADDED BY ARUN**********************/

bool moving = false;
/* For transitions. */
double cur_x_position;
double cur_y_position;
double cur_angle;
bool is_first_animation = true;
/***********************************************/

void set_maze(Maze target){
  maze_render = target;


}


/*Temporary camera function - called before redrawing the graphics
  void camera(int x, int z, int orientation){
  if(orientation == NORTH){
  gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 0.5, 0.5, z+1, 0, 1, 0); 
  }
  else if(orientation == EAST){
   
  gluLookAt(x + 0.5, 0.5 , z + 0.5,-x-1, 0.5, z + 0.5, 0, 1, 0); 
  }
  else if(orientation == SOUTH){
  gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 0.5, 0.5, 0-z, 0, 1, 0); 
  }
  ///change
  else if(orientation == WEST){

  gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 1, 0.5, z + 0.5, 0, 1, 0); 
  }
  } */

/*************ADDED BY ARUN**********************/
//method camera function which takes in the values co-ordinates and sets the camera in
//the current position.
static void camera(double x, double z, double angleRadians){
  //the y value (EYE_HEIGHT) does not change, so it looks like a first person view.
  const double EYE_HEIGHT = 0.5;
  //gluLookAt is used here to position the camera in the centre of the current grid square,
  //looking out in the direction given by angleRadians
  gluLookAt(x + 0.5, EYE_HEIGHT, z + 0.5, x + 0.5 + cos(angleRadians), EYE_HEIGHT, z + 0.5 + sin(angleRadians), 0, 1, 0);
	
}

/***********************************************************************/

/*Draw a single floor tile*/
void drawFloorTile(int i, int j){

  if(i == end_x && j == end_y){
    glColor3f(1.0, 0.0, 0.0);
  }


  if(i == end_x && j == end_y){
    glBindTexture(GL_TEXTURE_2D, finish_texture);
  }
  else{
    glBindTexture( GL_TEXTURE_2D, floor_texture );
  }
  glBegin(GL_QUADS);	
  glTexCoord3d(0.0 , 1.0, 0.0); glVertex3f(0.0f + i, 0.0f,1.0f + j);

  glTexCoord3d(1.0 , 1.0, 0.0); glVertex3f(1.0f + i, 0.0f,1.0f + j);

  glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(1.0f + i,0.0f, 0.0f + j);

  glTexCoord3d(0.0, 0.0, 0.0);glVertex3f(0.0f + i,0.0f, 0.0f + j);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);

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
  else if(direction == WEST){
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,1.0);glVertex3f(0.0f + i, 1.0f , 0.0f + j);
    glTexCoord2d(1.0,1.0);glVertex3f(0.0f + i, 1.0f , 1.0f + j);
    glTexCoord2d(1.0,0.0);glVertex3f(0.0f + i, 0.0f , 1.0f + j);
    glTexCoord2d(0.0,0.0);glVertex3f(0.0f+ i, 0.0f , 0.0f + j);
    glEnd();
  }
  else if(direction == EAST){
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

  for(i = 0; i < N_ROWS; i++){
    for(j = 0; j < N_COLUMNS; j++){

      drawFloorTile(i,j);
      
    }
  }

}



/*Draw all the walls*/
void drawWalls(void){
  int i, j;


  
  for(i = 0; i < N_ROWS; i++){
    for(j = 0; j < N_COLUMNS; j++){



      if(maze_render.value_at(i, j, NORTH) == 1){
	drawWall(i, j, NORTH);
      }
      if(maze_render.value_at(i, j, SOUTH) == 1){
	drawWall(i, j, SOUTH);
      }
      if(maze_render.value_at(i, j, EAST) == 1){
	drawWall(i, j, EAST);
      }
      if(maze_render.value_at(i, j, WEST) == 1){
	drawWall(i, j, WEST);
      }
    }
  }
}
/*Display function - called from main - This function is called as
 * often as possible - Whenever the idle loop finishes*/
void renderWorld(void){

 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();


  /*************ADDED BY ARUN**********************/
  //Call the camera function and pass in the current co-ordinates
  camera(cur_x_position, cur_y_position, cur_angle);
  /***********************************************************************/

  drawFloor(); 
  drawWalls();
  //drawCube(end_x,end_y);
  //glDisable(GL_LIGHTING);
  SDL_GL_SwapBuffers();
}

/*Reshape also called from main - This gets called once at the start of the game
  and then whenever the window gets resized UNUSED AT THE MOMENT UNTIL I GET THIS WORKING IN SDL*/
void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  /*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
  gluPerspective (80, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
  glMatrixMode (GL_MODELVIEW);	
}

/*************ADDED BY ARUN**********************/
Uint32 gameStateTimerFunc(Uint32 interval, void *value) {
  //when there is animation in progress then set needs_render to ture.
  bool needs_render = false;
  double angle;

  //Set the orientation the person is looking based on the direction	
  switch (orientation) {
  case NORTH:
    angle = PI / 2;
    break;
  case WEST:
    angle = 0.0;
    break;
  case SOUTH:
    angle = 3 * PI / 2;
    break;
  case EAST:
    angle = PI;
    break;
  default:
    angle = 0.0;
  }
	
  // if almost at the correct position, jump straight there to avoid rounding errors
  //get the absolute value of current x position to avoid ronding errors when rotating along the x axis
  if (abs(cur_x_position - x_position) < 0.1 || is_first_animation) {
    cur_x_position = x_position;
  }
  //get the absolute value of current y position to avoid ronding errors when rotating along the y axis
  if (abs(cur_y_position - y_position) < 0.1 || is_first_animation) {
    cur_y_position = y_position;
  }
	
  // make sure cur_angle between -2PI and 2PI so the rotation around the circle can be smooth
  if (cur_angle >= 2 * PI) cur_angle -= 2*PI;
  if (cur_angle < 0) cur_angle += 2*PI;
	
  // if almost at the correct angle, jump straight there to avoid rounding errors when rotating
  if (abs(cur_angle - angle) < (PI / 2) / 10 || is_first_animation) {
    cur_angle = angle;
  }
	
  //check if cur_x_postion has increased or decreased, if so then increment or decrement the cur_x_position by 0.1
  //so the transition is smooth along the x axis. Set the needs_render to true so the current frame is rendered
  //when moving
  if(cur_x_position < x_position){
    cur_x_position += 0.1 * interval;
    needs_render = true;
  }else if(cur_x_position > x_position){
    cur_x_position -= 0.1 * interval;
    needs_render = true;
  }
	
  //check if cur_y_postion has increased or decreased, if so then increment or decrement the cur_y_position by 0.1
  //so the transition is smooth along the y axis. Set the needs_render to true so the current frame is rendered
  //when moving
  if(cur_y_position < y_position){
    cur_y_position += 0.1 * interval;
    needs_render = true;
  }else if(cur_y_position > y_position){
    cur_y_position -= 0.1 * interval;
    needs_render = true;
  }
	
  //find the angle difference so it could be used when rotating around the orientation
  double angle_diff = angle - cur_angle;
  if (angle_diff > PI) {
    angle_diff = -(PI * 2 - angle_diff);
  }else if (angle_diff < -PI) {
    angle_diff = 360 + angle_diff;
  }
	
  //if the calculated angle_diff is greater then 0.0 then increment the cur_angle by 0.1 so it seems
  //like rotating anti-clockwise. otherwise rotate clock wise.
  if(angle_diff > 0.0){
    cur_angle += (PI / 2) / 10 * interval;
    needs_render = true;
  }else if(angle_diff < 0.0){
    cur_angle -= (PI / 2) / 10 * interval;
    needs_render = true;
  }
	
  //if needs_render is set to true then call the glut function to redisplay the current frame
  //so the frame seems to be moving.
  if (needs_render) {
    moving = true;
    //renderWorld();
  }else{
    moving = false;
  }

  is_first_animation = false;
	
  return interval;
}
/***********************************************************************/
