#ifndef GOBLIN_H
#define GOBLIN_H

#include "PC.h"

class Goblin : public PC {
  Goblin(pair<int, int> pos);
  friend class Generator;
 public:
  ~Goblin();
};

#endif
