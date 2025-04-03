#include "ENEMY.h"

Enemy::Enemy(int HP, int ATK, int DEF, string race, pair<int, int> POS):
  HP{HP}, ATK{ATK}, DEF{DEF}, race{race}, POS{POS} {
  Gold = (race == "human" || race == "merchant" || race == "dragon") 
         ? 0 : rand() % 2 + 1;
  hostile = (race == "merchant") ? false : true;
}

Enemy::~Enemy() {}

int Enemy::getHP() const {
  return HP;
}

int Enemy::getATK() const {
  return ATK;
}

int Enemy::getDEF() const {
  return DEF;
}

int Enemy::getGold() const {
  return Gold;
}

bool Enemy::isDead() const {
  return HP <= 0;
}

string Enemy::getRace() const {
  return race;
}

void Enemy::setHP(const int &hp) {
  HP = hp;
}

pair<int, int> Enemy::getPos() const {
  return POS;
}

void Enemy::setPos(const pair<int, int> &pos) {
  POS = pos;
}

void Enemy::setActed() {
  acted = true;
}

void Enemy::unsetActed() {
  acted = false;
}

bool Enemy::HasActed() const {
  return acted;
}

void Enemy::sethostile() {
  hostile = true;
}

bool Enemy::ishostile() const {
  return hostile;
}

pair<int, int> Enemy::DHpos() const { return make_pair(0, 0); }

bool Enemy::success() const {
  vector<bool> cases = {true, false};
  return cases[rand() % 2];
}

void Enemy::attack(PC *player) {
  if (isDead()) {
    return ;
  }
  string Erace = getRace();
  string initial = string(1, Erace[0] - ('a' - 'A'));
  if (Erace == "dwarf") {
    initial = "W";
  }
  if (Erace == "halfling") {
    initial = "L";
  }
  if (!success()) {
    enemy_msg = initial + " missed! ";
    return ; 
  }
  string Prace = player->getRace();
  float Pdef = player->getDEF();
  int Php = player->getHP();
  int initialHP = player->get_initialHP();
  damage = ceil((100/(100 + Pdef)) * ATK);
  damage = (damage > Php) ? Php : damage;
  enemy_msg = initial + " deals " + to_string(damage) + " damage to PC. ";
  player->setHP(initialHP - damage);
  damage = 0;
}

string Enemy::getMSG() {
  string msg = enemy_msg;
  enemy_msg = "";
  return msg;
}

int Enemy::bag_size() const { return 0; }

bool Enemy::has_item() const { return false; }

pair<string, int> Enemy::get_item(int which) { return make_pair("", 0); }

void Enemy::consume(int which) { }

string Enemy::get_shopmsg() const { return ""; }