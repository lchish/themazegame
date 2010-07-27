#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_mixer.h>

#include "main_game.h"
#include "game_state.h"
#include "render_world.h"
#include "defs.h"
#include "maze.h"
#include "audio.h"
#include "texture.h"

using namespace std;

/*Our maze*/ //creates new instance
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
int start_y = 0;
int end_x;
int end_y;

/*Textures*/
GLuint wall_texture,floor_texture;

/*Music*/
Mix_Music *world_music;

/*Modifies the players position/orientation based
  on input variables such as moving_fowards_global*/
void move(){
  if(moving_fowards_global){
    if(orientation == NORTH){
      if(maze.value_at(x_position, y_position, NORTH) != 0){
	printf("No");
      }
      else{
	y_position++;
      }
    }
    if(orientation == SOUTH){
      if(maze.value_at(x_position, y_position, SOUTH) != 0){
	printf("No");
      }
      else{
	y_position--;
      }
    }
    if(orientation == EAST){
      if(maze.value_at(x_position, y_position, EAST) != 0){
	printf("No");
      }
      else{
	x_position++;
      }
    }
    if(orientation == WEST){
      if(maze.value_at(x_position, y_position, WEST) != 0){
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
  
  if(orientation == SOUTH){
  printf("%d %d SOUTH\n", x_position, y_position);
  }
if(orientation == NORTH){
  printf("%d %d NORTH\n", x_position, y_position);
  }
if(orientation == EAST){
  printf("%d %d EAST\n", x_position, y_position);
  }
if(orientation == WEST){
  printf("%d %d WEST\n", x_position, y_position);
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

  TODO: Needs to be changed to a timer function later so it dosen't hog 100%cpu */
void idle(void){

  if(turning_left_global == true || turning_right_global == true
     || moving_fowards_global == true){
    move();
  }
  
  if(x_position == end_x && y_position == end_y){

    printf("You win!\n");
    exit(0);
  }
  //glutPostRedisplay(); don't think there is a SDL equivalent of this
  // so taking it out.
}


/*Leslies code*/
static void initTextures(){
  wall_texture = genTexture("data/images/textures/wall.bmp");
  floor_texture = genTexture("data/images/textures/floor.bmp");
}

static void freeTextures(){
  glDeleteTextures( 1, &wall_texture);
  glDeleteTextures(1, &floor_texture);
}

static void initMusic(){
  world_music = loadAudioFile("data/audio/music/test.ogg");
  //might as well start it playing
  //if(music_on)
  playAudio(world_music,-1);//-1 loops forever
}

static void freeMusic(){                                                                                                                                                            
  unloadAudioFile(world_music);                                                                                                                                                      
}
//This code will need to be moved to main_game later.
/*Initialization of the game*/
int gameInit(){
  x_position = start_x;
  y_position = start_y;
  orientation = WEST;
  end_x = 3;
  end_y = 4;

  initTextures();
  initMusic();
  reshape(SCREEN_WIDTH,SCREEN_HEIGHT);
  return 0;
}

int gameDeInit(){
  if(isAudioPlaying())
    stopAllAudio();
  freeTextures();
  freeMusic();
  return 0;
}
