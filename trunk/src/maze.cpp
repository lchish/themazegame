#include <cstdio>
#include <cstdlib>
#include <list>
#include <ctime>

#include "maze.h"


#include "defs.h"

#include "genmaze.h"


#include <time.h>


#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <cstring>
//#include <string.h>


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


//  int maze[5][5][4];

//mazes are now 3d. Third dimension is walls.
 Maze::Maze(){
   heightv = 3;
   widthv = 3;

   for(int i = 0;i < 3; i++){
     for(int j = 0; j < 3; j++){

       maze[i][j][NORTH] = 1;
       maze[i][j][EAST] = 1;
       maze[i][j][SOUTH] = 1;
       maze[i][j][WEST] = 1;
     }

   }
  
   //     generator(0, NULL);


   /*
  for(int i = 0; i < 3; i++){
     for(int j=  0; j < 3; j++){

       //       printf("%d %d NORTH:%d\n", i, j, maze_def[i][j][NORTH]);
       //      printf("%d %d  EAST:%d\n", i, j, maze_def[i][j][EAST]);
       //       printf("%d %d SOUTH:%d\n",i, j, maze_def[i][j][SOUTH]);
       //       printf("%d %d  WEST:%d\n",i,j, maze_def[i][j][WEST]);

      maze[i][j][NORTH] = maze_def[i][j][NORTH];
      maze[i][j][SOUTH] = maze_def[i][j][SOUTH];
      maze[i][j][EAST] = maze_def[i][j][EAST];
      maze[i][j][WEST] = maze_def[i][j][WEST];
     }
  }   

   */


   
  
   
  maze[0][0][NORTH] = 0;
  maze[0][0][EAST] = 0;
  maze[0][1][SOUTH] = 0;
  maze[0][1][EAST] = 0;
  maze[0][1][NORTH] = 0;
  maze[0][2][SOUTH] = 0;
  maze[0][2][EAST] = 0;
  maze[1][0][WEST] = 0;
  maze[1][0][EAST] = 0;
  maze[1][1][WEST] = 0;
  maze[1][2][WEST] = 0;
  maze[1][2][EAST] = 0;
  maze[2][0][WEST] = 0;
  maze[2][0][NORTH] = 0;
  maze[2][1][SOUTH] = 0;
  maze[2][2][WEST] = 0;
 


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
