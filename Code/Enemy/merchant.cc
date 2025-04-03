#include "merchant.h"

Merchant::Merchant(pair<int, int> POS): Enemy{30, 70, 5, "merchant", POS} {
  for (int i = 0; i < 4; i++) {
    bag.emplace_back(items[rand()%3], (rand()%6)+5);
  }
}

Merchant::~Merchant() {}

int Merchant::bag_size() const {
  return bag.size();
}

bool Merchant::has_item() const {
  return bag.size() !=  0;
}

pair<string, int> Merchant::get_item(int which) {
  return bag[which];
}

void Merchant::consume(int which) {
  bag.erase(bag.begin() + which);
}

string Merchant::get_shopmsg() const {
  string msg;
  int count = 0;
  for (const auto &item : bag) {
    count++;
    msg += to_string(count) + ". " + item.first + " " + to_string(item.second) + "Gold  ";
  }
  return msg;
}
