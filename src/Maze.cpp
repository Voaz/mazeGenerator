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

Cell **generatePaths(int w, int h) {
  Cell **field = new Cell*[w];
  for (size_t i = 0; i < w; i++) {
    field[i] = new Cell[h];
  }

  std::map<int, std::vector<int>> groups;

  for (size_t j = 0; j < w; j++) {
    groups.clear();
    // second step
    for (size_t i = 0; i < h; i++) {
      if (field[j][i].getID() == 0) {
        field[j][i].setID(i+1);
      }

      groups[field[j][i].getID()].push_back(i);
    }
    showGroups(groups);
    // third step
    for (size_t i = 0; i < h; i++) {
      if (getRandomNumber(0, 2) == 1) {
        field[j][i].setRightBorder();
      } else {
        if (i + 1 <= w) {
          if (field[j][i].getID() == field[j][i+1].getID()) {
            field[j][i].setRightBorder();
            // field[j][i+1].setID(i+2);
            // groups[field[j][i].getID()]--;
            // groups[field[j][i+1].getID()]++;
          } else {
            auto it = std::find(groups[field[j][i+1].getID()].begin(),
                                groups[field[j][i+1].getID()].end(), i + 1);
            if (it != groups[field[j][i+1].getID()].end()) {
                groups[field[j][i+1].getID()].erase(it);
            }
            // groups[field[j][i+1].getID()].erase(
            //   groups[field[j][i+1].getID()].begin() +
            //   std::find_end(groups[field[j][i+1].getID()].begin(),
            //
            //   )
            // );
            // groups[field[j][i+1].getID()].erase(
            //   std::remove(std::begin(groups[field[j][i+1].getID()]),
            //   std::end(groups[field[j][i+1].getID()]), i+1),
            //   groups[field[j][i+1].getID()].end());
            field[j][i+1].setID(field[j][i].getID());
            groups[field[j][i].getID()].push_back(i);
          }
        }
      }
    }
    #ifdef LGEN_DEBUG
        // fiveth step
        for (size_t i = 0; i < h; i++) {
          std::cout << field[j][i].toString();
        }
        std::cout << "\n";
    #endif
    showGroups(groups);
    // fourth step
    for (size_t i = 0; i < h; i++) {
      if (getRandomNumber(0, 2) == 1 && groups[field[j][i].getID()].size() >1) {
        field[j][i].setBottomBorder();
        auto it = std::find(groups[field[j][i].getID()].begin(),
                            groups[field[j][i].getID()].end(), i);
        if (it != groups[field[j][i+1].getID()].end()) {
            groups[field[j][i+1].getID()].erase(it);
        }
        // groups[field[j][i].getID()].erase(
        //   std::remove(groups[field[j][i].getID()].begin(),
        //   groups[field[j][i].getID()].end(), i),
        //   groups[field[j][i].getID()].end());;
      }
    }
    // showGroups(groups);
#ifdef LGEN_DEBUG
    // fiveth step
    for (size_t i = 0; i < h; i++) {
      std::cout << field[j][i].toString();
    }
    std::cout << "\n";
#endif
    groups.clear();
    if (j + 1 < w) {
      for (size_t i = 0; i < h; i++) {
        field[j+1][i].setParams(field[j][i]);
        if (field[j+1][i].getRight() == 1) {
          /* code */
        }
      }
    }
  }
  return field;
}
