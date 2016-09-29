//
// Copyright (c) 2016 by Voaz Charov. All Rights Reserved.
//
#include <algorithm>
#include "Group.h"

Group::Group(int width) : width(width) {}

bool Group::addIndex(int group, int index) {
  auto it = cellGroup.find(group);
  if (it != cellGroup.end()) {
    if (std::find(it->second.begin(),
                  it->second.end(),
                  index) != it->second.end()) {
      return false;
    }
  }
  cellGroup.insert(std::make_pair(group, index));
  return true;
}

bool Group::removeIndex(int group, int index) {
  auto it = cellGroup.find(group);
  if (it != cellGroup.end()) {
    auto it_index = std::find(it->second.begin(),
                  it->second.end(),
                  index);
    if (it_index != it->second.end()) {
      it->second.erase(it_index);
      return true;
    }
  }
  return false;
}

int Group::getGroupSize(int group) {
  return cellGroup.find(group)->second.size();
}


int Group::getEmptyGroup() {
  for (size_t i = 0; i <= width; i++) {
    if (cellGroup.find(i) == cellGroup.end()) {
      return i;
    }
  }
  return -1;
}

int Group::getWhichGroupItemIs(int index) {
  for (auto it : cellGroup) {
    if (std::find(it.second.begin(),
                  it.second.end(),
                  index) != it.second.end()) {
      return it.first;
    }
  }
  return -1;
}

void Group::clear() {
  cellGroup.clear();
}
