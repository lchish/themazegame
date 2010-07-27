#include <cstdio>
#include <cstdlib>
#include <list>
#include <ctime>

#include "maze.h"
#include "defs.h"

using namespace std;

//mazes are now 3d. Third dimension is walls.
 Maze::Maze(){
   heightv = 10;
   widthv = 10;

   for(int i = 0; i < heightv; i++){
     for(int j = 0; j < widthv; j++){
       maze[i][j][SOUTH] = 1;
       maze[i][j][NORTH] = 1;
       maze[i][j][EAST] = 1;
       maze[i][j][WEST] = 1;
     }
   }
   
   //maze[0][0][SOUTH] = 0;
   //maze[0][0][EAST] = 0;
   //maze[0][0][WEST] = 0;
   //test maze for now
   maze[0][0][NORTH] = 0;
   maze[0][1][SOUTH] = 0;
   maze[0][1][NORTH] = 0;
   maze[0][2][SOUTH] = 0;
   maze[0][2][NORTH] = 0;
   maze[0][3][SOUTH] = 0;
   maze[0][3][EAST] = 0;
   maze[1][3][WEST] = 0;
   maze[1][3][SOUTH] = 0;
   maze[1][2][NORTH] = 0;
   
  //no need for malloc at the moment
}

int Maze::height(){
  return heightv;
}
int Maze::width(){
  return widthv;
}

int Maze::value_at(int i, int j, int k){
  return maze[i][j][k];
}
