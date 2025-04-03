#include "orc.h"

Orc::Orc(pair<int, int> POS): Enemy{180, 30, 25, "orc", POS} {}

Orc::~Orc() {}

void Orc::attack(PC *player) {
  if (isDead()) {
    return ;
  }
  if (!success()) { 
    enemy_msg = "O missed! ";
    return ; 
  }
  string Prace = player->getRace();
  float Pdef = player->getDEF();
  int Php = player->getHP();
  int initial = player->get_initialHP();
  damage = (Prace == "Goblin") ? ceil((100/(100 + Pdef)) * ATK) * 1.5 :
                                 ceil((100/(100 + Pdef)) * ATK);
  damage = (damage > Php) ? Php : damage;
  enemy_msg = "O deals " + to_string(damage) + " damage to PC. ";
  player->setHP(initial - damage);
  damage = 0;
}
