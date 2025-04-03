#ifndef DRAGON_H
#define DRAGON_H

#include "ENEMY.h"

class Dragon : public Enemy {
  pair<int, int> HoardPos;
 public:
  Dragon(pair<int, int> POS, pair<int, int> HoardPos);
  ~Dragon();
  pair<int, int> DHpos() const override;
};

#endif
