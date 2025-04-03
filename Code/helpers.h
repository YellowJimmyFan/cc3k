#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <cctype>
#include <fstream>
#include "floor.h"

ostream &operator<<(ostream &out, ifstream &ifs);

string get_str(ifstream &ifs);

void reset_record(const string &file);

void move(Floor &f, bool &PlayAgain, const string &dir);

void use(Floor &f, const string &dir);

void attack(Floor &f, const string &dir);

bool is_digit(const string &s);

#endif
