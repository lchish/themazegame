#include <cstdio>
#include <cstdlib>
#include <list>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>



#include "maze.h"
#include "defs.h"




using std::string;
using std::vector;

//#include <string.h>


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define N_ROWS    (8)
#define N_COLUMNS (8)

/*****************************************************************
 * Local Types
 *****************************************************************/

int temp_maze[N_ROWS][N_COLUMNS][4];








typedef std::set<int>        Group;
typedef std::map<int, Group> GroupIdToGroup;

class Room
{
   public:
      Room(int id, int row, int column);

      void  visit(int depth, Group &visited, Room *caller);
      void  deadEndFound(int depth, Room *room);
      Room  *getMaxRoom();

      bool hasNorth();
      bool hasSouth();
      bool hasEast();
      bool hasWest();

      void setNorth(Room *north);
      void setSouth(Room *south);
      void setEast (Room *east);
      void setWest (Room *west);

      void setGroupID(int id);
      int  getGroupID();

   public:
      const int mID;
      const int mRow;
      const int mColumn;

   private:
      int mGroupID;

      Room *mNorth;
      Room *mSouth;
      Room *mEast;
      Room *mWest;

      Room *mMaxRoom;
      int   mMaxDepth;
};

typedef vector<Room *>  RoomRow;
typedef vector<RoomRow> Rooms;

class Wall
{
   public:
      Wall(Room *first, Room *second);
      Room *getFirst();
      Room *getSecond();

   private:
      Room *mFirst;
      Room *mSecond;
      bool  mPresent;
};

typedef vector<Wall *> Walls;

template <typename T>
class Cleaner
{
   public:
      Cleaner();
      ~Cleaner();
      void add(T *ptr);

   private:
      Cleaner(const Cleaner &);
      Cleaner &operator=(const Cleaner &);

   private:
      vector<T *> mList;
};

template <typename T>
Cleaner<T>::Cleaner()
{
}

template <typename T>
Cleaner<T>::~Cleaner()
{
   for(int n = mList.size(), i = 0; i < n; i ++)
   {
      delete mList[i];
      mList[i] = NULL;
   }

   mList.clear();
}

template <typename T>
void Cleaner<T>::add(T *ptr)
{
   mList.push_back(ptr);
}

/*****************************************************************
 * Local Function Prototypes
 *****************************************************************/

static void seedRandom();

static void init(
   int           rows,
   int           columns,
   Rooms         &rooms,
   Walls         &walls,
   Cleaner<Room> &roomCleaner,
   Cleaner<Wall> &wallCleaner
);

/*****************************************************************
 * Local Type Definitions
 *****************************************************************/

// --------------
// Room
// --------------

Room::Room(int id, int row, int column) :
   mID(id), mRow(row), mColumn(column), mGroupID(0), 
   mNorth(0), mSouth(0), mEast(0), mWest(0), mMaxRoom(0), mMaxDepth(0)
{
}

void Room::visit(int depth, Group &visited, Room *caller)
{
   bool isDeadEnd = true;

   visited.insert(mID);

   if(mNorth && visited.find(mNorth->mID) == visited.end())
   {
      isDeadEnd = false;
      mNorth->visit(depth + 1, visited, caller);
   }

   if(mSouth && visited.find(mSouth->mID) == visited.end())
   {
      isDeadEnd = false;
      mSouth->visit(depth + 1, visited, caller);
   }

   if(mWest && visited.find(mWest->mID) == visited.end())
   {
      isDeadEnd = false;
      mWest->visit(depth + 1, visited, caller);
   }

   if(mEast && visited.find(mEast->mID) == visited.end())
   {
      isDeadEnd = false;
      mEast->visit(depth + 1, visited, caller);
   }

   if(isDeadEnd)
   {
      caller->deadEndFound(depth, this);
   }
}

void Room::deadEndFound(int depth, Room *room)
{
   if(depth > mMaxDepth)
   {
      mMaxDepth = depth;
      mMaxRoom  = room;
   }
}

Room *Room::getMaxRoom()
{
   return(mMaxRoom);
}

bool Room::hasNorth() { return(mNorth != NULL); }
bool Room::hasSouth() { return(mSouth != NULL); }
bool Room::hasEast()  { return(mEast  != NULL); }
bool Room::hasWest()  { return(mWest  != NULL); }

void Room::setNorth(Room *ptr) { mNorth = ptr; }
void Room::setSouth(Room *ptr) { mSouth = ptr; }
void Room::setEast (Room *ptr) { mEast  = ptr; }
void Room::setWest (Room *ptr) { mWest  = ptr; }

void Room::setGroupID(int id) { mGroupID = id;    }
int  Room::getGroupID()       { return(mGroupID); }

// --------------
// Wall
// --------------

Wall::Wall(Room *first, Room *second) :
   mFirst(first), mSecond(second), mPresent(true)
{
}

Room *Wall::getFirst()  { return(mFirst);  }
Room *Wall::getSecond() { return(mSecond); }

/*****************************************************************
 * Local Functions
 *****************************************************************/

static void seedRandom()
{
   srand(time(NULL));
}




