#include "floor.h"

using namespace std;

Floor::Floor(int floorNum, const string &mapname)
  : floorNum{floorNum}, InputMap{mapname} {
  for (int i = 0; i < 5; ++i) {
    chambers.push_back(new Chamber{i});
  }
  string stringLine;
  vector<Cell*> charLine;
  bool start = false;
  int count = 0;
  while (count < 25 && getline(InputMap, stringLine)) {
    if (!start) {
      if (stringLine.empty()) continue;
      else start = true; 
    }
    for (const char &c : stringLine) {
      charLine.push_back(new Cell{c});
    }
    themap.emplace_back(charLine);
    charLine.clear();
    count++;
  }
  player = generator.createPC(make_pair(0, 0), "s");
  if (mapname != "./txtFiles/cc3k-emptySingleFloor.txt") is_newmap = true;
}

Floor::~Floor() {
  delete player;
  for (auto p : chambers) {
    delete p;
  }
  for (auto row : themap) {
    for (auto cell : row) {
      delete cell;
    }
  }
  for (auto item : items) {
    delete item;
  }
  for (auto enemy : enemies) {
    delete enemy;
  }
  chambers.clear();
  themap.clear();
  items.clear();
  enemies.clear();
}

bool Floor::is_moved() const { return VALIDMOVED; }

int Floor::which_chamber(const pair<int, int> &pos) {
  int fir = pos.first, sec = pos.second;
  if (fir >= 3 && fir <= 6) {
    if (sec >= 3 && sec <= 28) return 0;
    else return 3;
  } else if (fir >= 7 && fir <= 12) {
    if (sec >= 38 && sec <= 49) return 2;
    else return 3;
  } else {
    if (sec >= 4 && sec <= 24) return 1;
    else return 4;
  }
}

int Floor::valid_count(int chamber_num) const {
  map<int, pair<int, int>> range = chambers[chamber_num]->getRange();
  int valid_num = 0;
  for (const auto &pairs : range) {
    int row = pairs.first;
    int left = pairs.second.first;
    int right = pairs.second.second;
    for (int col = left; col <= right; ++col) {
      if (themap[row][col]->is_valid() && !(themap[row][col]->is_DH())) {
        ++valid_num;
      }
    }
  }
  return valid_num;
}

int Floor::get_Score() const {
  return player->getScore();
}

pair<int, int> Floor::valid_pos(int index, int chamber_num) const {
  map<int, pair<int, int>> range = chambers[chamber_num]->getRange();
  int count = 0;
  pair<int, int> pos;
  bool finish = false;
  for (const auto &pairs : range) {
    int row = pairs.first;
    int left = pairs.second.first;
    int right = pairs.second.second;
    for (int col = left; col <= right; ++col) {
      if (themap[row][col]->is_valid() && !(themap[row][col]->is_DH())) {
        if (count == index) {
          pos = make_pair(row, col);
          finish = true;
          break;
        }
        ++count;
      }
    }
    if (finish) break;
  }
  return pos;
}

void Floor::freezeORunfreeze() {
  frozen = !frozen;
}

vector<pair<int, int>> Floor::validPosNear(const pair<int, int> &pos) const {
  vector<pair<int, int>> Vpos;
  int fir = 0, sec = 0;
  for (const auto &POS : positions) {
    fir = POS.second.first + pos.first;
    sec = POS.second.second + pos.second;
    if (themap[fir][sec]->is_valid() &&
       !(themap[fir][sec]->is_DH())) {
      Vpos.emplace_back(fir, sec);
    }
  }
  return Vpos;
}

bool Floor::PlayerIsAround(const pair<int, int> &pos) const {
  int fir = 0, sec = 0;
  for (const auto &POS : positions) {
    fir = POS.second.first + pos.first;
    sec = POS.second.second + pos.second;
    if (themap[fir][sec]->is_player()) {
      return true;
    }
  }
  return false;
}

bool Floor::Attackable(Enemy *which) const {
  pair<int, int> enemyPos = which->getPos();
  string Erace = which->getRace();
  if (which->isDead()) {
    return false;
  }
  if (Erace == "dragon") {
    pair<int, int> DHPOS = which->DHpos();
    return PlayerIsAround(enemyPos) || PlayerIsAround(DHPOS);
  }
  bool result = (Erace == "merchant") ? 
                (PlayerIsAround(enemyPos) && which->ishostile()) :
                PlayerIsAround(enemyPos);
  return result;
}

