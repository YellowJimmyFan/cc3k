#ifndef ELF_H
#define ELF_H

#include "ENEMY.h"

class Elf : public Enemy {
 public:
  Elf(pair<int, int> POS);
  ~Elf();
  void attack(PC *player) override;
};

#endif
