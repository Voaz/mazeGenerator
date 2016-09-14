

#ifndef CELL_H
#define CELL_H
#include <string>

class Cell {
public:
  Cell();

  int getID();
  int getBottom();
  int getRight();

  void setID(int id);
  void setParams(Cell& cell);
  void setRightBorder();
  void setBottomBorder();
  std::string toMJson();
  std::string toString();
private:
  int id;
  int top;
  int right;
  int left;
  int bottom;
};
#endif
