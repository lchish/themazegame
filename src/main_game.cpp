/***********************************************
 ***********************************************

WARNING
WARNING
WARNING

GOT WEIRD PROBLEM HAPPENING WHERE IF TURNING_LEFT_GLOBAL, RIGHT_GLOBAL.. AND MOVING_FOWARDS...
if they are initially set to 0, they get set to 1. So setting to -1 for now.*/


/*WARNING WARNING

WARNING

WARNING*/
/************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_mixer.h>
#include <ctime>


#include <sstream>
#include <iostream>


#include "main_game.h"
#include "game_state.h"
#include "render_world.h"
#include "defs.h"
#include "audio.h"
#include "texture.h"
#include "maze.h"

using namespace std;

/*Our maze*/ //creates new instance
//Maze maze;

Maze maze;

/* For move function */
 int turning_left_global = 0;
int turning_right_global = 0;
 int moving_fowards_global = 0;

/*Our player data structure - Where we are in the world */
int x_position = 0;
int y_position = 0;
int orientation;

/*Where we start*/
int start_x = 0;
int start_y = 0;

int end_x = 7;
int end_y = 1;

/*Music*/
Mix_Music *world_music;
bool music_on = true;

/*Modifies the players position/orientation based
  on input variables such as moving_fowards_global*/
static void move(){

  printf("Moving fowards: %d \n", moving_fowards_global);


  if(moving_fowards_global == 1){
    if(orientation == NORTH){
      if(maze.value_at(x_position, y_position, NORTH) != 0){
	printf("No");
      }
      else{
	if(y_position < 8){
	  y_position++;
	}
      
      }
    }
    if(orientation == SOUTH){
      if(maze.value_at(x_position, y_position, SOUTH) != 0){
	printf("No");
      }
      else{
	if(y_position > 0){
	  y_position--;
	}
      }
    }

    if(orientation == EAST){
      if(maze.value_at(x_position, y_position, WEST) != 0){
	printf("No");
      }
      else{
	if(x_position > 0){
	  x_position--;
	}
      }
    }
      
    if(orientation == WEST){
      if(maze.value_at(x_position, y_position, EAST) != 0){
	printf("No");
      }
      else{
	if(x_position < 8){
	  x_position++;
	}
      }
    }
  }


  else if(turning_right_global == 1){
    if(orientation == WEST){
      orientation = NORTH;
    }
    else{
      orientation++;
    }
  }
  else if(turning_left_global == 1){
    if(orientation == NORTH){
      orientation = WEST ;
    }
    else{
      orientation--;
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
void mainGameKeyboardUp(SDLKey key)
{

  if (key == SDLK_LEFT){
    turning_left_global = 0;
  }
  else if(key == SDLK_RIGHT){
    turning_right_global = 0;
  }

  else if(key == SDLK_UP){
    moving_fowards_global = 0;
  }
  else if(key == SDLK_m){
    music_on = !music_on;
  }
}

/*Called when a key is held down*/
void mainGameKeyboardDown(SDLKey key){
  printf("KEY\n");

  if(key == SDLK_LEFT){


    turning_left_global = 1;
  }

  else if(key == SDLK_UP){
    moving_fowards_global = 1;
  }

  else if(key == SDLK_RIGHT){
    turning_right_global = 1;
  }
}

/*Our main game function.. checks for input, moves and redraws the screen.

  TODO: Needs to be changed to a timer function later so it dosen't hog 100%cpu */
void mainGameUpdate(void){

  if(turning_left_global == 1 || turning_right_global == 1
     || moving_fowards_global == 1){
    printf("Moving\n");
    move();
  }
  
  if(x_position == end_x && y_position == end_y){

    printf("You win!\n");
    exit(0);
  }
  //glutPostRedisplay(); don't think there is a SDL equivalent of this
  // so taking it out.
  //check if music should be playing
  if(!music_on && isAudioPlaying()){
    pauseAudio();
  }else if(music_on && !isAudioPlaying()){
    resumeAudio();
  }

 
}

/*Display function - called from main - This function is called as
 * often as possible - Whenever the idle loop finishes*/
void mainGameRender(void){
  renderWorld();
}

/*Leslies code*/
static void initTextures(){


  srand(time(NULL));


  int floor_tex_num = 0;
  int wall_tex_num = 0;

  floor_tex_num = rand() % 8; //SINCE THERE ARE 8 FLOOR TEXTURES ATM.
  wall_tex_num = rand() % 3; // 3 wall textures atm.

  string w_string = "data/images/textures/w";

  ostringstream oss_wall;
  oss_wall <<wall_tex_num;

  string w_num = oss_wall.str();

  w_string += w_num;
  w_string += ".bmp";




  string f_string = "data/images/textures/f";


  ostringstream oss_floor;
  oss_floor << floor_tex_num;

  string f_num = oss_floor.str();
  
  f_string += f_num;



  f_string += ".bmp";

  char *c_w_string = (char*)w_string.c_str();
  char *c_f_string = (char*)f_string.c_str();

  cout << c_w_string << endl;
  cout << c_f_string << endl;
 

  wall_texture = genTexture(c_w_string);
  floor_texture = genTexture(c_f_string);
  finish_texture = genTexture("data/images/textures/finish.bmp");

}

static void freeTextures(){
  glDeleteTextures( 1, &wall_texture);
  glDeleteTextures(1, &floor_texture);
}

static void initMusic(){
  world_music = loadAudioFile("data/audio/music/gamemusic.ogg");
  //might as well start it playing
  if(music_on) 
    playAudio(world_music,-1);//-1 loops forever
}

static void freeMusic(){
  unloadAudioFile(world_music);
}

//This code will need to be moved to main_game later.
/*Initialization of the game*/
int mainGameInit(){



   

  x_position = start_x;
  y_position = start_y;
  orientation = WEST;




  initTextures();
  initMusic();

  set_maze(maze);



  reshape(SCREEN_WIDTH,SCREEN_HEIGHT);
  return 0;
}

int mainGameDeInit(){
  if(isAudioPlaying())
    stopAllAudio();
  freeTextures();
  freeMusic();
  return 0;
}



