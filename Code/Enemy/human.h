#ifndef HUMAN_H
#define HUMAN_H

#include "ENEMY.h"

class Human : public Enemy {
 public:
  Human(pair<int, int> POS);
  ~Human();
};

#endif
