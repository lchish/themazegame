/** 
 * Generates the maze. Not particularly sure what this does as it was not
 * written by us but it works. Used under permission from author.
 */


// -----------------------------------------------------------------
// Our algorithm for creating random mazes works as follows:
//
//    - Suppose we have 5 rows and 8 columns ...
// 
//       +---+---+---+---+---+---+---+---+
//       |   |   |   |   |   |   |   |   |
//       +---+---+---+---+---+---+---+---+
//       |   |   |   |   |   |   |   |   |
//       +---+---+---+---+---+---+---+---+
//       |   |   |   |   |   |   |   |   |
//       +---+---+---+---+---+---+---+---+
//       |   |   |   |   |   |   |   |   |
//       +---+---+---+---+---+---+---+---+
//       |   |   |   |   |   |   |   |   |
//       +---+---+---+---+---+---+---+---+
//
//     The perimeter of the maze will always remain in place
//     but we'll construct the maze by knocking down a number
//     of the interior walls.
//
//    - So, in this example, for each row, we have 7 (8 - 1)
//      interior walls => 5 rows * 7 per row => 35 vertical interior walls
//
//      We also have 8 horizontal interior walls for each row
//      (except the last one) => 4 (5 - 1) rows * 8 per row => 32
//      horizontal interior walls
//
//      For 'R' rows and 'C' columns we'll have:
//         (R - 1) * C + (C - 1) * R -> total interior walls
//
//    - We then put all our walls into an array and randomize
//      them.  Afterwards, we start at the beginning of the array
//      and work our way through all the interior walls knocking
//      down any walls that would connect rooms not already
//      connected (reachable from each other currently)
//
//    - The way we determine if two rooms are connected is as follows:
//
//      - A group is a list of rooms
//
//      - We start with as many groups as there are rooms and
//        each group containing only one room.  This reflects
//        the initial state of the maze with no rooms being
//        connected to any other rooms
//
//      - As we consider an interior wall, we see which group
//        the two rooms it separates belongs to.  If the rooms are
//        in the same group we leave the wall in place.  If the rooms
//        are in different groups we knock down the wall and absorb
//        all members of the group room two belongs to into the
//        group room one belongs to.
//
//    - Finally, we also determine the longest possible path
//      through the maze and use that path to determine the maze's
//      start and end points.  We find the longest path by:
//
//      - start with an empty list of the rooms we've already visited
//
//      - we begin with room(0, 0)
//
//      - each time we visit a room, we'll add that room to the list
//        of rooms we've already visited
//
//      - for each room, we'll examine if we have neighbors (rooms)
//        to the north, south, east and west and recursively visit
//        them if we've not already been to that room
//
//      - eventually, we'll run out of rooms to visit at which point
//        we report back where we ended up and how many hops it took
//        us to get there, we record the ending room that had the
//        largest number of hops
//
//      - using the above, we find the longest path from room(0, 0), but
//        this may not be the longest path through the maze overall, we
//        find that longest path by repeating the above steps but using
//        as the starting room, the room that was farthest from room(0, 0)
//
// Usage:
//
//    maze { -size rowsXcolumns } { -ps }
//       -ps         => postscript output (default is text)
//       -size 50x75 => 50 rows by 75 columns (default is 16x16)
//       -h          => display help information
// -----------------------------------------------------------------


/*****************************************************************
 * C/C++ Headers
 *****************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

#include <string.h>

#include <vector>
#include <set>
#include <map>

#include "maze.h"


#include "genmaze.h"
//dont include defs. Huge fuckup.
//#include "defs.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


using std::string;
using std::vector;

/*****************************************************************
 * Local Defines
 *****************************************************************/

#define N_ROWS    (3)
#define N_COLUMNS (3)

/*****************************************************************
 * Local Types
 *****************************************************************/


int maze_def[3][3][4];


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

static string toString(long value);

static void getLongestPath(Rooms &rooms, Room **beginPtr, Room **endPtr);

static void dumpTxt(Rooms &rooms, Room *first, Room *last);

static void dumpPS(Rooms &rooms, Room *first, Room *last);

static void init(
		 int           rows,
		 int           columns,
		 Rooms         &rooms,
		 Walls         &walls,
		 Cleaner<Room> &roomCleaner,
		 Cleaner<Wall> &wallCleaner
		 );

static bool equalsIC(char *first, char *second);