Enemy *Floor::which_enemy(const pair<int, int> &pos) const {
  Enemy *enemy = nullptr;
  for (const auto &e : enemies) {
    if (pos == e->getPos() && !(e->isDead())) enemy = e;
  }
  return enemy;
}

Item *Floor::which_item(const pair<int, int> &pos) const {
  Item *item = nullptr;
  for (const auto &i : items) {
    if (pos == i->getPos()) item = i;
  }
  return item;
}

void Floor::got_win() {
  win = true;
}

bool Floor::is_win() {
  return win;
}

void Floor::showStat() {
  for (const auto &row : themap) {
    for (const auto &cell : row) {
      cout << *cell;
    }
    cout << endl;
  }
  string msg = "Race: " + player->getRace() + " Gold: " + to_string(player->getGold());
  cout << setw(69) << left << msg;
  cout << "Floor " << floorNum << endl;
  cout << "HP: " << player->getHP() << endl;
  cout << "Atk: " << player->getATK() << endl;
  cout << "Def: " << player->getDEF() << endl;
  cout << "Action: " << action_msg << endl;
}

bool Floor::has_it(const string &type, pair<int, int> &pos) {
  int i = 0;
  int j = 0;
  for (const auto &row : themap) {
    for (const auto &col : row) {
      if ((type == "PC" && col->is_player()) ||
          (type == "stair" && col->is_stair())) {
        pos = make_pair(i, j);
        return true;
      }
      j++;
    }
    i++;
    j = 0;
  }
  return false;
}

void Floor::generatePC(const string &msg) {
  delete player;
  pair<int, int> pos;
  pair<int, int> stair_pos;
  if (has_it("stair", stair_pos)) {
    stairChamber = which_chamber(stair_pos);
  }
  if (!has_it("PC", pos)) {
    vector<int> validChambers;
    for (int i = 0; i < 5; ++i) {
      if (i == stairChamber) {
        continue;
      }
      validChambers.emplace_back(i);
    }
    int chamber_num = validChambers[rand() % validChambers.size()];
    spawnedChamber = chamber_num;
    int count = valid_count(chamber_num);
    int index = rand() % count;
    pos = valid_pos(index, chamber_num);
  } else {
    spawnedChamber = which_chamber(pos);
  }
  string race;
  string line;
  istringstream iss;
  while (true) {
    try {
      cout << msg << endl;
      getline(cin, line);
      iss.str(line);
      player = (iss >> race) ? generator.createPC(pos, line) : generator.createPC(pos);
      break;
    } 
    catch (const runtime_error &error) {
      cerr << error.what() << endl;
      iss.clear();
    }
  }
  int row = pos.first;
  int col = pos.second;
  themap[row][col]->set_content('@');
  player->setPos(pos);
  action_msg = "Player character has spawned.";
}

void Floor::show_interface(const string &file) const {
  ifstream ifs{file};
  int count = 0, y = 0, x = 0;
  string line;
  clear();
  while (getline(ifs, line)) {
    for (const char &c : line) {
      if (c != ' ') {
        if (count < 9) {
          attron(A_BOLD | A_BLINK | COLOR_PAIR(4));
          mvprintw(y, x, "%c", c);
          attroff(A_BOLD | A_BLINK | COLOR_PAIR(4));
        } else if (count == 10 || count == 21) {
          if (x >= 40 && x < 70)  {
            attron(COLOR_PAIR(1));
            mvprintw(y, x, "%c", c);
            attroff(COLOR_PAIR(1));
          } else if (c == '+' || c == '-' || c == '|') {
            attron(A_DIM | COLOR_PAIR(6));
            mvprintw(y, x, "%c", c);
            attroff(A_DIM | COLOR_PAIR(6));
          } else {
            mvprintw(y, x, "%c", c);
          }
        } else if (c > 48 && c < 58) {
          attron(COLOR_PAIR(5));
          mvprintw(y, x, "%c", c);
          attroff(COLOR_PAIR(5));
        } else if (count == 9 || count == 24) {
          attron(A_DIM | COLOR_PAIR(6));
          mvprintw(y, x, "%c", c);
          attroff(A_DIM | COLOR_PAIR(6));
        }
        else if (c == '|') {
          attron(A_DIM | COLOR_PAIR(6));
          mvprintw(y, x, "%c", c);
          attroff(A_DIM | COLOR_PAIR(6));
        } 
        else {
          mvprintw(y, x, "%c", c);
        }
      } else {
        mvprintw(y, x, "%c", c);
      }
      x++;
    }
    count++;
    y++;
    x = 0;
  }
  refresh();
}

