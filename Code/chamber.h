#ifndef CHAMBER_H
#define CHAMBER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Chamber {
  int chamberNum;
  map<int, pair<int, int>> range;
 public:
  Chamber(int chamberNum);
  ~Chamber();
  int CurChamber() const;
  map<int, pair<int, int>> getRange() const;
};

#endif
