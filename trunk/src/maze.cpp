#include <cstdio>
#include <cstdlib>

#include "maze.h"



//default constructor
 Maze::Maze(){

   heightv = 10;
   widthv = 10;


   for(int i = 0; i < heightv; i++){
     for(int j = 0; j < widthv; j++){
       maze[i][j] = 0;
     }
   }

   maze[0][0] = 1;
   maze[0][1] = 1;
   maze[0][2] = 1;
   maze[0][3] = 1;
   maze[0][4] = 1;
   maze[0][5] = 1;
   maze[0][6] = 1;
   maze[0][8] = 1;
   maze[0][9] = 1;
   maze[1][0] = 1;
   maze[1][2] = 1;
   maze[1][6] = 1;
   maze[1][8] = 1;
   maze[2][0] = 1;
   maze[2][1] = 1;
   maze[2][2] = 1;
   maze[2][3] = 1;
   maze[2][4] = 1;
   maze[2][5] = 1;
   maze[2][6] = 1;
   maze[2][7] = 1;
   maze[2][8] = 1;
   maze[2][9] = 1;
   maze[3][0] = 1;
   maze[3][9] = 1;
   maze[4][0] = 1;
   maze[4][3] = 1;
   maze[4][4] = 1;
   maze[4][5] = 1;
   maze[4][6] = 1;
   maze[4][7] = 1;
   maze[4][8] = 1;
   maze[4][9] = 1;
   maze[5][0] = 1;
   maze[5][3] = 1;
   maze[6][0] = 1;
   maze[6][3] = 1;
   maze[6][4] = 1;
   maze[6][5] = 1;
   maze[6][6] = 1;
   maze[6][7] = 1;
   maze[6][8] = 1;
   maze[6][9] = 1;
   maze[7][0] = 1;
   maze[7][1] = 1;
   maze[7][2] = 1;
   maze[7][3] = 1;
   maze[7][7] = 1;
   maze[7][9] = 1;
   maze[8][0] = 1;
   maze[8][5] = 1;
   maze[8][7] = 1;
   maze[8][8] = 1;
   maze[8][9] = 1;
   maze[9][0] = 1;
   maze[9][3] = 1;
   maze[9][4] = 1;
   maze[9][5] = 1;
   maze[9][6] = 1;
   maze[9][7] = 1;

   //no need for malloc at the moment
}

int Maze::height(){
  return heightv;
}
int Maze::width(){
  return widthv;
}

int Maze::value_at(int i, int j){
  return maze[i][j];
}