void Floor::generate_PC(const string &file) {
  delete player;
  int ch;
  pair<int, int> pos;
  pair<int, int> stair_pos;
  if (has_it("stair", stair_pos)) {
    stairChamber = which_chamber(stair_pos);
  }
  if (!has_it("PC", pos)) {
    vector<int> validChambers;
    for (int i = 0; i < 5; ++i) {
      if (i == stairChamber) {
        continue;
      }
      validChambers.emplace_back(i);
    }
    int chamber_num = validChambers[rand() % validChambers.size()];
    spawnedChamber = chamber_num;
    int count = valid_count(chamber_num);
    int index = rand() % count;
    pos = valid_pos(index, chamber_num);
  } else {
    spawnedChamber = which_chamber(pos);
  }
  ostringstream oss;
  bool finish = false;
  show_interface(file);
  while (!finish && (ch = getch())) {
    switch (ch) {
      case 'd':
      case 's':
      case 'v':
      case 't':
      case 'g':
        player = generator.createPC(pos, string(1, ch));
        finish = true;
        break;
      default:
        player = generator.createPC(pos);
        finish = true;
        break;
    }
  }
  int row = pos.first;
  int col = pos.second;
  themap[row][col]->set_content('@');
  player->setPos(pos);
  action_msg = "Player character has spawned.";
}

void Floor::generateStair() {
  pair<int, int> pos;
  if (!has_it("stair", pos)) {
    vector<int> validChambers;
    for (int i = 0; i < 5; ++i) {
      if (i == spawnedChamber) {
        continue;
      }
      validChambers.emplace_back(i);
    }
    int chamber_num = validChambers[rand() % validChambers.size()];
    int count = valid_count(chamber_num);
    int index = rand() % count;
    pos = valid_pos(index, chamber_num);
  }
  int row = pos.first;
  int col = pos.second;
  themap[row][col]->set_content('\\');
}

void Floor::generateItems() {
  if (is_newmap) {
    int ind;
    int i = 0;
    int j = 0;
    for (const auto &row : themap) {
      for (const auto &col : row) {
        ind = col->what_content() - '0';
        if (ind >= 0 && ind <= 5) {
          items.push_back(generator.createItem(make_pair(i, j), given_type[ind]));
          themap[i][j]->set_content('P');
        } else if (ind >= 6 && ind <= 9) {
          items.push_back(generator.createItem(make_pair(i, j), given_type[ind]));
          if (given_type[ind] == "DH") {
            themap[i][j]->set_content('.');
            themap[i][j]->setDH();
          } else {
            themap[i][j]->set_content('G');
          }
        } 
        ++j;
      }
      ++i;
      j = 0;
    }
  } else {
    int chamber_num = 0;
    int type = 0;
    int index = 0;
    int validNum = 0;
    pair<int, int> pos;
    for (int i = 0; i < 10; i++) {
      chamber_num = rand() % 5;
      validNum = valid_count(chamber_num);
      while (validNum == 0) {
        chamber_num = rand() % 5;
        validNum = valid_count(chamber_num);
      }
      type = rand() % 6;
      index = rand() % validNum;
      pos = valid_pos(index, chamber_num);
      items.push_back(generator.createItem(pos, por_types[type]));
      themap[pos.first][pos.second]->set_content('P');
    }
    validNum = 0;
    for (int i = 0; i < 10; i++) {
      chamber_num = rand() % 5;
      validNum = valid_count(chamber_num);
      while (validNum == 0) {
        chamber_num = rand() % 5;
        validNum = valid_count(chamber_num);
      }
      type = rand() % 8;
      index = rand() % validNum;
      pos = valid_pos(index, chamber_num);
      items.push_back(generator.createItem(pos, gold_types[type]));
      if (gold_types[type] != "DH") {
        themap[pos.first][pos.second]->set_content('G');
      } else {
        themap[pos.first][pos.second]->setDH();
      }
    }
  }
}

