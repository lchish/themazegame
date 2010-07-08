#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "defs.h"
#include "render_world.h"
#include "texture.h"


#include "main_game.h"

using namespace std;


/*Textures*/
GLuint wall_texture;
GLuint floor_texture;

/*Temporary camera function - called before redrawing the graphics*/
 void camera(int x, int z, int orientation){
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

/*Leslies code*/
 void init_textures(){
  wall_texture = genTexture("data/images/textures/wall.bmp");
  floor_texture = genTexture("data/images/textures/floor.bmp");



  /*TO MOVE LATER*/


}

 void free_textures(){
  glDeleteTextures( 1, &wall_texture );
  glDeleteTextures(1, &floor_texture);
}





/*Display function - called from main - This function is called as
 * often as possible - Whenever the idle loop finishes*/
void display(void){

GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  camera(x_position, y_position, orientation);

  drawFloor(); 
  drawWalls();




  SDL_GL_SwapBuffers();
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
