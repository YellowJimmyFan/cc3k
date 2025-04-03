#ifndef GENERATOR_H
#define GENERATOR_H

#include <utility>

#include "Player/PC.h"
#include "Player/drow.h"
#include "Player/shade.h"
#include "Player/troll.h"
#include "Player/goblin.h"
#include "Player/vampire.h"

#include "Enemy/ENEMY.h"
#include "Enemy/elf.h"
#include "Enemy/orc.h"
#include "Enemy/dwarf.h"
#include "Enemy/human.h"
#include "Enemy/dragon.h"
#include "Enemy/halfling.h"
#include "Enemy/merchant.h"

#include "Item/ITEM.h"
#include "Item/potion.h"
#include "Item/treasure.h"

using namespace std;

class Generator {
 public:
  PC *createPC(const pair<int, int> &pos, const string &race = "s");
  Enemy *createEnemy(const pair<int, int> &pos, const string &race);
  Enemy *createDragon(const pair<int, int> &pos, const pair<int, int> &DHPos);
  Item *createItem(const pair<int, int> &pos, const string &type);
};

#endif
