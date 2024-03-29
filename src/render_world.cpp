/**
 * This code follows on from main_game.cpp and draws the walls and 
 * floor of the game and sets the camera position based on the player position.
 */
#include <cstdio>
#include <cstdlib>
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

Maze maze_render;

/*Textures*/
GLuint wall_texture;
GLuint floor_texture;

//for finish tile. Floor only.
GLuint finish_texture;

void set_maze(Maze target){
  maze_render = target;
}

/*Temporary camera function - called before redrawing the graphics*/
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
  else if(orientation == WEST){
    gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 1, 0.5, z + 0.5, 0, 1, 0); 
  }
}

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
  camera(x_position, y_position, orientation);
  drawFloor(); 
  drawWalls();
  SDL_GL_SwapBuffers();
}
/* Sets the size of the world */
void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  /*SETTING THIS TO HIGH CAUSES OBJECTS REALLY CLOSE TO NOT BE DRAWN*/
  gluPerspective (80, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
  glMatrixMode (GL_MODELVIEW);  
}
