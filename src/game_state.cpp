#include <cstdio>

#include "game_state.h"

#include "menu_state.h"
#include "main_game.h"



void set_game_state(int state_number){
	printf("Entering state %d\n",state_number);
	// call the init method of the state we want
	if(CURRENT_STATE !=-1){
		switch(CURRENT_STATE){
			case MENU_STATE_NUMBER:
				menuDeInit();
				break;
			case GAME_STATE_NUMBER:
				gameDeInit();
				break;
		}
	}
	CURRENT_STATE = state_number;
	switch(state_number){
			case MENU_STATE_NUMBER:
				menuInit();
				break;
			case GAME_STATE_NUMBER:
				gameInit();
				break;
	}
}
/* This runs the update loop for the current state */
void gameStateUpdate(){
	if(CURRENT_STATE==MENU_STATE_NUMBER){
		menuUpdate();
	}else if(CURRENT_STATE==GAME_STATE_NUMBER){
		idle();
	}
}
void gameStateReshape(int w,int h){
	if(CURRENT_STATE==MENU_STATE_NUMBER){
		//todo add a reshape for the menu?
	}else if(CURRENT_STATE==GAME_STATE_NUMBER){
	  	reshape(w,h);
	}
}
void gameStateKeyboardUp(SDLKey key){
	if(CURRENT_STATE==MENU_STATE_NUMBER){
		menuKeyUp(key);
	}else if(CURRENT_STATE==GAME_STATE_NUMBER){
	  inGameKeyboardUp(key);
	}
}
void gameStateKeyboardDown(SDLKey key){
	if(CURRENT_STATE==MENU_STATE_NUMBER){
	  menuKeyDown(key);
	}else if(CURRENT_STATE==GAME_STATE_NUMBER){
	  inGameKeyboardDown(key);
	}
}
void gameStateRender(){
	if(CURRENT_STATE==MENU_STATE_NUMBER){
		menuRender();
	}else if(CURRENT_STATE==GAME_STATE_NUMBER){
		display();
	}
}
