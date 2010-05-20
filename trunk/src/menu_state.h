#ifndef MENU_STATE_H
#define MENU_STATE_H

int menuInit();
int menuDeInit();
void menuUpdate();
void menuRender();
void menuKeyPressed(unsigned char key,int x,int y);
void menuProcessNormalKeys(int key,int x,int y);
#endif
