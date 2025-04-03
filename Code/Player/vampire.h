#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "PC.h"

class Vampire : public PC {
  Vampire(pair<int, int> pos);
  friend class Generator;
 public:
  ~Vampire();
};

#endif
