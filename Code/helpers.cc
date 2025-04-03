#include "helpers.h"

ostream &operator<<(ostream &out, ifstream &ifs) {
  string line;
  while (getline(ifs, line)) cout << line << endl;
  return out;
}

string get_str(ifstream &ifs) {
  string line;
  string s;
  while (getline(ifs, line)) s += line + '\n';
  return s;
}

void reset_record(const string &file) {
  ifstream ifs{file};
  string line;
  getline(ifs, line);
  ifs.close();
  ofstream ofs{file};
  ofs << 0 << endl;
  ofs.close();
}

void move(Floor &f, bool &PlayAgain, const string &dir) {
  string line;
  f.move_pc(dir);
  if (f.is_moved()) f.TrollFeature();
  f.Eact();
  f.now_stat();
  if (!f.PCdies()) {
    f.resetActed();
  }
}

void use(Floor &f, const string &dir) {
  f.usePotion(dir);
  if (f.is_moved()) f.TrollFeature();
  f.Eact();
  f.now_stat();
  if (!f.PCdies()) {
    f.resetActed();
  }
}

void attack(Floor &f, const string &dir) {
  f.attack(dir);
  if (f.is_moved()) f.TrollFeature();
  f.Eact();
  f.now_stat();
  if (!f.PCdies()) {
    f.resetActed();
  }
}

bool is_digit(const string &s) {
  for (const char &c : s) {
    if (!isdigit(c)) return false;
  }
  return true;
}
