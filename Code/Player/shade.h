#ifndef SHADE_H
#define SHADE_H

#include "PC.h"

class Shade : public PC {
  Shade(pair<int, int> pos);
  friend class Generator;
 public:
  ~Shade();
};

#endif
