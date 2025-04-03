#include "chamber.h"

using namespace std;

Chamber::Chamber(int chamberNum): chamberNum{chamberNum} {
  pair<int, int> colRange;
  if (chamberNum == 0) {
    for (int i = 3; i < 7; ++i) {
      colRange = make_pair(3, 28);
      range.emplace(i, colRange);
    }
  } else if (chamberNum == 1) {
      for (int i = 15; i < 22; ++i) {
        colRange = make_pair(4, 24);
        range.emplace(i, colRange);
      }
  } else if (chamberNum == 2) {
      for (int i = 10; i < 13; ++i) {
        colRange = make_pair(38, 49);
        range.emplace(i, colRange);
      }
  } else if (chamberNum == 3) {
      for (int i = 3; i < 13; ++i) {
        if (i < 5) {
          colRange = make_pair(39, 61);
        } else if (i == 5) {
            colRange = make_pair(39, 69);
        } else if (i == 6) {
            colRange = make_pair(39, 72);
        } else {
            colRange = make_pair(61, 75);
        }
        range.emplace(i, colRange);
      }
  } else if (chamberNum == 4) {
      for (int i = 16; i < 22; ++i) {
        (i < 19) ? colRange = make_pair(65, 75)
                 : colRange = make_pair(37, 75);
        range.emplace(i, colRange);
      }
  }
}

Chamber::~Chamber() {}

int Chamber::CurChamber() const {
  return chamberNum;
}

map<int, pair<int, int>> Chamber::getRange() const {
  return range;
}