static bool getArgs(
		    int    argc,
		    char   **argv,
		    int    *rowsPtr,
		    int    *columnsPtr,
		    bool   *postScriptOutputPtr,
		    bool   *helpPtr,
		    string &errMsg
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

static string toString(long value)
{
  char buffer[255] = { '\0' };

  sprintf(buffer, "%ld", value);

  string s = buffer;

  return(s);
}

static void getLongestPath(Rooms &rooms, Room **beginPtr, Room **endPtr)
{
  // First, find the room that requires the longest path to
  // reach from the cell with row = 0, column = 0.

  Room *theRoom = rooms[0][0];
  Group history;

  theRoom->visit(0, history, theRoom);

  Room *rFirst = theRoom->getMaxRoom();

  // Now, find the room that requires the longest path to
  // reach from 'rFirst'.  We need to clear our history
  // so we'll be allowed to visit our neighbors again.

  history.clear();

  rFirst->visit(0, history, rFirst);

  Room *rLast = rFirst->getMaxRoom();

  *beginPtr = rFirst;
  *endPtr   = rLast;
}






static void dumpTxt(Rooms &rooms, Room *first, Room *last)
{

    int nRows    = rooms.size();
    int nColumns = rooms[0].size();


 

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
	maze_def[i][j][NORTH] = 1;
	maze_def[i][j][SOUTH] = 1;
	maze_def[i][j][EAST] = 1;
	maze_def[i][j][WEST] = 1;
      }
    }


    for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
       
      if(rooms[i][j]->hasNorth()){
	maze_def[i][j][NORTH] = 0;
	

      }
      if(rooms[i][j]->hasSouth()){
	maze_def[i][j][SOUTH] = 0;
	

      }      
      if(rooms[i][j]->hasWest()){
	maze_def[i][j][WEST] = 0;


      }


      if(rooms[i][j]->hasEast()){
		
	maze_def[i][j][EAST] = 0;

	

      }
    }
    }

    

   for(int i = 0; i < nRows; i++){
      for(int j = 0; j < nColumns; j++){
	printf("generator %d\n", maze_def[i][j][EAST]);
      }

    }
    

    
  string s =
    "Rows: " + toString(nRows) + ", Columns: " + toString(nColumns);

  bool hasFirstAndLast = false;

  if(first && last)
    {
      s              += " ";
      hasFirstAndLast = true;

      string fr = toString(first->mRow);
      string fc = toString(first->mColumn);
      string lr = toString(last->mRow);
      string lc = toString(last->mColumn);

      s +=
	"Start: [" + fr + ", " + fc + "], " +
	"End: [" + lr + ", " + lc + "]";
    }

  printf(
	 "========================================================\n"
	 "%s\n"
	 "========================================================\n",
	 s.c_str()
	 );

  const char *indent = "   ";
  int theWidth       = 3;
  string dashes      = "";
  string spaces      = "";
  int i              = 0;
  int j              = 0;

  for(i = 0; i < theWidth; i ++)
    {
      dashes += "-";
      spaces += " ";
    }

  for(i = nRows - 1; i >= 0; i --)
    {
      if(i == nRows - 1)
	{
	  printf("%s+", indent);

	  for(j = 0; j < nColumns; j ++)
            printf("%s+", dashes.c_str());

	  printf("\n");
	}

      for(j = 0; j < nColumns; j ++)
	{
	  if(j == 0)
            printf("%s|", indent);

	  char c = ' ';

	  if(hasFirstAndLast)
	    {
	      if(rooms[i][j] == first)
		c = 'S';

	      else if(rooms[i][j] == last)
		c = 'E';
	    }

	  printf(
		 " %c %c", c, rooms[i][j]->hasEast() ? ' ' : '|'
		 );
	}

      printf("\n");
      printf("%s+", indent);

      for(j = 0; j < nColumns; j ++)
	{
	  if(i == 0 || !rooms[i][j]->hasSouth())
            printf("%s+", dashes.c_str());

	  else
            printf("%s+", spaces.c_str());
	}

      printf("\n");
    }



}

