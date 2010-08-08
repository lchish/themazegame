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

//eeh


using namespace std;

Maze maze_render;

/*Textures*/
GLuint wall_texture;
GLuint floor_texture;


void set_maze(Maze target){
  maze_render = target;


  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      printf("[%d][%d]N%dE%dS%dW%d\n",i, j,  maze_render.value_at(i, j, NORTH),maze_render.value_at(i, j, EAST),maze_render.value_at(i, j, SOUTH),maze_render.value_at(i, j, WEST));
    }
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
  ///change
  else if(orientation == WEST){

 gluLookAt(x + 0.5, 0.5 , z + 0.5,x + 1, 0.5, z + 0.5, 0, 1, 0); 
  }
}

/*Draw a single floor tile*/
void drawFloorTile(int i, int j){



 


  if(i == end_x && j == end_y){
    glColor3f(1.0, 0.0, 0.0);
  }



  glBindTexture( GL_TEXTURE_2D, floor_texture );
  glBegin(GL_QUADS);	
  glTexCoord3d(0.0 , 1.0, 0.0); glVertex3f(0.0f + i, 0.0f,1.0f + j);

  glTexCoord3d(1.0 , 1.0, 0.0); glVertex3f(1.0f + i, 0.0f,1.0f + j);

  glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(1.0f + i,0.0f, 0.0f + j);

  glTexCoord3d(0.0, 0.0, 0.0);glVertex3f(0.0f + i,0.0f, 0.0f + j);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);

}


void drawCube(int i, int j){
  glBegin(GL_QUADS); 
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f + i + 0.25, 0.5f, 0.0f + j + 0.25);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.5f + i + 0.25, 0.5f, 0.0f+ j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.5f + i + 0.25, 0.0f, 0.0f+j + 0.25);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f + i + 0.25, 0.0f, 0.0f + j + 0.25);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f + i + 0.25, 0.5f , 0.5f+j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f);  
  glVertex3f(0.5f + i + 0.25, 0.5f , 0.5f+j + 0.25);
  glColor3f(0.0f, 1.0f, 0.0f);  
  glVertex3f(0.5f + i + 0.25, 0.0f , 0.5f+j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(0.0f + i + 0.25, 0.0f , 0.5f+j + 0.25);
  glEnd();
  
  
  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f + i + 0.25, 0.5f , 0.0f + j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f);  
  glVertex3f(0.0f + i + 0.25, 0.5f , 0.5f + j + 0.25);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f + i + 0.25, 0.0f , 0.5f + j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(0.0f+ i + 0.25,  0.0f , 0.0f + j + 0.25);
  glEnd();
  
  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.5f + i + 0.25, 0.5f, 0.0f + j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.5f + i + 0.25, 0.5f , 0.5f + j + 0.25);
  glColor3f(0.0f, 1.0f, 0.0f); 
  glVertex3f(0.5f + i + 0.25, 0.0f , 0.5f + j + 0.25);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.5f + i + 0.25, 0.0f , 0.0f + j + 0.25);
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

  for(i = 0; i < maze_render.width(); i++){
    for(j = 0; j < maze_render.height(); j++){


      /*ERROR ERROR ERROR DONT LET THIS STAY IN HERE */
     
	drawFloorTile(i,j);
      
    }
  }

}



/*Draw all the walls*/
void drawWalls(void){
  int i, j;


  
  for(i = 0; i < maze_render.width(); i++){
    for(j = 0; j < maze_render.height(); j++){



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
