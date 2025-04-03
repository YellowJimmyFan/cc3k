#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include <iostream>
#include <utility>
#include <cstdlib>
#include "../Player/PC.h"

using namespace std;

class PC;
class Enemy {
 protected:
  int HP;
  int ATK;
  int DEF;
  int Gold;
  string race;
  bool hostile;
  bool acted = false;
  pair<int, int> POS;
  int damage = 0;
  string enemy_msg = "";
  Enemy(int HP, int ATK, int DEF, string race, pair<int, int> POS);
 public:
  virtual ~Enemy() = 0;
  int getHP() const;
  int getATK() const;
  int getDEF() const;
  int getGold() const;
  bool isDead() const;
  string getRace() const;
  void setHP(const int &hp);
  pair<int, int> getPos() const;
  void setPos(const pair<int, int> &pos);

  void setActed();
  void unsetActed();
  bool HasActed() const;
  void sethostile();
  bool ishostile() const;
  virtual pair<int, int> DHpos() const;
  bool success() const;
  virtual void attack(PC *player);
  string getMSG();
  virtual int bag_size() const;
  virtual bool has_item() const;
  virtual pair<string, int> get_item(int which);
  virtual void consume(int which);
  virtual string get_shopmsg() const;
};

#endif
