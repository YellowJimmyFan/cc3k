#ifndef MERCHANT_H
#define MERCHANT_H

#include "ENEMY.h"
#include <map>
#include <vector>

const vector<string> items = {"RH", "BA", "BD"};

class Merchant : public Enemy {
  vector<pair<string, int>> bag;
 public:
  Merchant(pair<int, int> POS);
  ~Merchant();
  int bag_size() const override;
  bool has_item() const override;
  pair<string, int> get_item(int which) override;
  void consume(int which) override;
  string get_shopmsg() const override;
};

#endif
