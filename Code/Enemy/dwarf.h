#ifndef DWARF_H
#define DWARF_H

#include "ENEMY.h"

class Dwarf : public Enemy {
 public:
  Dwarf(pair<int, int> POS);
  ~Dwarf();
};

#endif
