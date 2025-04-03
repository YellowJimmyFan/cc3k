#include "cell.h"

Cell::Cell(const char &content): content{content} {
  if (content == '|' || content == '-') {
    is_wall = true;
  } else if (content == '+') {
    is_door = true;
  } else if (content == '#') {
    is_passage = true;
  } else if (content == ' ') {
    is_space = true;
  }
}

Cell::~Cell() { }

bool Cell::is_Door() const {
  return is_door;
}

bool Cell::is_Passage() const {
  return is_passage;
}

bool Cell::is_valid() const {
  return content == '.';
}

bool Cell::is_DH() const {
  return DH;
}

void Cell::setDH() {
  DH = !DH;
}

bool Cell::is_stair() const {
  return content == '\\';
}

bool Cell::is_potion() const {
  return content == 'P';
}

bool Cell::is_gold() const {
  return content == 'G';
}

bool Cell::is_smallenemy() const {
  if (content == 'H' || content == 'W' || content == 'L' || 
      content == 'E' || content == 'O' || content == 'M') {
    return true;
  }
  return false;
}

bool Cell::is_enemy() const {
  if (content == 'H' || content == 'W' || content == 'L' || content == 'E' ||
      content == 'O' || content == 'M' || content == 'D') {
    return true;
  }
  return false;
}

bool Cell::is_player() const {
  return content == '@';
}

void Cell::set_content(const char &c) {
  content = c;
}

char Cell::what_content() const {
  return content;
}

ostream &operator<<(ostream &out, const Cell &cell) {
  if (cell.is_enemy()) {
    out << RED;
  } else if (cell.is_potion()) {
    out << GREEN;
  } else if (cell.is_gold()) {
    out << YELLOW;
  } else if (cell.is_player() || cell.is_stair()) {
    out << BLUE;
  }
  return out << cell.content << DEFAULT;
}
