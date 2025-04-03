#ifndef ITEM_H
#define ITEM_H

#include <utility>
#include <iostream>

using namespace std;

class Item {
 protected:
  int hp;
  int atk;
  int def;
  int gold;
  pair<int, int> POS;
  string type;
  bool valid = true;
  Item(pair<int, int> POS, string type);
 public:
  virtual ~Item() = 0;
  int getGold() const;
  bool isValid() const;
  void invalidate();
  string getType() const;
  pair<int, int> getPos() const;
};

#endif