vector<pair<int, int>> Floor::getDHpos() const {
  vector<pair<int, int>> pos;
  for (const auto &item : items) {
    if (item->getType() == "DH") {
      pos.emplace_back(item->getPos());
    }
  }
  return pos;
}

bool Floor::searchDH(pair<int, int> &pos, const vector<pair<int, int>> &DHpos) {
  int fir = 0, sec = 0;
  for (const auto &pair : order_pos) {
    fir = pair.first + pos.first;
    sec = pair.second + pos.second;
    if (themap[fir][sec]->is_DH()) {
      auto it = find(DHpos.begin(), DHpos.end(), make_pair(fir, sec));
      if (it != DHpos.end()) {
        pos = make_pair(fir, sec);
        return true;
      }
    }
  }
  return false;
}

void Floor::generateDragons() {
  vector<pair<int, int>> DHpos = getDHpos();
  vector<pair<int, int>> valid_dhpos;
  pair<int, int> dragonpos;
  pair<int, int> hoardpos;
  int valid_size = 0;
  int index = 0;
  if (is_newmap) {
    int i = 0;
    int j = 0;
    for (const auto &row : themap) {
      for (const auto &col : row) {
        if (col->what_content() == 'D') {
          dragonpos = make_pair(i, j);
          if (searchDH(dragonpos, DHpos)) {
            enemies.push_back(generator.createDragon(make_pair(i, j), dragonpos));
            auto it = find(DHpos.begin(), DHpos.end(), dragonpos);
            if (it != DHpos.end()) DHpos.erase(it);
          }
        }
        ++j;
      }
      ++i;
      j = 0;
    }
    for (const auto &pos : DHpos) {
      themap[pos.first][pos.second]->set_content('G');
      themap[pos.first][pos.second]->setDH();
    }
  } else {
    for (const auto &pos : DHpos) {
      valid_dhpos = validPosNear(pos);
      valid_size = valid_dhpos.size();
      if (valid_size == 0) {
        enemies.push_back(generator.createDragon(pos, pos));
        themap[pos.first][pos.second]->set_content('D');
        continue;
      } else {
        index = rand() % valid_size;
        dragonpos = valid_dhpos[index];
        enemies.push_back(generator.createDragon(dragonpos, pos));
        themap[dragonpos.first][dragonpos.second]->set_content('D');
      }
    }
  }
}

void Floor::generateEnemy() {
  if (is_newmap) {
    int i = 0;
    int j = 0;
    pair<int, int> pos;
    string type;
    for (const auto &row : themap) {
      for (const auto &col : row) {
        if (col->is_smallenemy()) {
          pos = make_pair(i, j);
          type = string(1, col->what_content());
          enemies.push_back(generator.createEnemy(pos, type));
        }
        ++j;
      }
      ++i;
      j = 0;
    }
  } else {
    int chamber_num = 0;
    int type = 0;
    int index = 0;
    int validNum = 0;
    pair<int, int> pos;
    char what;
    for (int i = 0; i < 20; i++) {
      chamber_num = rand() % 5;
      validNum = valid_count(chamber_num);
      while (validNum == 0) {
        chamber_num = rand() % 5;
        validNum = valid_count(chamber_num);
      }
      type = rand() % 18;
      index = rand() % validNum;
      pos = valid_pos(index, chamber_num);
      enemies.push_back(generator.createEnemy(pos, enemy_types[type]));
      what = enemy_types[type][0];
      themap[pos.first][pos.second]->set_content(what);
    }
  }
}

void Floor::update_floor() {
  ifstream originalMap{"./txtFiles/cc3k-emptySingleFloor.txt"};
  string stringLine;
  int row = 0;
  int col = 0;
  if (is_newmap) {
    bool start = false;
    int count = 0;
    while (count < 25 && getline(InputMap, stringLine)) {
      if (!start) {
        if (stringLine.empty()) continue;
        else start = true; 
      }
      for (const char &c : stringLine) {
        themap[row][col++]->set_content(c);
      }
      row++;
      col = 0;
      count++;
    }
  } else {
    while (getline(originalMap, stringLine)) {
      for (const char &c : stringLine) {
        themap[row][col++]->set_content(c);
      }
      row++;
      col = 0;
    }
  }
}

