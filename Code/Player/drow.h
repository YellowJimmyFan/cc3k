#ifndef DROW_H
#define DROW_H

#include "PC.h"

class Drow : public PC {
  Drow(pair<int, int> pos);
  friend class Generator;
 public:
  ~Drow();
};

#endif
