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

#include "maze.h"

/*Our maze*/
Maze maze;


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


/*Modifies the players position/orientation based
  on input variables such as moving_fowards_global*/
void move(){
  if(moving_fowards_global){
    if(orientation == NORTH){
      if(maze.value_at(x_position, y_position+1) != 1){
	printf("No");
      }
      else{
	y_position++;
      }
    }
    if(orientation == SOUTH){
      if(maze.value_at(x_position, y_position-1) != 1){
	printf("No");
      }
      else{
	y_position--;
      }
    }
    if(orientation == EAST){
      if(maze.value_at(x_position+1, y_position) != 1){
	printf("No");
      }
      else{
	x_position++;
      }
    }
    if(orientation == WEST){
	if(maze.value_at(x_position-1, y_position) != 1){
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


  reshape(800, 600);

  //reshape(wid, hei);

  return 0;
}

int gameDeInit(){
  free_textures();
  return 0;
}
