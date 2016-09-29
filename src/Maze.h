#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"


class Maze {
public:
  Maze(int width, int height);
  void CreateMaze();
private:
  Cell **field;
  int width;
  int height;
};
#endif //MAZE_H
