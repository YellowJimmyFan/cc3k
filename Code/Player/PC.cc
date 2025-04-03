#include "PC.h"

PC::PC() {}

PC::PC(int MaxHP, int CurHP, int ATK, int DEF, string race, pair<int, int> POS):
  MaxHP{MaxHP}, CurHP{CurHP}, ATK{ATK}, DEF{DEF},
  Gold{0}, race{race}, POS{POS} {}

PC::~PC() {}

void PC::store_item(const string &type) {
  bag.emplace_back(type);
}

string PC::get_bagmsg() const {
  string msg;
  int count = 0;
  for (const auto &item : bag) {
    count++;
    msg += to_string(count) + ". " + item + "  ";
  }
  return msg;
}

vector<string> PC::get_bag() {
  return bag;
}

void PC::consume(int num) {
  bag.erase(bag.begin() + num);
}

int PC::getHP() const {
  return CurHP;
}

int PC::get_initialHP() const {
  return CurHP;
}

int PC::getATK() const {
  return ATK;
}

int PC::getDEF() const {
  return DEF;
}

int PC::getGold() const {
  return Gold;
}

int PC::getScore() const {
  if (race == "Shade") {
    return 1.5 * Gold;
  }
  return Gold;
}

string PC::getRace() const {
  return race;
}

pair<int, int> PC::getPos() const {
  return POS;
}

int PC::getMaxHP() const {
  return MaxHP;
}

void PC::setHP(const int &hp) {
  CurHP = hp;
}

void PC::addGold(const int &amount) {
  Gold += amount;
}

void PC::setPos(const pair<int, int> &pos) {
  POS = pos;
}

bool PC::success() const {
  vector<bool> cases = {true, false};
  return cases[rand() % 2];
}

void PC::attack(Enemy *enemy) {
  string Prace = getRace();
  string Erace = enemy->getRace();
  int initial = get_initialHP();
  if (Erace == "halfling") {
    if (!success()) { 
      player_msg = "PC missed! ";
      return ; 
    }
  }
  if (Prace == "Vampire") {
    (Erace == "dwarf") ? setHP(initial - 5) : setHP(initial + 5);
  }
  float Edef = enemy->getDEF();
  int Ehp = enemy->getHP();
  int atk = getATK();
  damage = ceil((100/(100 + Edef)) * atk);
  damage = (damage > Ehp) ? Ehp : damage;
  char c = (Erace == "halfling") ? 'l' : ((Erace == "dwarf") ? 'w' : Erace[0]);
  player_msg = "PC deals " + to_string(damage) + " damage to " + string(1, c - ('a' - 'A')) + 
               " (" + to_string(Ehp - damage) + " HP). ";
  enemy->setHP(Ehp - damage);
  damage = 0;
}

string PC::getmsg() {
  string msg = player_msg;
  player_msg = "";
  return msg;
}

bool PC::isDead() const {
  return CurHP <= 0;
}

string PC::getEffect() const { return ""; }
