/**
 * Does everything for the main game state except render the world.
 * Basically creates a new maze, initialises textures and music and allows
 * the player to move through the world. 
 */
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

/*Our maze*/
Maze  maze;

/* For move function */
int turning_left_global = 0;
int turning_right_global = 0;
int moving_fowards_global = 0;

/*Our player data structure - Where we are in the world */
int x_position = 0;
int y_position = 0;
int orientation;


/*Where we start.  These constants are all from defs.h */
int start_x = START_X;
int start_y = START_Y;

int end_x = END_X;
int end_y = END_Y;

/*Music*/
Mix_Music *world_music;
bool music_on = true;

/*Modifies the players position/orientation based
  on input variables such as moving_fowards_global*/
static void move(){
  if(moving_fowards_global == 1){
    if(orientation == NORTH){
      if(maze.value_at(x_position, y_position, NORTH) != 0){
      }
      else{
	y_position++;
      }
    }
    if(orientation == SOUTH){
      if(maze.value_at(x_position, y_position, SOUTH) != 0){
      }
      else{
	  y_position--;
      }
    }
    if(orientation == EAST){
      if(maze.value_at(x_position, y_position, WEST) != 0){
      }
      else{
	x_position--;
      }
    }
    if(orientation == WEST){
      if(maze.value_at(x_position, y_position, EAST) != 0){
      }
      else{
	  x_position++;
      }
    }
  }else if(turning_right_global == 1){
    if(orientation == WEST){
      orientation = NORTH;
    }else{
      orientation++;
    }
  }else if(turning_left_global == 1){
    if(orientation == NORTH){
      orientation = WEST ;
    }else{
      orientation--;
    } 
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
void mainGameKeyboardDown(SDLKey key)
{
  if(key == SDLK_LEFT){
    turning_left_global = 1;
  }else if(key == SDLK_UP){
    moving_fowards_global = 1;
  }else if(key == SDLK_RIGHT){
    turning_right_global = 1;
  }
}

/*Our main game function.. checks for input, moves and redraws the screen.

  TODO: Needs to be changed to a timer function later so it dosen't hog 100%cpu */
void mainGameUpdate(void)
{
  if(turning_left_global == 1 || turning_right_global == 1
     || moving_fowards_global == 1){
    move();
  }
  if(x_position == end_x && y_position == end_y){
    printf("You win!\n");
    exit(0);
  }
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

static void initTextures(){
  srand(time(NULL));
  int floor_tex_num = 0;
  int wall_tex_num = 0;

  /*get a random texture number. Texture files are called w0.bmp, f0.bmp
   * f1.bmp and so on*/
  floor_tex_num = rand() % FLOOR_TEX_COUNT; 
  wall_tex_num = rand() % WALL_TEX_COUNT;

  string w_string = "data/images/textures/w"; /*where our wall textures are 
					       *located + the first character*/

  ostringstream oss_wall; //used to add integer to string
  oss_wall <<wall_tex_num;
  string w_num = oss_wall.str();
  w_string += w_num;
  w_string += ".tga";

  //same thing for floors.
  string f_string = "data/images/textures/f";
  ostringstream oss_floor;
  oss_floor << floor_tex_num;
  string f_num = oss_floor.str();
  f_string += f_num;
  f_string += ".tga";

  /*Turn them back into char arrays, since SDL needs these instead of strings */
  char *c_w_string = (char*)w_string.c_str();
  char *c_f_string = (char*)f_string.c_str();
  
  /*Now that we have the filenames, Generate the textures*/
  wall_texture = genTexture(c_w_string);
  floor_texture = genTexture(c_f_string);
  finish_texture = genTexture("data/images/textures/finish.tga");
}

static void freeTextures(){
  glDeleteTextures( 1, &wall_texture);
  glDeleteTextures(1, &floor_texture);
  glDeleteTextures(1,&finish_texture);
}

static void initMusic(){
  const char *music_files[3];
  music_files[0] = "data/audio/music/gamemusic.ogg";
  music_files[1] = "data/audio/music/gameMusic2.ogg";
  music_files[2] = "data/audio/music/gameMusic3.ogg";
  srand(time(NULL));
  world_music = loadAudioFile(music_files[rand() %3]);
  //might as well start it playing
  if(music_on) 
    playAudio(world_music,-1);//-1 loops forever
}

static void freeMusic(){
  unloadAudioFile(world_music);
}

/*Initialization of the game*/
int mainGameInit(){
  x_position = start_x;
  y_position = start_y;
  orientation = WEST;
  initTextures();
  initMusic();

  //sets this in the render file.
  set_maze(maze);
  reshape(SCREEN_WIDTH,SCREEN_HEIGHT);
  return 0;
}

//Free
int mainGameDeInit(){
  if(isAudioPlaying())
    stopAllAudio();
  freeTextures();
  freeMusic();
  return 0;
}



