#ifndef CELL_H
#define CELL_H

#define DEFAULT "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

#include <iostream>

using namespace std;

class Cell {
  char content;
  bool DH = false;
  bool is_wall = false;
  bool is_door = false;
  bool is_passage = false;
  bool is_space = false;
 public:
  Cell(const char &content);
  ~Cell();
  bool is_Door() const;
  bool is_Passage() const;
  bool is_valid() const;
  bool is_DH() const;
  void setDH();
  bool is_stair()const;
  bool is_potion() const;
  bool is_gold() const;
  bool is_smallenemy() const;
  bool is_enemy() const;
  bool is_player() const;
  void set_content(const char &c);
  char what_content() const;
  friend ostream &operator<<(ostream &out, const Cell &cell);
};

#endif
