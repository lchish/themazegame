#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "main_game.h"
#include "game_state.h"

#include "render_world.h"

#include "defs.h"


/*The maze floor is on the X-Z axis, and the walls get drawn on the Y axis*/
int maze[10][10];
int maze_size = 07;

/* For move function */
int turning_left_global;
int turning_right_global;
int moving_fowards_global;


/*Our player data structure - Where we are in the world */
int x_position;
int y_position;
int orientation;

/*Where we start*/
int start_x = 0;
int start_y = 1;



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
void inGameKeyboardUp(SDLKey key)
{

  if (key == SDLK_LEFT){
    turning_left_global = false;
  }
  else if(key == SDLK_RIGHT){
    turning_right_global = false;
  }

  else if(key == SDLK_UP){
    moving_fowards_global = false;
  }

}


/*Called when a key is held down*/
void inGameKeyboardDown(SDLKey key){
  if(key == SDLK_LEFT){
    turning_left_global = true;
  }

  else if(key == SDLK_UP){
    moving_fowards_global = true;
  }

  else if(key == SDLK_RIGHT){
    turning_right_global = true;
  }
}




/*Our main game function.. checks for input, moves and redraws the screen.

  Needs to be changed to a timer function later so it dosen't hog 100%cpu, and
  also needs to be moved to main_game*/

void idle(void){

  if(turning_left_global == true || turning_right_global == true
     || moving_fowards_global == true){
    move();
  }
  //glutPostRedisplay(); don't think there is a SDL equivalent of this
  // so taking it out.
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
