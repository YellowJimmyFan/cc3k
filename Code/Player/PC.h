#ifndef PC_H
#define PC_H

#include <cmath>
#include <climits>
#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include "../Enemy/ENEMY.h"

using namespace std;

class Enemy;
class PC {
 protected:
  int MaxHP;
  int CurHP;
  int ATK;
  int DEF;
  int Gold;
  string race;
  vector<string> bag;
  int damage = 0;
  string player_msg = "";
  pair<int, int> POS;
  PC(int MaxHP, int CurHP, int ATK, int DEF, string race, pair<int, int> POS);
 public:
  PC();
  virtual ~PC() = 0;

  virtual void store_item(const string &type);
  virtual string get_bagmsg() const;
  virtual vector<string> get_bag();
  virtual void consume(int num);
  virtual int getHP() const;
  virtual int get_initialHP() const;
  virtual int getATK() const;
  virtual int getDEF() const;
  virtual int getGold() const;
  virtual int getScore() const;
  virtual string getRace() const;
  virtual pair<int, int> getPos() const;

  virtual int getMaxHP() const;
  virtual void setHP(const int &hp);
  virtual void addGold(const int &amount);
  virtual void setPos(const pair<int, int> &pos);

  bool success() const;
  virtual void attack(Enemy *enemy);
  virtual string getmsg();
  virtual bool isDead() const;
  virtual string getEffect() const;
};

#endif
