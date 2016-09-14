//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//
#include "Cell.h"

Cell::Cell() {
  id = 0;
}

void Cell::setID(int id) {
  this->id = id;
}

int Cell::getID() {
  return id;
}

void Cell::setRightBorder() {
  right = 1;
}

int Cell::getBottom() {
  return bottom;
}

std::string Cell::toMJson() {
  return "[" + std::to_string(right) + ", " + std::to_string(bottom) + "]";
}

void Cell::setParams(Cell& cell) {
  if (cell.getBottom() != 1) {
    id = cell.getID();
  }
}

std::string Cell::toString() {
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

void Cell::setBottomBorder() {
  bottom = 1;
}

int Cell::getRight() {
  return right;
}