void Floor::update_player(const pair<int, int> &pos) {
  int row = pos.first;
  int col = pos.second;
  int hp = player->getHP();
  int amt = player->getGold();
  char theRace = tolower(player->getRace()[0]);
  vector<string> bag_items = player->get_bag();
  delete player;
  player = generator.createPC(pos, string(1, theRace));
  spawnedChamber = which_chamber(pos);
  player->setHP(hp);
  player->addGold(amt);
  themap[row][col]->set_content('@');
  player->setPos(pos);
  for (const string &s : bag_items) {
    player->store_item(s);
  }
}

void Floor::reset_DH() {
  for (const auto &row : themap) {
    for (const auto &col : row) {
      if (col->is_DH()) col->setDH();
    }
  }
}

void Floor::update_items() {
  reset_DH();
  for (auto i : items) delete i;
  items.clear();
  generateItems();
}

void Floor::update_enemies() {
  for (auto enemy : enemies) delete enemy;
  enemies.clear();
  generateDragons();
  generateEnemy();
  if (mer_atked) {
    setAllMerchantHostile();
  }
}

void Floor::move_pc(const string &dir) {
  VALIDMOVED = true;
  pair<int, int> pos = player->getPos();
  pair<int, int> new_pos = positions.at(dir);
  new_pos.first += pos.first;
  new_pos.second += pos.second;
  action_msg = "Player is moved one block to " + dir + ". ";
  if (themap[new_pos.first][new_pos.second]->is_valid()) {
    player->setPos(new_pos);
    if (themap[pos.first][pos.second]->is_Door()) {
      themap[pos.first][pos.second]->set_content('+');
    } else {
      themap[pos.first][pos.second]->set_content('.');
    }
    themap[new_pos.first][new_pos.second]->set_content('@');
  } else if (themap[new_pos.first][new_pos.second]->is_Door()) {
    player->setPos(new_pos);
    if (themap[pos.first][pos.second]->is_Passage()) {
      themap[pos.first][pos.second]->set_content('#');
    } else {
      themap[pos.first][pos.second]->set_content('.');
    }
    themap[new_pos.first][new_pos.second]->set_content('@');
  } else if (themap[new_pos.first][new_pos.second]->is_Passage()) {
    player->setPos(new_pos);
    if (themap[pos.first][pos.second]->is_Door()) {
      themap[pos.first][pos.second]->set_content('+');
    } else {
      themap[pos.first][pos.second]->set_content('#');
    }
    themap[new_pos.first][new_pos.second]->set_content('@');
  } else if (themap[new_pos.first][new_pos.second]->is_stair()) {
    floorNum++;
    if (floorNum == 6) {
      got_win();
      return;
    }
    update_floor();
    has_it("PC", new_pos);
    update_player(new_pos);
    generateStair();
    update_items();
    update_enemies();
    action_msg = "Player is moved to floor " + to_string(floorNum) + ". ";
  } else if (themap[new_pos.first][new_pos.second]->is_gold()) {
    int amt = which_item(new_pos)->getGold();
    string type = which_item(new_pos)->getType();
    player->addGold(amt);
    player->setPos(new_pos);
    if (themap[pos.first][pos.second]->is_Door()) {
      themap[pos.first][pos.second]->set_content('+');
    } else {
      themap[pos.first][pos.second]->set_content('.');
    }
    themap[new_pos.first][new_pos.second]->set_content('@');
    action_msg = "Player picked up a gold " + type + ". ";
  } else {
    VALIDMOVED = false;
    action_msg = "Invalid movement.";
  }
}

void Floor::buy(const string &dir) {
  pair<int, int> pos = player->getPos();
  pair<int, int> new_pos = positions.at(dir);
  new_pos.first += pos.first;
  new_pos.second += pos.second;
  vector<string> bag = player->get_bag();
  if (themap[new_pos.first][new_pos.second]->what_content() == 'M') {
    Enemy *merchant = which_enemy(new_pos);
    if (!(merchant->ishostile())) {
      if (merchant->has_item()) {
        if (bag.size() == 4) {
          action_msg = "Your bag is full";
          return;
        }
        bool finished = false;
        char ch;
        clear();
        string msg = merchant->get_shopmsg() + '\n' + "Your gold amt: " + to_string(player->getGold());
        mvprintw(0, 0, "%s", msg.c_str());
        // refresh();
        while (!finished && (ch = getch())) {
          switch (ch) {
            case '1':
            case '2':
            case '3':
            case '4':
              if (ch - '0' > merchant->bag_size()) {
                break;
              } else {
                pair<string, int> item = merchant->get_item(ch - '1');
                if (player->getGold() < item.second) break;
                else {
                  merchant->consume(ch - '1');
                  action_msg = "You spend " + to_string(item.second) + " Gold to buy a " + item.first;
                  finished = true;
                  player->addGold(-item.second);
                  player->store_item(item.first);
                }
              }
            case 'q':
              finished = true;
          }
        }
        refresh();
      } else {
        action_msg = "Sold Out";
      }
    }
  } else {
    action_msg = "There's no merchant at " + dir;
  }
}

