#ifndef EFFECTS_H
#define EFFECTS_H

#include "DECORATOR.h"

using namespace std;

class Effects : public Decorator {
  int rh = 10;
  int ph = -10;
  int ba = 5;
  int wa = -5;
  int bd = 5;
  int wd = -5;
  string type;
  int Damage = 0;
  string msg = "";
 public:
  Effects(PC *effected, string type);

  void store_item(const string &type) override;
  string get_bagmsg() const override;
  vector<string> get_bag() override;
  void consume(int num) override;

  int getHP() const override;
  int get_initialHP() const override;
  int getATK() const override;
  int getDEF() const override;
  int getGold() const override;
  int getScore() const override;
  string getRace() const override;
  pair<int, int> getPos() const override;

  int getMaxHP() const override;
  void setHP(const int &HP) override;
  void addGold(const int &amount) override;
  void setPos(const pair<int, int> &pos) override;

  void attack(Enemy *enemy) override;
  string getmsg() override;
  bool isDead() const override;

  string getEffect() const override;
};

#endif
