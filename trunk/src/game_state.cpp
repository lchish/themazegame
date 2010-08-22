/**
 * Functions used for changing from one game state to another.
 * For example to change from menu state -> main game state call 
 * set game state with the main game states UID.
 */
#include <cstdio>
#include <SDL/SDL.h>

#include "game_state.h"
#include "menu_state.h"
#include "main_game.h"

void set_game_state(int state_number){
  fprintf(stderr,"Entering state %d\n",state_number);
  // call the init method of the state we want and deinit the current one
  if(CURRENT_STATE !=-1){
    switch(CURRENT_STATE){
    case MENU_STATE_NUMBER:
      menuDeInit();
      break;
    case GAME_STATE_NUMBER:
      mainGameDeInit();
      break;
    }
  }
  CURRENT_STATE = state_number;
  switch(state_number){
  case MENU_STATE_NUMBER:
    menuInit();
    break;
  case GAME_STATE_NUMBER:
    mainGameInit();
    break;
  }
}
/* frees all memory used by the current game state*/
void gameStateFreeAll(){
  if(CURRENT_STATE == MENU_STATE_NUMBER){
    menuDeInit();
  }else if(CURRENT_STATE == GAME_STATE_NUMBER){
    mainGameDeInit();
  }
}
/* This runs the update loop for the current state */
void gameStateUpdate(){
  if(CURRENT_STATE==MENU_STATE_NUMBER){
    menuUpdate();
  }else if(CURRENT_STATE==GAME_STATE_NUMBER){
    mainGameUpdate();
  }
}
/* what happens when the keyboard button is released */
void gameStateKeyboardUp(SDLKey key){
  if(CURRENT_STATE==MENU_STATE_NUMBER){
    menuKeyUp(key);
  }else if(CURRENT_STATE==GAME_STATE_NUMBER){
    mainGameKeyboardUp(key);
  }
}
/* what happens when the keyboard button is down */
void gameStateKeyboardDown(SDLKey key){
  if(CURRENT_STATE==MENU_STATE_NUMBER){
    menuKeyDown(key);
  }else if(CURRENT_STATE==GAME_STATE_NUMBER){
    mainGameKeyboardDown(key);
  }
}
/* render loop*/
void gameStateRender(){
  if(CURRENT_STATE==MENU_STATE_NUMBER){
    menuRender();
  }else if(CURRENT_STATE==GAME_STATE_NUMBER){
    mainGameRender();
  }
}
