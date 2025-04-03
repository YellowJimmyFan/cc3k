#ifndef HALFLING_H
#define HALFLING_H

#include "ENEMY.h"

class Halfling : public Enemy {
 public:
  Halfling(pair<int, int> POS);
  ~Halfling();
};

#endif
