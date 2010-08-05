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


   /*
 maze[0][0][NORTH] = 0;
  maze[0][0][EAST] = 0;
  maze[0][0][SOUTH] = 1;
  maze[0][0][WEST] = 1;

  maze[1][0][NORTH] = 0;
  maze[1][0][EAST] = 0;
  maze[1][0][SOUTH] = 1;
  maze[1][0][WEST] = 0;

  maze[2][0][NORTH] = 1;
  maze[2][0][EAST] = 0;
  maze[2][0][SOUTH] = 1;
  maze[2][0][WEST] = 0;

  maze[3][0][NORTH] = 0;
  maze[3][0][EAST] = 1;
  maze[3][0][SOUTH] = 1;
  maze[3][0][WEST] = 0;

  maze[4][0][NORTH] = 0;
  maze[4][0][EAST] = 0;
  maze[4][0][SOUTH] = 1;
  maze[4][0][WEST] = 0;

  maze[5][0][NORTH] = 1;
  maze[5][0][EAST] = 0;
  maze[5][0][SOUTH] = 1;
  maze[5][0][WEST] = 0;

  maze[6][0][NORTH] = 1;
  maze[6][0][EAST] = 0;
  maze[6][0][SOUTH] = 1;
  maze[6][0][WEST] = 0;

  maze[7][0][NORTH] = 0;
  maze[7][0][EAST] = 1;
  maze[7][0][SOUTH] = 1;
  maze[7][0][WEST] = 0;









  maze[0][1][NORTH] = 0;
  maze[0][1][EAST] = 1;
  maze[0][1][SOUTH] = 0;
  maze[0][1][WEST] = 1;

  maze[1][1][NORTH] = 1;
  maze[1][1][EAST] = 1;
  maze[1][1][SOUTH] = 0;
  maze[1][1][WEST] = 1;

  maze[2][1][NORTH] = 1;
  maze[2][1][EAST] = 0;
  maze[2][1][SOUTH] = 1;
  maze[2][1][WEST] = 1;

  maze[3][1][NORTH] = 0;
  maze[3][1][EAST] = 0;
  maze[3][1][SOUTH] = 0;
  maze[3][1][WEST] = 0;

  maze[4][1][NORTH] = 1;
  maze[4][1][EAST] = 0;
  maze[4][1][SOUTH] = 0;
  maze[4][1][WEST] = 0;

  maze[5][1][NORTH] = 1;
  maze[5][1][EAST] = 0;
  maze[5][1][SOUTH] = 1;
  maze[5][1][WEST] = 0;

  maze[6][1][NORTH] = 0;
  maze[6][1][EAST] = 1;
  maze[6][1][SOUTH] = 1;
  maze[6][1][WEST] = 0;

  maze[7][1][NORTH] = 1;
  maze[7][1][EAST] = 1;
  maze[7][1][SOUTH] = 0;
  maze[7][1][WEST] = 1;







  maze[0][2][NORTH] = 1;
  maze[0][2][EAST] = 0;
  maze[0][2][SOUTH] = 0;
  maze[0][2][WEST] = 1;

  maze[1][2][NORTH] = 1;
  maze[1][2][EAST] = 0;
  maze[1][2][SOUTH] = 1;
  maze[1][2][WEST] = 0;

  maze[2][2][NORTH] = 1;
  maze[2][2][EAST] = 1;
  maze[2][2][SOUTH] = 1;
  maze[2][2][WEST] = 0;

  maze[3][2][NORTH] = 0;
  maze[3][2][EAST] =1 ;
  maze[3][2][SOUTH] = 0;
  maze[3][2][WEST] = 1;

  maze[4][2][NORTH] = 0;
  maze[4][2][EAST] = 0;
  maze[4][2][SOUTH] = 1;
  maze[4][2][WEST] = 1;

  maze[5][2][NORTH] = 0;
  maze[5][2][EAST] = 1;
  maze[5][2][SOUTH] = 1;
  maze[5][2][WEST] = 0;

  maze[6][2][NORTH] = 1;
  maze[6][2][EAST] = 1;
  maze[6][2][SOUTH] = 0;
  maze[6][2][WEST] = 1;

  maze[7][2][NORTH] = 0;
  maze[7][2][EAST] = 1;
  maze[7][2][SOUTH] = 1;
  maze[7][2][WEST] = 1;







  maze[0][3][NORTH] = 0;
  maze[0][3][EAST] = 0;
  maze[0][3][SOUTH] = 1;
  maze[0][3][WEST] = 1;

  maze[1][3][NORTH] = 1;
  maze[1][3][EAST] = 1;
  maze[1][3][SOUTH] = 1;
  maze[1][3][WEST] = 0;

  maze[2][3][NORTH] = 0;
  maze[2][3][EAST] = 0;
  maze[2][3][SOUTH] = 1;
  maze[2][3][WEST] = 1;

  maze[3][3][NORTH] = 0;
  maze[3][3][EAST] = 1;
  maze[3][3][SOUTH] = 0;
  maze[3][3][WEST] = 0;

  maze[4][3][NORTH] = 1;
  maze[4][3][EAST] = 1;
  maze[4][3][SOUTH] = 0;
  maze[4][3][WEST] = 1;

  maze[5][3][NORTH] = 0;
  maze[5][3][EAST] = 0;
  maze[5][3][SOUTH] = 0;
  maze[5][3][WEST] = 1;

  maze[6][3][NORTH] = 1;
  maze[6][3][EAST] = 1;
  maze[6][3][SOUTH] = 1;
  maze[6][3][WEST] = 0;

  maze[7][3][NORTH] = 0;
  maze[7][3][EAST] = 0;
  maze[7][3][SOUTH] = 0;
  maze[7][3][WEST] = 1;







  maze[0][4][NORTH] = 0;
  maze[0][4][EAST] = 0;
  maze[0][4][SOUTH] = 0;
  maze[0][4][WEST] = 1;

  maze[1][4][NORTH] = 1;
  maze[1][4][EAST] = 0;
  maze[1][4][SOUTH] = 1;
  maze[1][4][WEST] = 0;

  maze[2][4][NORTH] = 0;
  maze[2][4][EAST] = 0;
  maze[2][4][SOUTH] = 0;
  maze[2][4][WEST] = 0;

  maze[3][4][NORTH] = 1;
  maze[3][4][EAST] = 0;
  maze[3][4][SOUTH] = 0;
  maze[3][4][WEST] = 0;

  maze[4][4][NORTH] = 1;
  maze[4][4][EAST] = 1;
  maze[4][4][SOUTH] = 1;
  maze[4][4][WEST] = 0;

  maze[5][4][NORTH] = 0;
  maze[5][4][EAST] = 0;
  maze[5][4][SOUTH] = 0;
  maze[5][4][WEST] = 1;

  maze[6][4][NORTH] = 1;
  maze[6][4][EAST] = 0;
  maze[6][4][SOUTH] = 1;
  maze[6][4][WEST] = 0;

  maze[7][4][NORTH] = 0;
  maze[7][4][EAST] = 0;
  maze[7][4][SOUTH] = 0;
  maze[7][4][WEST] = 0;







  maze[0][5][NORTH] = 0;
  maze[0][5][EAST] = 1;
  maze[0][5][SOUTH] = 0;
  maze[0][5][WEST] = 1;

  maze[1][5][NORTH] = 0;
  maze[1][5][EAST] = 0;
  maze[1][5][SOUTH] = 1;
  maze[1][5][WEST] = 1;

  maze[2][5][NORTH] = 0;
  maze[2][5][EAST] = 1;
  maze[2][5][SOUTH] = 0;
  maze[2][5][WEST] = 0;

  maze[3][5][NORTH] = 1;
  maze[3][5][EAST] = 0;
  maze[3][5][SOUTH] = 1;
  maze[3][5][WEST] = 1;

  maze[4][5][NORTH] = 1;
  maze[4][5][EAST] = 0;
  maze[4][5][SOUTH] = 1;
  maze[4][5][WEST] = 0;

  maze[5][5][NORTH] = 1;
  maze[5][5][EAST] = 1;
  maze[5][5][SOUTH] = 0;
  maze[5][5][WEST] = 0;

  maze[6][5][NORTH] = 0;
  maze[6][5][EAST] = 1;
  maze[6][5][SOUTH] = 1;
  maze[6][5][WEST] = 1;

  maze[7][5][NORTH] = 1;
  maze[7][5][EAST] = 1;
  maze[7][5][SOUTH] = 0;
  maze[7][5][WEST] = 1;



  maze[0][6][NORTH] = 0;
  maze[0][6][EAST] = 0;
  maze[0][6][SOUTH] = 0;
  maze[0][6][WEST] = 1;

  maze[1][6][NORTH] = 1;
  maze[1][6][EAST] = 1;
  maze[1][6][SOUTH] = 0;
  maze[1][6][WEST] = 0;

  maze[2][6][NORTH] = 1;
  maze[2][6][EAST] = 0;
  maze[2][6][SOUTH] = 0;
  maze[2][6][WEST] = 1;

  maze[3][6][NORTH] = 0;
  maze[3][6][EAST] = 0;
  maze[3][6][SOUTH] = 1;
  maze[3][6][WEST] = 0;


  maze[4][6][NORTH] = 0;
  maze[4][6][EAST] = 0;
  maze[4][6][SOUTH] = 1;
  maze[4][6][WEST] = 0;

  maze[5][6][NORTH] = 0;
  maze[5][6][EAST] = 1;
  maze[5][6][SOUTH] = 1;
  maze[5][6][WEST] = 0;

  maze[6][6][NORTH] = 0;
  maze[6][6][EAST] = 1;
  maze[6][6][SOUTH] = 0;
  maze[6][6][WEST] = 1;



  maze[7][6][NORTH] = 0;
  maze[7][6][EAST] = 1;
  maze[7][6][SOUTH] = 1;
  maze[7][6][WEST] = 1; 





  maze[0][7][NORTH] = 1;
  maze[0][7][EAST] = 0;
  maze[0][7][SOUTH] = 0;
  maze[0][7][WEST] = 1;

  maze[1][7][NORTH] = 1;
  maze[1][1][EAST] = 1;
  maze[1][1][SOUTH] = 1;
  maze[1][1][WEST] = 0;

  maze[2][7][NORTH] = 1;
  maze[2][7][EAST] = 1;
  maze[2][7][SOUTH] = 1;
  maze[2][7][WEST] = 1;

  maze[3][7][NORTH] = 1;
  maze[3][7][EAST] = 1;
  maze[3][7][SOUTH] = 0;
  maze[3][7][WEST] = 1;


  maze[4][7][NORTH] = 1;
  maze[4][7][EAST] = 1;
  maze[4][7][SOUTH] = 0;
  maze[4][7][WEST] = 1;

  maze[5][7][NORTH] = 1;
  maze[5][7][EAST] = 0;
  maze[5][7][SOUTH] = 0;
  maze[5][7][WEST] = 1;

  maze[6][7][NORTH] = 1;
  maze[6][7][EAST] = 0;
  maze[6][7][SOUTH] = 1;
  maze[6][7][WEST] = 0;

  maze[7][7][NORTH] = 1;
  maze[7][7][EAST] = 1;
  maze[7][7][SOUTH] = 0;
  maze[7][7][WEST] = 0; 
*/
   /*
  
   
  maze[0][0][NORTH] = 0;
  maze[0][0][EAST] = 0;
  maze[0][0][SOUTH] = 1;
  maze[0][0][WEST] = 1;

  maze[0][1][NORTH] = 0;
  maze[0][1][EAST] = 0;
  maze[0][1][SOUTH] = 1;
  maze[0][1][WEST] = 0;

  maze[0][2][NORTH] = 1;
  maze[0][2][EAST] = 0;
  maze[0][2][SOUTH] = 1;
  maze[0][2][WEST] = 0;

  maze[0][3][NORTH] = 0;
  maze[0][3][EAST] = 1;
  maze[0][3][SOUTH] = 1;
  maze[0][3][WEST] = 0;

  maze[0][4][NORTH] = 0;
  maze[0][4][EAST] = 0;
  maze[0][4][SOUTH] = 1;
  maze[0][4][WEST] = 0;

  maze[0][5][NORTH] = 1;
  maze[0][5][EAST] = 0;
  maze[0][5][SOUTH] = 1;
  maze[0][5][WEST] = 0;

  maze[0][6][NORTH] = 1;
  maze[0][6][EAST] = 0;
  maze[0][6][SOUTH] = 1;
  maze[0][6][WEST] = 0;

  maze[0][7][NORTH] = 0;
  maze[0][7][EAST] = 1;
  maze[0][7][SOUTH] = 1;
  maze[0][7][WEST] = 0;









  maze[1][0][NORTH] = 0;
  maze[1][0][EAST] = 1;
  maze[1][0][SOUTH] = 0;
  maze[1][0][WEST] = 1;

  maze[1][1][NORTH] = 1;
  maze[1][1][EAST] = 1;
  maze[1][1][SOUTH] = 0;
  maze[1][1][WEST] = 1;

  maze[1][2][NORTH] = 1;
  maze[1][2][EAST] = 0;
  maze[1][2][SOUTH] = 1;
  maze[1][2][WEST] = 1;


  maze[1][3][NORTH] = 0;
  maze[1][3][EAST] = 0;
  maze[1][3][SOUTH] = 0;
  maze[1][3][WEST] = 0;

  maze[1][4][NORTH] = 1;
  maze[1][4][EAST] = 0;
  maze[1][4][SOUTH] = 0;
  maze[1][4][WEST] = 0;

  maze[1][5][NORTH] = 1;
  maze[1][5][EAST] = 0;
  maze[1][5][SOUTH] = 1;
  maze[1][5][WEST] = 0;

  maze[1][6][NORTH] = 0;
  maze[1][6][EAST] = 1;
  maze[1][6][SOUTH] = 1;
  maze[1][6][WEST] = 0;

  maze[1][7][NORTH] = 1;
  maze[1][7][EAST] = 1;
  maze[1][7][SOUTH] = 0;
  maze[1][7][WEST] = 1;







  maze[2][0][NORTH] = 1;
  maze[2][0][EAST] = 0;
  maze[2][0][SOUTH] = 0;
  maze[2][0][WEST] = 1;

  maze[2][1][NORTH] = 1;
  maze[2][1][EAST] = 0;
  maze[2][1][SOUTH] = 1;
  maze[2][1][WEST] = 0;

  maze[2][2][NORTH] = 1;
  maze[2][2][EAST] = 1;
  maze[2][2][SOUTH] = 1;
  maze[2][2][WEST] = 0;

  maze[2][3][NORTH] = 0;
  maze[2][3][EAST] =1 ;
  maze[2][3][SOUTH] = 0;
  maze[2][3][WEST] = 1;

  maze[2][4][NORTH] = 0;
  maze[2][4][EAST] = 0;
  maze[2][4][SOUTH] = 1;
  maze[2][4][WEST] = 1;

  maze[2][5][NORTH] = 0;
  maze[2][5][EAST] = 1;
  maze[2][5][SOUTH] = 1;
  maze[2][5][WEST] = 0;

  maze[2][6][NORTH] = 1;
  maze[2][6][EAST] = 1;
  maze[2][6][SOUTH] = 0;
  maze[2][6][WEST] = 1;

  maze[2][7][NORTH] = 0;
  maze[2][7][EAST] = 1;
  maze[2][7][SOUTH] = 1;
  maze[2][7][WEST] = 1;







  maze[3][0][NORTH] = 0;
  maze[3][0][EAST] = 0;
  maze[3][0][SOUTH] = 1;
  maze[3][0][WEST] = 1;

  maze[3][1][NORTH] = 1;
  maze[3][1][EAST] = 1;
  maze[3][1][SOUTH] = 1;
  maze[3][1][WEST] = 0;

  maze[3][2][NORTH] = 0;
  maze[3][2][EAST] = 0;
  maze[3][2][SOUTH] = 1;
  maze[3][2][WEST] = 1;

  maze[3][3][NORTH] = 0;
  maze[3][3][EAST] = 1;
  maze[3][3][SOUTH] = 0;
  maze[3][3][WEST] = 0;

  maze[3][4][NORTH] = 1;
  maze[3][4][EAST] = 1;
  maze[3][4][SOUTH] = 0;
  maze[3][4][WEST] = 1;

  maze[3][5][NORTH] = 0;
  maze[3][5][EAST] = 0;
  maze[3][5][SOUTH] = 0;
  maze[3][5][WEST] = 1;

  maze[3][6][NORTH] = 1;
  maze[3][6][EAST] = 1;
  maze[3][6][SOUTH] = 1;
  maze[3][6][WEST] = 0;

  maze[3][7][NORTH] = 0;
  maze[3][7][EAST] = 0;
  maze[3][7][SOUTH] = 0;
  maze[3][7][WEST] = 1;







  maze[4][0][NORTH] = 0;
  maze[4][0][EAST] = 0;
  maze[4][0][SOUTH] = 0;
  maze[4][0][WEST] = 1;

  maze[4][1][NORTH] = 1;
  maze[4][1][EAST] = 0;
  maze[4][1][SOUTH] = 1;
  maze[4][1][WEST] = 0;

  maze[4][2][NORTH] = 0;
  maze[4][2][EAST] = 0;
  maze[4][2][SOUTH] = 0;
  maze[4][2][WEST] = 0;

  maze[4][3][NORTH] = 1;
  maze[4][3][EAST] = 0;
  maze[4][3][SOUTH] = 0;
  maze[4][3][WEST] = 0;

  maze[4][4][NORTH] = 1;
  maze[4][4][EAST] = 1;
  maze[4][4][SOUTH] = 1;
  maze[4][4][WEST] = 0;

  maze[4][5][NORTH] = 0;
  maze[4][5][EAST] = 0;
  maze[4][5][SOUTH] = 0;
  maze[4][5][WEST] = 1;

  maze[4][6][NORTH] = 1;
  maze[4][6][EAST] = 0;
  maze[4][6][SOUTH] = 1;
  maze[4][6][WEST] = 0;

  maze[4][7][NORTH] = 0;
  maze[4][7][EAST] = 0;
  maze[4][7][SOUTH] = 0;
  maze[4][7][WEST] = 0;








  maze[5][0][NORTH] = 0;
  maze[5][0][EAST] = 1;
  maze[5][0][SOUTH] = 0;
  maze[5][0][WEST] = 1;

  maze[5][1][NORTH] = 0;
  maze[5][1][EAST] = 0;
  maze[5][1][SOUTH] = 1;
  maze[5][1][WEST] = 1;

  maze[5][2][NORTH] = 0;
  maze[5][2][EAST] = 1;
  maze[5][2][SOUTH] = 0;
  maze[5][2][WEST] = 0;

  maze[5][3][NORTH] = 1;
  maze[5][3][EAST] = 0;
  maze[5][3][SOUTH] = 1;
  maze[5][3][WEST] = 1;

  maze[5][4][NORTH] = 1;
  maze[5][4][EAST] = 0;
  maze[5][4][SOUTH] = 1;
  maze[5][4][WEST] = 0;

  maze[5][5][NORTH] = 1;
  maze[5][5][EAST] = 1;
  maze[5][5][SOUTH] = 0;
  maze[5][5][WEST] = 0;

  maze[5][6][NORTH] = 0;
  maze[5][6][EAST] = 1;
  maze[5][6][SOUTH] = 1;
  maze[5][6][WEST] = 1;

  maze[5][7][NORTH] = 1;
  maze[5][7][EAST] = 1;
  maze[5][7][SOUTH] = 0;
  maze[5][7][WEST] = 1;



  maze[6][0][NORTH] = 0;
  maze[6][0][EAST] = 0;
  maze[6][0][SOUTH] = 0;
  maze[6][0][WEST] = 1;

  maze[6][1][NORTH] = 1;
  maze[6][1][EAST] = 1;
  maze[6][1][SOUTH] = 0;
  maze[6][1][WEST] = 0;

  maze[6][2][NORTH] = 1;
  maze[6][2][EAST] = 0;
  maze[6][2][SOUTH] = 0;
  maze[6][2][WEST] = 1;

  maze[6][3][NORTH] = 0;
  maze[6][3][EAST] = 0;
  maze[6][3][SOUTH] = 1;
  maze[6][3][WEST] = 0;


  maze[6][4][NORTH] = 0;
  maze[6][4][EAST] = 0;
  maze[6][4][SOUTH] = 1;
  maze[6][4][WEST] = 0;

  maze[6][5][NORTH] = 0;
  maze[6][5][EAST] = 1;
  maze[6][5][SOUTH] = 1;
  maze[6][5][WEST] = 0;

  maze[6][6][NORTH] = 0;
  maze[6][6][EAST] = 1;
  maze[6][6][SOUTH] = 0;
  maze[6][6][WEST] = 1;

  maze[6][7][NORTH] = 0;
  maze[6][7][EAST] = 1;
  maze[6][7][SOUTH] = 1;
  maze[6][7][WEST] = 1; 





  maze[7][0][NORTH] = 1;
  maze[7][0][EAST] = 0;
  maze[7][0][SOUTH] = 0;
  maze[7][0][WEST] = 1;

  maze[7][1][NORTH] = 1;
  maze[7][1][EAST] = 1;
  maze[7][1][SOUTH] = 1;
  maze[7][1][WEST] = 0;

  maze[7][2][NORTH] = 1;
  maze[7][2][EAST] = 1;
  maze[7][2][SOUTH] = 1;
  maze[7][2][WEST] = 1;

  maze[7][3][NORTH] = 1;
  maze[7][3][EAST] = 1;
  maze[7][3][SOUTH] = 0;
  maze[7][3][WEST] = 1;


  maze[7][4][NORTH] = 1;
  maze[7][4][EAST] = 1;
  maze[7][4][SOUTH] = 0;
  maze[7][4][WEST] = 1;

  maze[7][5][NORTH] = 1;
  maze[7][5][EAST] = 0;
  maze[7][5][SOUTH] = 0;
  maze[7][5][WEST] = 1;

  maze[7][6][NORTH] = 1;
  maze[7][6][EAST] = 0;
  maze[7][6][SOUTH] = 1;
  maze[7][6][WEST] = 0;

  maze[7][7][NORTH] = 1;
  maze[7][7][EAST] = 1;
  maze[7][7][SOUTH] = 0;
  maze[7][7][WEST] = 0; 
 

   */

   maze[0][0][NORTH] = 0;
   maze[0][1][SOUTH] = 0;
   maze[0][1][EAST] = 0;
   maze[1][1][WEST] = 0;
   maze[1][1][NORTH] = 0;
   maze[1][2][SOUTH] = 0;
   maze[0][2][NORTH] = 0;
   maze[1][2][EAST] = 0;
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