void Floor::show_bag() {
  vector<string> bag = player->get_bag();
  if (bag.size() == 0) {
    action_msg = "There's no items in bag";
    return ;
  }
  bool finished = false;
  char ch;
  clear();
  mvprintw(0, 0, "%s", player->get_bagmsg().c_str());
  refresh();
  while (!finished && (ch = getch())) {
    switch (ch) {
      case '1':
      case '2':
      case '3':
      case '4':
        if (long unsigned int size = ch - '0'; size > bag.size()) {
          break;
        } else {
          int ind = ch - '1';
          player->consume(ind);
          Item * i = generator.createItem(make_pair(0, 0), bag[ind]);
          items.push_back(i);
          player = new Effects{player, bag[ind]};
          action_msg = "You used a potion " + bag[ind];
          finished = true;
        }
      case 'q':
        finished = true;
    }
  }
}

void Floor::usePotion(const string &dir) {
  pair<int, int> pos = player->getPos();
  pair<int, int> potion_pos = positions.at(dir);
  potion_pos.first += pos.first;
  potion_pos.second += pos.second;
  if (which_item(potion_pos) && which_item(potion_pos)->isValid() && 
      !(themap[potion_pos.first][potion_pos.second]->is_gold())) {
    which_item(potion_pos)->invalidate();
    string Type = which_item(potion_pos)->getType();
    player = new Effects{player, Type};
    action_msg = "Player uses " + Type + player->getEffect() + ". ";
    themap[potion_pos.first][potion_pos.second]->set_content('.');
  } else {
    action_msg = "No potion at " + dir + ". ";
    VALIDMOVED = false;
  }
}

void Floor::attack(const string &dir) {
  pair<int, int> pos = player->getPos();
  pair<int, int> enemy_pos = positions.at(dir);
  pair<int, int> dhpos;
  string msg = "";
  enemy_pos.first += pos.first;
  enemy_pos.second += pos.second;
  Enemy *tmp = which_enemy(enemy_pos);
  if (tmp && !tmp->isDead()) {
    string Erace = tmp->getRace();
    if (Erace == "merchant") {
      mer_atked = true;
      setAllMerchantHostile();
    }
    if (Erace == "dragon") {
      dhpos = tmp->DHpos();
    }
    int Egold = tmp->getGold();
    player->attack(tmp);
    action_msg = player->getmsg();
    if (!which_enemy(enemy_pos)) {
      if (Erace == "dwarf") {
        action_msg += "W";
      } else if (Erace == "halfling") {
        action_msg += "L";
      } else {
        action_msg += string(1, Erace[0] - ('a' - 'A'));
      }
      action_msg += " died. ";
      if (player->getRace() == "Goblin") {
        player->addGold(5);
        action_msg += "PC steals 5 Gold. ";
      }
      if (Erace != "human" && Erace != "dragon") {
        if (Erace == "merchant") {
          items.push_back(generator.createItem(enemy_pos, "MH"));
        } else {
          if (Egold == 1) {
            items.push_back(generator.createItem(enemy_pos, "SP"));
          } else {
            items.push_back(generator.createItem(enemy_pos, "NP"));
          }
        }
        themap[enemy_pos.first][enemy_pos.second]->set_content('G');
      } else {
        if (Erace == "human") {
          items.push_back(generator.createItem(enemy_pos, "NP"));
          themap[enemy_pos.first][enemy_pos.second]->set_content('G');
          vector<pair<int, int>> poses = validPosNear(enemy_pos);
          int size_poses = poses.size();
          if (size_poses != 0) {
            int index = rand() % size_poses;
            items.push_back(generator.createItem(poses[index], "NP"));
            themap[poses[index].first][poses[index].second]->set_content('G');
          } else {
            player->addGold(2);
            action_msg += "PC gains 1 NP from H. ";
          }
        } else {
          if (dhpos == player->getPos()) {
            player->addGold(6);
            action_msg += "PC(right on DH pos) gains 6 gold. ";
          } else {
            themap[dhpos.first][dhpos.second]->set_content('G');
            action_msg += "DH pos shows up. ";
          }
          themap[dhpos.first][dhpos.second]->setDH();
          themap[enemy_pos.first][enemy_pos.second]->set_content('.');
        }
      }
    }
    VALIDMOVED = true;
  } else {
    action_msg = "There's no enemy at " + dir + ". ";
    VALIDMOVED = false;
  }
}

