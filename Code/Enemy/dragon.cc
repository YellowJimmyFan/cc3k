#include "dragon.h"

Dragon::Dragon(pair<int, int> POS, pair<int, int> HoardPos): 
  Enemy{150, 20, 20, "dragon", POS}, HoardPos{HoardPos} {}

Dragon::~Dragon() {}

pair<int, int> Dragon::DHpos() const {
  return HoardPos;
}
