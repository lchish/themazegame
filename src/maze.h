class Maze{

public:
 
  int value_at(int i, int j, int k);
  int height();
  int width();
  Maze();//generate random maze
  //Maze(FILE file);//generate maze from file

private:
  int maze[10][10][4];
  int heightv;
  int widthv;

  int current_x;
  int current_y;

};
