#include "effects.h"

Effects::Effects(PC *effected, string type): Decorator{effected}, type{type} {
  int cur_hp = effected->getHP();
  int cur_atk = effected->getATK();
  int cur_def = effected->getDEF();
  int max_hp = effected->getMaxHP();
  string cur_race = effected->getRace();
  if (cur_race == "Drow") {
    rh *= 1.5;
    ph *= 1.5;
    ba *= 1.5;
    wa *= 1.5;
    bd *= 1.5;
    wd *= 1.5;
  }
  int diff = 0;
  if (type == "RH") {
    diff = max_hp - cur_hp;
    rh = (diff < rh) ? diff : rh;
  } else if (type == "PH") {
    diff = ph + cur_hp;
    ph = (diff < 0) ? -cur_hp : ph;
  } else if (type == "WA") {
    diff = wa + cur_atk;
    wa = (diff < 0) ? -cur_atk : wa;
  } else if (type == "WD") {
    diff = wd + cur_def;
    wd = (diff < 0) ? -cur_def : wd;
  }
}

void Effects::store_item(const string &type) {
  original->store_item(type);
}

string Effects::get_bagmsg() const {
  return original->get_bagmsg();
}

vector<string> Effects::get_bag() {
  return original->get_bag();
}

void Effects::consume(int num) {
  original->consume(num);
}

int Effects::getHP() const {
  int result = (type == "RH") ? rh : ((type == "PH") ? ph : 0);
  return original->getHP() + result;
}

int Effects::get_initialHP() const {
  return original->get_initialHP();
}

int Effects::getATK() const {
  int result = (type == "BA") ? ba : ((type == "WA") ? wa : 0);
  return original->getATK() + result;
}

int Effects::getDEF() const {
  int result = (type == "BD") ? bd : ((type == "WD") ? wd : 0);
  return original->getDEF() + result;
}

int Effects::getGold() const {
  return original->getGold();
}

int Effects::getScore() const {
  if (original->getRace() == "Shade") {
    return 1.5 * original->getGold();
  }
  return original->getGold();
}

string Effects::getRace() const {
  return original->getRace();
}

pair<int, int> Effects::getPos() const {
  return original->getPos();
}

int Effects::getMaxHP() const {
  return original->getMaxHP();
}

void Effects::setHP(const int &HP) {
  original->setHP(HP);
}

void Effects::addGold(const int &amount) {
  original->addGold(amount);
}

void Effects::setPos(const pair<int, int> &pos) {
  original->setPos(pos);
}

string Effects::getEffect() const {
  string msg = "";
  if (type == "RH") {
    msg = "(" + to_string(rh) + " health points RESTORED)"; 
  } else if (type == "PH") {
    msg = "(" + to_string(ph) + " health points)"; 
  } else if (type == "BA") {
    msg = "(" + to_string(ba) + " ATK DAMAGE INCREASED)"; 
  } else if (type == "WA") {
    msg = "(" + to_string(wa) + " ATK DAMAGE)"; 
  } else if (type == "BD") {
    msg = "(" + to_string(bd) + " DEF ABILITY INCREASED)"; 
  } else {
    msg = "(" + to_string(wd) + " DEF ABILITY)"; 
  }
  return msg;
}

void Effects::attack(Enemy *enemy) {
  string Prace = getRace();
  string Erace = enemy->getRace();
  if (Erace == "halfling") {
    if (!original->success()) {
      Damage = 0;
      msg = "PC missed! ";
      return ; 
    }
  }
  if (Prace == "Vampire") {
    (Erace == "dwarf") ? setHP(original->get_initialHP() - 5) 
                       : setHP(original->get_initialHP() + 5);
  }
  float Edef = enemy->getDEF();
  int Ehp = enemy->getHP();
  int atk = getATK();
  Damage = ceil((100/(100 + Edef)) * atk);
  Damage = (Damage > Ehp) ? Ehp : Damage;
  char c = (Erace == "halfling") ? 'l' : ((Erace == "dwarf") ? 'w' : Erace[0]);
  msg = "PC deals " + to_string(Damage) + " damage to " + 
        string(1, c - ('a' - 'A')) + " (" + to_string(Ehp - Damage) + " HP). ";
  enemy->setHP(Ehp - Damage);
  Damage = 0;
}

string Effects::getmsg() {
  string MSG = msg;
  msg = "";
  return MSG;
}

bool Effects::isDead() const {
  return getHP() <= 0;
}