static void dumpPS(Rooms &rooms, Room *first, Room *last)
{
  int nRows    = rooms.size();
  int nColumns = rooms[0].size();

  double pageHeight = 11.0 * 72.0;
  double pageWidth  = 8.5  * 72.0;
  double margin     = .25  * 72.0;
  double cellHeight = (pageHeight - (2 * margin)) / nRows;
  double cellWidth  = (pageWidth  - (2 * margin)) / nColumns;
  double cellSize   = (cellHeight < cellWidth ? cellHeight : cellWidth);
  double mazeHeight = cellSize * nRows;
  double mazeWidth  = cellSize * nColumns;
  double xStart     = (pageWidth  - mazeWidth)  / 2.0;
  double yStart     = (pageHeight - mazeHeight) / 2.0;

  printf("%%!PS-ADOBE\n");

  double y = yStart;

  for(int i = 0; i < nRows; i ++)
    {
      double x = xStart;

      for(int j = 0; j < nColumns; j ++)
	{
	  Room *r = rooms[i][j];

	  if(i == 0)
	    {
	      if(!r->hasSouth())
		{
		  printf(
			 "%f %f moveto %f %f lineto stroke\n",
			 x, y, x + cellSize, y
			 );
		}
	    }

	  if(i == 0 || j == 0)
	    {
	      if(!r->hasWest())
		{
		  printf(
			 "%f %f moveto %f %f lineto stroke\n",
			 x, y, x, y + cellSize
			 );
		}
	    }

	  if(!r->hasEast())
	    {
	      printf(
		     "%f %f moveto %f %f lineto stroke\n",
		     x + cellSize, y, x + cellSize, y + cellSize
		     );
	    }

	  if(!r->hasNorth())
	    {
	      printf(
		     "%f %f moveto %f %f lineto stroke\n",
		     x, y + cellSize, x + cellSize, y + cellSize
		     );
	    }

	  if(r == first || r == last)
	    {
	      printf(
		     "newpath %f %f %f 0 360 arc closepath fill\n",
		     x + cellSize / 2.0,
		     y + cellSize / 2.0,
		     .25 * cellSize
		     );
	    }

	  x += cellSize;
	}

      y += cellSize;
    }

  printf("showpage\n");
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

static bool equalsIC(char *first, char *second)
{
  int nFirst  = strlen(first);
  int nSecond = strlen(second);

  if(nFirst != nSecond){
    return(false);
  }
  while(*first)
    {
      if(toupper(*first) != toupper(*second))
	return(false);

      first++;
      second++;
    }

  return(true);
}



static bool getArgs(
		    int    argc,
		    char   **argv,
		    int    *rowsPtr,
		    int    *columnsPtr,
		    bool   *postScriptOutputPtr,
		    bool   *helpPtr,
		    string &errMsg
		    )
{
  *rowsPtr             = N_ROWS;
  *columnsPtr          = N_COLUMNS;
  *postScriptOutputPtr = false;
  *helpPtr             = false;

  for(int i = 1; i < argc; i ++)
    {
      if(argv[i][0] == '-')
	{
	  char *ptr = argv[i] + 1;

	  if(equalsIC(ptr, "size"))
	    {
	      if(i + 1 == argc)
		{
		  errMsg = "Missing value after '-size'";
		  return(false);
		}

	      ptr      = argv[i + 1];
	      string s = ptr;
	      char *x  = NULL;

	      if((x = strchr(ptr, 'x')) == NULL &&
		 (x = strchr(ptr, 'X')) == NULL)
		{
		  errMsg = "Invalid size: [" + s + "]";
		  return(false);
		}

	      char *endPtr  = NULL;
	      long int rows = strtol(ptr, &endPtr, 10);

	      if(endPtr != x)
		{
		  errMsg = "Invalid size: [" + s + "]";
		  return(false);
		}

	      long int columns = strtol(x + 1, &endPtr, 10);

	      if(*endPtr)
		{
		  errMsg = "Invalid size: [" + s + "]";
		  return(false);
		}

	      if(rows <= 1 || columns <= 1)
		{
		  errMsg = "Rows and columns must be at least 2: [" + s + "]";
		  return(false);
		}
 
	      *rowsPtr    = rows;
	      *columnsPtr = columns;
	    }
	  else if(equalsIC(ptr, "ps"))
	    {
	      *postScriptOutputPtr = true;
	    }
	  else if(equalsIC(ptr, "h"))
	    {
	      *helpPtr = true;
	    }
	  else
	    {
	      errMsg = "Invalid argument: [";
	      errMsg += argv[i];
	      errMsg += "]";

	      return(false);
	    }
	}
    }

  return(true);
}

/*****************************************************************
 * main
 *****************************************************************/

void generator(int argc, char **argv)
{
  int rows              = N_ROWS;
  int columns           = N_COLUMNS;
  bool postScriptOutput = false;
  bool help             = false;
  string errMsg         = "";

  bool status = getArgs(
			argc, argv, &rows, &columns, &postScriptOutput, &help, errMsg
			);

  if(!status || help)
    {
      printf(
	     "Usage: %s { -ps } { -size rowsXcolumns }\n"
	     "   -ps         => postscript output\n"
	     "   -size 50x75 => 50 rows by 75 columns\n"
	     "   -h          => display this message\n",
	     argv[0]
	     );

      if(!status)
	printf("\n%s\n", errMsg.c_str());

      return;
    }

  if(false)
    {
      printf(
	     "Rows: [%d], Columns: [%d], postScriptOutput: [%s]\n",
	     rows, columns, postScriptOutput ? "Yes" : "No"
	     );
    }

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
      if(false)
	{
	  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	  printf("(%d / %d)\n", i + 1, nWalls);
	  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	  dumpTxt(rooms, NULL, NULL);
	}

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

  Room *rFirst = NULL;
  Room *rLast  = NULL;

  getLongestPath(rooms, &rFirst, &rLast);

  void (*dump)(Rooms &, Room *, Room *) =
    postScriptOutput ? dumpPS : dumpTxt;



  dump(rooms, rFirst, rLast); //prints


}
