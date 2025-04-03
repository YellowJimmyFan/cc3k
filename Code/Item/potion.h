#ifndef POTION_H
#define POTION_H

#include "ITEM.h"

class Potion : public Item {
  Potion(pair<int, int> POS, string type);
 public:
  ~Potion();
  friend class Generator;
};

#endif
