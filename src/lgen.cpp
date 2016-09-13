//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <chrono>
#include <utility>
#include <vector>
#include <map>
#include <string>

#include "json/value.h"

class Cell {
public:
  Cell() { id = 0;}
  void setID(int id);
  int getID();
  void setRightBorder() { right = 1; }
  int getBottom() { return bottom; }
  std::string toMJson() {
    return "[" + std::to_string(right) + ", " + std::to_string(bottom) + "]";
  }
  void setParams(Cell& cell) {
    if (cell.getBottom() != 1) {
      id = cell.getID();
    }
  }
  std::string toString() {
    std::string ret = std::to_string(id);

    if (bottom == 1) {
      ret += "_";
    }
    if (right == 1) {
      ret += "|";
    } else {
      ret += " ";
    }
    return ret;
  }
  void setBottomBorder() { bottom = 1; }
private:
  int id;
  int top;
  int right;
  int left;
  int bottom;
};

void Cell::setID(int id) {
  this->id = id;
}
int Cell::getID() {
  return id;
}
int getRandomNumber(int start, int end) {
  // std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  // std::uniform_int_distribution<int> distribution(start, end);
  // return distribution(generator);
  return rand() % (end - start) + start;
}

std::pair<int, int> nextStep() {}

Cell **generatePaths(Cell **field, int w, int h) {
  std::map<int, int> groups;

  for (size_t j = 0; j < w; j++) {
    groups.clear();
    // second step
    for (size_t i = 0; i < h; i++) {
      if (field[j][i].getID() == 0) {
        field[j][i].setID(i+1);
      }
      groups[field[j][i].getID()]++;
    }
    // third step
    for (size_t i = 0; i < h; i++) {
      if (getRandomNumber(0, 2) == 1) {
        field[j][i].setRightBorder();
      } else {
        if (i + 1 <= w) {
          if (field[j][i].getID() == field[j][i+1].getID()) {
            field[j][i].setRightBorder();
            field[j][i+1].setID(i+2);
            groups[field[j][i].getID()]--;
            groups[field[j][i+1].getID()]++;
          } else {
            groups[field[j][i+1].getID()]--;
            field[j][i+1].setID(field[j][i].getID());
            groups[field[j][i].getID()]++;
          }
        }
      }
    }
    // fourth step
    for (size_t i = 0; i < h; i++) {
      if (getRandomNumber(0, 2) == 1 && groups[field[j][i].getID()] > 1) {
        field[j][i].setBottomBorder();
      }
    }

    // fiveth step
    for (size_t i = 0; i < h; i++) {
      std::cout << field[j][i].toString();
    }
    std::cout << "\n";
    groups.clear();
    if (j + 1 < w) {
      for (size_t i = 0; i < h; i++) {
        field[j+1][i].setParams(field[j][i]);
      }
    }

  }
}

void convertToJson(Cell **field, int w, int h) {
  Json::Value root;

  //root["maze"] = "test";
  root["width"] = w;
  root["height"] = h;
  for (size_t i = 0; i < w; i++) {
    for (size_t j = 0; j < h; j++) {
      std::cout << "test" << i << std::endl;
      root["Cells"][std::to_string(i)][std::to_string(j)].append(Json::arrayValue())
        field[i][j].toMJson();
      //root["2"]["bottom"] = 1;
    }

  }


  std::cout << "\n" << root.toStyledString() << "\n";
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  int lab_width;
  int lab_height;
  int player_pos_w;
  int player_pos_h;

  std::cin >> lab_width;
  std::cin >> lab_height;
  std::cin >> player_pos_w;
  std::cin >> player_pos_h;

  Cell **field = new Cell*[lab_width];
  for (size_t i = 0; i < lab_width; i++) {
    field[i] = new Cell[lab_height];
  }

  generatePaths(field, lab_width, lab_height);

  convertToJson(field, lab_width, lab_height);

  return 0;
}
