#include "generator.h"
#include <stdexcept>

PC *Generator::createPC(const pair<int, int> &pos, const string &race) {
  if (race == "d") {
    return new Drow{pos};
  } else if (race == "g") {
      return new Goblin{pos};
  } else if (race == "s") {
      return new Shade{pos};
  } else if (race == "t") {
      return new Troll{pos};
  } else if (race == "v"){
      return new Vampire{pos};
  } else {
      string msg = "INVALID RACE";
      throw runtime_error(msg);
  }
}

Enemy *Generator::createEnemy(const pair<int, int> &pos, const string &race) {
  if (race == "H") {
    return new Human{pos};
  } else if (race == "W") {
      return new Dwarf{pos};
  } else if (race == "E") {
      return new Elf{pos};
  } else if (race == "O") {
      return new Orc{pos};
  } else if (race == "M"){
      return new Merchant{pos};
  } else {
      return new Halfling{pos};
  }
}

Enemy *Generator::createDragon(const pair<int, int> &pos, const pair<int, int> &DHPos) {
  return new Dragon{pos, DHPos};
}

Item *Generator::createItem(const pair<int, int> &pos, const string &type) {
  if (type == "SP" || type == "NP" || type == "MH" || type == "DH") {
    return new Treasure{pos, type};
  } else {
    return new Potion{pos, type};
  }
}
