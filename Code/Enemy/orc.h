#ifndef ORC_H
#define ORC_H

#include "ENEMY.h"

class Orc : public Enemy {
 public:
  Orc(pair<int, int> POS);
  ~Orc();
  void attack(PC *player) override;
};

#endif
