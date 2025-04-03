#ifndef TREASURE_H
#define TREASURE_H

#include "ITEM.h"

class Treasure : public Item {
  Treasure(pair<int, int> POS, string type);
 public:
  ~Treasure();
  friend class Generator;
};

#endif
