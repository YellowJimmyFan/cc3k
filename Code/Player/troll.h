#ifndef TROLL_H
#define TROLL_H

#include "PC.h"

class Troll : public PC {
  Troll(pair<int, int> pos);
  friend class Generator;
 public:
  ~Troll();
};

#endif
