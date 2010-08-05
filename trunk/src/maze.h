#ifndef MAZE_H
#define MAZE_H
class Maze{

public:
 
  int value_at(int i, int j, int k);
  int height();
  int width();
  Maze();//generate random maze
  //Maze(FILE file);//generate maze from file
  int maze[8][8][4];

 private:
  int heightv;
  int widthv;

  int current_x;
  int current_y;

};

#endif
