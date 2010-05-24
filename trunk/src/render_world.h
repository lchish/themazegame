#ifndef RENDER_WORLD_HPP
#define RENDER_WORLD_HPP



extern void display();
extern void setTempMaze(void);
extern void reshape(int, int);
extern void idle();
extern void myTimer(int);

void processNormalKeys(unsigned char key, int x, int y);
void keyboardup(unsigned char key, int x, int y);
int gameInit();
int gameDeInit();
void gameStateTimerFunc(int value);
#endif