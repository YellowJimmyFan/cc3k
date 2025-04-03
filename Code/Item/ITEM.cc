#include "ITEM.h"

Item::Item(pair<int, int> POS, string type): POS{POS}, type{type} {
  hp = 0;
  atk = 0;
  def = 0;
  gold = 0;
  if (type == "RH") {
    hp = 10;
  } else if (type == "BH") {
      hp = -10;
  } else if (type == "BA") {
      atk = 5;
  } else if (type == "WA") {
      atk = -5;
  } else if (type == "BD") {
      def = 5;
  } else if (type == "WD") {
      def = -5;
  } else if (type == "SP") {
      gold = 1;
  } else if (type == "NP") {
      gold = 2;
  } else if (type == "MH") {
      gold = 4;
  } else if (type == "DH") {
      gold = 6;
      valid = false;
  }
}

Item::~Item() {}

int Item::getGold() const {
  return gold;
}

bool Item::isValid() const {
  return valid;
}

void Item::invalidate() {
  valid = false;
}

string Item::getType() const {
  return type;
}

pair<int, int> Item::getPos() const {
  return POS;
}
