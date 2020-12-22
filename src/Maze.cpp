//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//
#include "Maze.h"
#include "Group.h"

Maze::Maze(int width, int height) {
  field = new Cell*[width];
  for (size_t i = 0; i < width; i++) {
    field[i] = new Cell[height];
  }
}

void Maze::CreateMaze() {
  Group *groups = new Group(width);
  for (size_t i = 0; i < width; i++) {
    groups->clear();

    for (size_t j = 0; j < height; j++) {
      if (field[i][j].getID() == 0) {
        field[i][j].setID(j+1);
      }

      groups->addIndex(field[j][i].getID(), i);
    }
  }
}

