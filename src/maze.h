#include "defs.h"
#ifndef MAZE_H
#define MAZE_H
class Maze{

public:
 
  int value_at(int i, int j, int k);
  int height();
  int width();
  Maze();//generate random maze
  int maze[N_ROWS][N_COLUMNS][4];

 private:
  int heightv;
  int widthv;

  int current_x;
  int current_y;

};

#endif
