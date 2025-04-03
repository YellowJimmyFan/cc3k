#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <ncurses.h>
#include <algorithm>

#include "cell.h"
#include "chamber.h"
#include "generator.h"

#include "Player/DECORATOR.h"
#include "Player/effects.h"

const vector<string> por_types = {"RH", "BA", "BD", "PH", "WA", "WD"};
const vector<string> gold_types = {"SP", "SP", "NP", "NP", 
                                   "NP", "NP", "NP", "DH"};
const vector<string> enemy_types = {"H", "H", "H", "H", "W", "W", "W", "L", 
                                    "L", "L", "L", "L", "E", "E", "O", "O",
                                    "M", "M"};
const vector<string> given_type = {"RH", "BA", "BD", "PH", "WA", "WD",
                                   "NP", "SP", "MH", "DH"};
const unordered_map<string, pair<int, int>> positions = {
  {"no", make_pair(-1, 0)},
  {"nw", make_pair(-1, -1)},
  {"we", make_pair(0, -1)},
  {"sw", make_pair(1, -1)},
  {"so", make_pair(1, 0)},
  {"se", make_pair(1, 1)},
  {"ea", make_pair(0, 1)},
  {"ne", make_pair(-1, 1)}
};
const vector<pair<int, int>> order_pos = {
  {-1, -1},
  {-1, 0},
  {-1, 1},
  {0, -1},
  {0, 1},
  {1, -1},
  {1, 0},
  {1, 1}
};
const map<char, string> commands = {
  {'w', "no"},
  {'a', "we"},
  {'s', "so"},
  {'d', "ea"},
  {'t', "nw"},
  {'y', "ne"},
  {'g', "sw"},
  {'h', "se"}
};

class Floor {
  int floorNum;
  bool win = false;
  string action_msg;
  bool frozen = false;
  Generator generator;
  PC *player;
  int spawnedChamber = 0;
  int stairChamber = -1;
  bool VALIDMOVED = true;
  bool is_newmap = false;
  bool mer_atked = false;
  vector<Chamber*> chambers;
  vector<Item*> items;
  vector<Enemy *> enemies;
  ifstream InputMap;
  vector<vector<Cell*>> themap;
 public:
  Floor(int floorNum, const string &mapname);
  ~Floor();
  int which_chamber(const pair<int, int> &pos);
  int valid_count(int chamber_num) const;
  int get_Score() const;
  pair<int, int> valid_pos(int index, int chamber_num) const;
  void freezeORunfreeze();
  vector<pair<int, int>> validPosNear(const pair<int, int> &pos) const;
  bool PlayerIsAround(const pair<int, int> &pos) const;
  bool Attackable(Enemy *which) const;
  Enemy *which_enemy(const pair<int, int> &pos) const;
  Item *which_item(const pair<int, int> &pos) const;
  void got_win();
  bool is_win();
  void showStat();
  bool is_moved() const;
  bool has_it(const string &type, pair<int, int> &pos);
  void show_interface(const string &file) const;
  void generatePC(const string &msg);
  void generate_PC(const string &file);
  void generateStair();
  void generateItems();
  vector<pair<int, int>> getDHpos() const;
  bool searchDH(pair<int, int> &pos, const vector<pair<int, int>> &DHpos);
  void generateDragons();
  void generateEnemy();
  void update_floor();
  void update_player(const pair<int, int> &pos);
  void reset_DH();
  void update_items();
  void update_enemies();
  void move_pc(const string &dir);
  void buy(const string &dir);
  void show_bag();
  void usePotion(const string &dir);
  void attack(const string &dir);
  void TrollFeature();
  void Eact();
  void resetActed();
  void setAllMerchantHostile();
  bool PCdies() const;
  void now_stat();
};

#endif
