#include "elf.h"

Elf::Elf(pair<int, int> POS): Enemy{140, 30, 10, "elf", POS} {}

Elf::~Elf() {}

void Elf::attack(PC *player) {
  if (isDead()) {
    return ;
  }
  string Prace = player->getRace();
  float Pdef = player->getDEF();
  int Php = player->getHP();
  int initial = player->get_initialHP();
  damage = ceil((100/(100 + Pdef)) * ATK);
  damage = (damage > Php) ? Php : damage;
  if (success()) {
    enemy_msg = (Prace == "Drow") ? "E deals " + to_string(damage) 
                                               + " damage to PC. "
                                  : "E deals " + to_string(damage) + 
                                    " damage to PC(first attack) and ";
    player->setHP(initial - damage);
  } else {
    enemy_msg = (Prace != "Drow") ? 
                "E missed first attack and " :  "E missed. ";
  }
  int sec_DAM = 0;
  if (Prace == "Drow") {
    return ;
  } else {
    if (success()) {
      sec_DAM = (damage > (Php - damage)) ? (Php - damage) : damage;
      player->setHP(initial - damage - sec_DAM);
      enemy_msg += "deals " + to_string(sec_DAM) + 
                   " damage to PC(second attack). ";
    } else {
      enemy_msg += "missed second attack. ";
    }
  }
  damage = 0;
}
