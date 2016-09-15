//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "json/value.h"
#include "Cell.h"

 #define LGEN_DEBUG

int getRandomNumber(int start, int end) {
  // std::default_random_engine
  // generator(std::chrono::system_clock::now().time_since_epoch().count());
  // std::uniform_int_distribution<int> distribution(start, end);
  // return distribution(generator);
  return rand() % (end - start) + start;
}

Cell **generatePaths(int w, int h) {
  Cell **field = new Cell*[w];
  for (size_t i = 0; i < w; i++) {
    field[i] = new Cell[h];
  }

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
      }
    }
  }
  return field;
}

void convertToJson(Cell **field, int w, int h) {
  Json::Value root;

  root["width"] = w;
  root["height"] = h;

  for (size_t i = 0, k = 0; i < w; i++) {
    for (size_t j = 0; j < h; j++) {
      Json::Value temp;
      temp["id"] = k;
      temp["right"] =  field[i][j].getRight();
      temp["bottom"] = field[i][j].getBottom();
      root["Cells"].append(temp);
      temp.clear();
      k++;
    }
  }
  std::ofstream fjson(std::to_string(time(nullptr)) + ".json");
  fjson << root.toStyledString();
  fjson.close();
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

  Cell **field = generatePaths(lab_width, lab_height);

  convertToJson(field, lab_width, lab_height);

  delete []field;

  return 0;
}