void Floor::TrollFeature() {
  if (player->getRace() == "Troll") {
    int initial = player->get_initialHP();

    int result = 0;
    if ((player->getHP() + 5) >= 120) {
      result = 120 - player->getHP() + initial;
    } else {
      result = 5 + initial;
    }
    if ((result - initial) > 0) {
      action_msg += "Inherent: restore " + 
                    to_string(result - initial) + " HP. ";
    }
    player->setHP(result);
  }
}

void Floor::Eact() {
  int i = 0, j = 0;
  if (frozen) {
    return ;
  }
  if (!VALIDMOVED) {
    return;
  }
  Enemy *enemy = nullptr;
  for (auto &n : themap) {
    if (player->isDead()) {
      break;
    }
    for (auto &m : n) {
      if (m->is_enemy()) {
        enemy = which_enemy(make_pair(i, j));
        if (!enemy->HasActed()) {
          if (Attackable(enemy)) {
            enemy->attack(player);
            action_msg += enemy->getMSG();
            if (player->isDead()) {
              action_msg += "PC dies, You LOSE!";
              break;
            }
          } else {
            if (enemy->getRace() == "dragon") {
              enemy->setActed();
              j++;
              continue;
            }
            vector<pair<int, int>> Vpos = validPosNear(make_pair(i, j));
            int Vsize = Vpos.size();
            if (Vsize == 0) {
            } else {
              char what = m->what_content();
              pair<int, int> Epos = Vpos[rand() % Vsize];
              enemy->setPos(Epos);
              m->set_content('.');
              themap[Epos.first][Epos.second]->set_content(what);
            }
          }
          enemy->setActed();
        }
      }
      j++;
    }
    i++;
    j = 0;
  }
}

void Floor::resetActed() {
  for (const auto &enemy : enemies) {
    if ((!enemy->isDead())) {
      enemy->unsetActed();
    }
  }
}

void Floor::setAllMerchantHostile() {
  for (const auto &M : enemies) {
    if (M->getRace() == "merchant") {
      if (!M->ishostile()) {
        M->sethostile();
      }
    }
  }
}

bool Floor::PCdies() const {
  return player->isDead();
}

void Floor::now_stat() {
  ostringstream oss;
  string initial;
  string msg;
  char ch;
  int y = 0, x = 0;
  clear();
  for (const auto &n : themap) {
    for (const auto &m : n) {
      ch = m->what_content();
      if (m->is_enemy()) {
        attron(COLOR_PAIR(1));
      } else if (m->is_potion()) {
        attron(COLOR_PAIR(2));
      } else if (m->is_gold()) {
        attron(COLOR_PAIR(3));
      } else if (m->is_player() || m->is_stair()) {
        attron(A_BOLD | COLOR_PAIR(4));
      }
      mvprintw(y, x, "%c", ch);
      if (m->is_enemy()) {
        attroff(COLOR_PAIR(1));
      } else if (m->is_potion()) {
        attroff(COLOR_PAIR(2));
      } else if (m->is_gold()) {
        attroff(COLOR_PAIR(3));
      } else if (m->is_player() || m->is_stair()) {
        attroff(A_BOLD | COLOR_PAIR(4));
      }
      x++;
    }
    y++;
    x = 0;
  }
  msg = "Race: " + player->getRace() + " Gold: " + to_string(player->getGold());
  oss << setw(69) << left << msg;
  oss << "Floor " << floorNum << endl;
  initial += oss.str();
  initial += "HP: " + to_string(player->getHP()) + '\n';
  initial += "Atk: " + to_string(player->getATK()) + '\n';
  initial += "Def: " + to_string(player->getDEF()) + '\n';
  initial += "Action: " + action_msg + '\n';
  mvprintw(y, 0, "%s", initial.c_str());
  refresh();
}
