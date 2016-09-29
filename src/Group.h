//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//
#ifndef GROUP_H
#define GROUP_H

#include <stdlib.h>
#include <map>
#include <vector>

class Group {
public:
  Group(int width);
  bool addIndex(int group, int index);
  bool removeIndex(int group, int index);
  int getGroupSize(int group);
  int getEmptyGroup();
  int getWhichGroupItemIs(int index);
  void clear();
private:
  int width;
  std::map<int, std::vector<int>> cellGroup;
};
#endif