static void init(
   int           rows,
   int           columns,
   Rooms         &rooms,
   Walls         &walls,
   Cleaner<Room> &roomCleaner,
   Cleaner<Wall> &wallCleaner
)
{
   int i  = 0;
   int j  = 0;
   int id = 0;

   for(i = 0; i < rows; i ++)
   {
      RoomRow row;

      for(int j = 0; j < columns; j ++, id ++)
      {
         Room *roomPtr = new Room(id, i, j);

         row.push_back(roomPtr);
         roomCleaner.add(roomPtr);
      }

      rooms.push_back(row);
   }

   for(i = 0; i < rows; i ++)
   {
      for(j = 1; j < columns; j ++)
      {
         Room *first   = rooms[i][j - 1];
         Room *second  = rooms[i][j];
         Wall *wallPtr = new Wall(first, second);

         walls.push_back(wallPtr);
         wallCleaner.add(wallPtr);
      }
   }

   for(i = 1; i < rows; i ++)
   {
      for(j = 0; j < columns; j ++)
      {
         Room *first   = rooms[i - 1][j];
         Room *second  = rooms[i][j];
         Wall *wallPtr = new Wall(first, second);

         walls.push_back(wallPtr);
         wallCleaner.add(wallPtr);
      }
   }
}



void gen_maze()
{
   int rows              = N_ROWS;
   int columns           = N_COLUMNS;
 

   string errMsg         = "";


   Rooms rooms;
   Walls walls;

   Cleaner<Room> roomCleaner;
   Cleaner<Wall> wallCleaner;

   init(rows, columns, rooms, walls, roomCleaner, wallCleaner);

   int nWalls = walls.size();

   // ------------------------------------------------
   // Shuffle the walls
   // ------------------------------------------------

   seedRandom();

   int i = 0;
   int j = 0;

   for(i = 0; i < nWalls; i ++)
   {
      int idx1 = 0;
      int idx2 = 0;

      do {

         int value1 = rand();
         int value2 = rand();

         if(value1 < 0) value1 = -value1;
         if(value2 < 0) value2 = -value2;

         idx1 = value1 % nWalls;
         idx2 = value2 % nWalls;

      }  while(idx1 == idx2);

      Wall *ptr   = walls[idx1];
      walls[idx1] = walls[idx2];
      walls[idx2] = ptr;
   }

   // ---------------------------------------------
   // Put each room initially into its own group
   // ---------------------------------------------

   GroupIdToGroup gMap;

   for(i = 0; i < rows; i ++)
   {
      for(j = 0; j < columns; j ++)
      {
         Room *r = rooms[i][j];

         Group theGroup;

         theGroup.insert(r->mID);

         gMap[r->mID] = theGroup;
         r->setGroupID(r->mID);
      }
   }

   // ------------------------------------------------
   // Now start knocking down walls ...
   // ------------------------------------------------

   for(i = 0; i < nWalls; i ++)
   {
  

      Room *first  = walls[i]->getFirst();
      Room *second = walls[i]->getSecond();

      // Are these two rooms already reachable
      // from one another?

      if(first->getGroupID() != second->getGroupID())
      {
         // Not yet reachable so correct that ...

         if(first->mColumn == second->mColumn)
         {
            first->setNorth(second);
            second->setSouth(first);
         }
         else
         {
            first->setEast(second);
            second->setWest(first);
         }

         // Now, we need to put everyone from second's group
         // into first's group

         int sid        = second->getGroupID();
         Group theGroup = gMap[sid];

         Group::iterator gi;

         for(gi = theGroup.begin(); gi != theGroup.end(); gi ++)
         {
            int roomID    = *gi;
            int theRow    = roomID / columns;
            int theColumn = roomID % columns;

            Room *ptr = rooms[theRow][theColumn];
            int gid   = first->getGroupID();

            gMap[gid].insert(roomID);
            ptr->setGroupID(gid);
         }

         gMap.erase(sid);
      }
   }

 
   for(int i = 0; i < 8; i++){
     for(int j = 0; j < 8; j++){
       if(rooms[j][i]->hasNorth()){
	 temp_maze[i][j][NORTH] = 0;
       }
       if(rooms[j][i]->hasSouth()){
	 temp_maze[i][j][SOUTH] = 0;
       }
       if(rooms[j][i]->hasEast()){
	 temp_maze[i][j][EAST] = 0;
       }
       if(rooms[j][i]->hasWest()){
	 temp_maze[i][j][WEST] = 0;
       }




     }
}
}

//  int maze[5][5][4];

//mazes are now 3d. Third dimension is walls.
 Maze::Maze(){

   heightv = 8;
   widthv = 8;


for(int i = 0; i < N_ROWS; i++){
  for(int j = 0; j < N_COLUMNS; j++){

    temp_maze[i][j][NORTH] = 1;
    temp_maze[i][j][SOUTH] = 1;
    temp_maze[i][j][EAST] = 1;
    temp_maze[i][j][WEST] = 1;

  }
 }






   for(int i = 0;i < 8; i++){
     for(int j = 0; j < 8; j++){
       maze[i][j][NORTH] = 1;
       maze[i][j][EAST] = 1;
       maze[i][j][SOUTH] = 1;
       maze[i][j][WEST] = 1;
     }

   }
 

   gen_maze();

   for(int i = 0; i < N_ROWS; i++){
     for(int j = 0; j < N_COLUMNS; j++){
       maze[i][j][NORTH] = temp_maze[i][j][NORTH];
   maze[i][j][SOUTH] = temp_maze[i][j][SOUTH];
   maze[i][j][EAST] = temp_maze[i][j][EAST];
   maze[i][j][WEST] = temp_maze[i][j][WEST];


     }
   }


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
