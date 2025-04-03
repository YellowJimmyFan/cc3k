#include <vector>
#include <string>
#include <set>
#include <time.h>
#include <ncurses.h>
#include <cctype>
#include "helpers.h"

using namespace std;

const set<string> dir_set = {"no", "so", "we", "ea", "ne", "nw", "se", "sw"};

int main(int argc, char *argv[]) {
  ifstream gameoverifs{"./txtFiles/gameover.txt"};
  ifstream chooseifs{"./txtFiles/choose.txt"};
  ifstream startifs{"./txtFiles/start.txt"};
  ifstream overifs{"./txtFiles/over.txt"};
  ifstream deadifs{"./txtFiles/died.txt"};
  ifstream winifs{"./txtFiles/win.txt"};
  string gameovermsg = get_str(gameoverifs);
  string choosemsg = get_str(chooseifs);
  string startmsg = get_str(startifs);
  string deadmsg = get_str(deadifs);
  string overmsg = get_str(overifs);
  string winmsg = get_str(winifs);
  string choosefile = "./txtFiles/choose.txt";
  bool quick_movement_mode = false;
  bool PlayAgain = true;
  int seed = time(0);
  int count1 = 0;
  int count = 0;
  vector<string> argments;  
  string mapname;
  if (argc > 4) {
    cerr << "invalid command" << endl;
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    string s = argv[i];
    argments.push_back(s);
  }
  for (const auto &s : argments) {
    if (s == "screen") {
      quick_movement_mode = true;
    } else if (s == "reset") {
      reset_record("./txtFiles/record.txt");
    } else if (is_digit(s)) {
      if (count1 > 0) {
        cerr << "invalid command" << endl;
        return 0;
      }
      seed = stoi(s);
      count1++;
    } else {
      if (count > 0) {
        cerr << "invalid command" << endl;
        return 0;
      }
      mapname = s;
      count++;
    }
  }
  if (!ifstream{mapname}.is_open()) {
    mapname = "./txtFiles/cc3k-emptySingleFloor.txt";
  }
  srand(seed);
  while (PlayAgain) {
    Floor f{1, mapname};
    PlayAgain = false;
    string line;
    string dir;
    if (!quick_movement_mode) {
      f.generatePC(startmsg);
      f.generateStair();
      f.generateItems();
      f.generateDragons();
      f.generateEnemy();
    }
    if (quick_movement_mode) {
      time_t start_time, current_time;
      double duration_seconds;
      bool gameover = false;
      bool second = false;
      bool is_use = false;
      bool is_attack = false;
      int ch;
      initscr();
      cbreak();
      noecho();
      keypad(stdscr, TRUE);
      curs_set(0);

      start_color();
      init_pair(1, COLOR_RED, COLOR_BLACK);
      init_pair(2, COLOR_GREEN, COLOR_BLACK);
      init_pair(3, COLOR_YELLOW, COLOR_BLACK);
      init_pair(4, COLOR_BLUE, COLOR_BLACK);
      init_pair(5, COLOR_CYAN, COLOR_BLACK);
      init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

      f.generate_PC(choosefile);
      f.generateStair();
      f.generateItems();
      f.generateDragons();
      f.generateEnemy();

      f.now_stat();
      while (!f.PCdies() && (ch = getch())) {
        clear();
        current_time = time(NULL);
        duration_seconds = (double)(current_time - start_time);
        if (second && duration_seconds <= 1) {
          switch (ch) {
            case 'w':
            case 's':
            case 'a':
            case 'd':
            case 't':
            case 'y':
            case 'g':
            case 'h':
              if (is_use) use(f, commands.at(ch));
              else if (is_attack) attack(f, commands.at(ch));
              else {f.buy(commands.at(ch)); f.now_stat();}
              break;
            case KEY_UP:
              if (is_use) use(f, "no");
              else if (is_attack) attack(f, "no");
              else {f.buy("no"); f.now_stat();}
              break;
            case KEY_DOWN:
              if (is_use) use(f, "so");
              else if (is_attack) attack(f, "so");
              else {f.buy("so"); f.now_stat();}
              break;
            case KEY_LEFT:
              if (is_use) use(f, "we");
              else if (is_attack) attack(f, "we");
              else {f.buy("we"); f.now_stat();}
              break;
            case KEY_RIGHT:
              if (is_use) use(f, "ea");
              else if (is_attack) attack(f, "ea");
              else {f.buy("ea"); f.now_stat();}
              break;
            default:
              f.now_stat();
              break;
          }
          second = false;
          is_use = false;
          is_attack = false;
        } else if (ch == 'j') {
          f.now_stat();
          second = true;
          is_attack = true;
          start_time = time(NULL);
        } else if (ch == 'k') {
          f.now_stat();
          second = true;
          is_use = true;
          start_time = time(NULL);
        } else if (ch == 'l') {
          f.now_stat();
          second = true;
          start_time = time(NULL);
        } else {
          switch (ch) {
            case 'w':
            case 's':
            case 'a':
            case 'd':
            case 't':
            case 'y':
            case 'g':
            case 'h':
              move(f, PlayAgain, commands.at(ch));
              break;
            case KEY_UP:
              move(f, PlayAgain, "no");
              break;
            case KEY_DOWN:
              move(f, PlayAgain, "so");
              break;
            case KEY_LEFT:
              move(f, PlayAgain, "we");
              break;
            case KEY_RIGHT:
              move(f, PlayAgain, "ea");
              break;
            case 'f':
              f.freezeORunfreeze();
              f.now_stat();
              break;
            case 'r':
              PlayAgain = true;
              break;
            case 'q':
              gameover = true;
              break;
            case 'u':
              f.show_bag();
              f.now_stat();
              break;
            default:
              f.now_stat();
              break;
          }
          second = false;
        }
        refresh();
        if (PlayAgain || gameover || f.is_win()) break;
      }
      if (f.PCdies()) {
        bool finish = false;
        clear();
        mvprintw(0, 0, "%s", deadmsg.c_str());
        refresh();
        while (!finish && (ch = getch())) {
          switch (ch) {
            case 'r':
              PlayAgain = true;
              finish = true;
              break;
            case 'q':
              finish = true;
              break;
            default:
              break;
          }
        }
      }
      if (gameover) {
        clear();
        mvprintw(0, 0, "%s", overmsg.c_str());
        refresh();
        if ((ch = getch())) {
          switch (ch) {
            default:
              break;
          }
        }
      }
      if (f.is_win()) {
        ostringstream oss;
        int cur = f.get_Score();
        int record;
        string line;
        ifstream ifs{"./txtFiles/record.txt"};
        getline(ifs, line);
        istringstream iss{line};
        iss >> record;
        ifs.close();
        oss << setw(53) << right << "|      Your Score: ";
        oss << setw(10) << left << cur << '|' << endl;
        ofstream ofs{"./txtFiles/record.txt"};
        if (cur > record) {
          oss << setw(53) << right << "|      New Record: ";
          oss << setw(10) << left << cur << '|' << endl;
          ofs << cur << endl;
        } else {
          oss << setw(55) << right << "|     Highest Score: ";
          oss << setw(8) << left << record << '|' << endl;
          ofs << record << endl;
        }
        oss << setw(64) << right << "|  Press any button to Quit  |" << endl;
        oss << setw(64) << right << "+----------------------------+" << endl;
        clear();
        mvprintw(18, 20, "%s", (winmsg + oss.str()).c_str());
        refresh();
        if ((ch = getch())) {
          switch (ch) {
            default:
              break;
          }
        }
      }
      endwin();
    } else {
      f.showStat();
      while (getline(cin, line)) {
        if (line.length() == 2 && dir_set.find(line) != dir_set.end()) {
          f.move_pc(line);
          if (f.is_moved()) f.TrollFeature();
          f.Eact();
          f.showStat();
          if (f.PCdies()) {
            cout << deadmsg;
            getline(cin, line);
            while((line != "r") && (line != "q")) {
              getline(cin, line);
              cout << "Invalid Command! Press again." << endl;
            }
            PlayAgain = (line == "r") ? true : false;
            break;
          } else {
            f.resetActed();
          }
        } else if (line == "q") {
          cout << gameovermsg;
          break;
        } else if (line[0] == 'u') {
          if (line.length() < 2 || line[1] != ' ') {
            cout << "Invalid command" << endl;
            continue;
          }
          istringstream iss{line.substr(2)};
          string s;
          if (iss >> dir && !(iss >> s) && dir_set.find(dir) != dir_set.end()) {
            f.usePotion(dir);
            if (f.is_moved()) f.TrollFeature();
            f.Eact();
            f.showStat();
            if (f.PCdies()) {
              cout << "Press r to restart, or q to Quit." << endl;
              getline(cin, line);
              while((line != "r") && (line != "q")) {
                getline(cin, line);
                cout << "Invalid Command! Press again." << endl;
              }
              PlayAgain = (line == "r") ? true : false;
              break;
            } else {
              f.resetActed();
            }
          } else {
            cout << "Invalid direction: " << dir << endl;
          }
        } else if (line[0] == 'a') {
          if (line.length() < 2 || line[1] != ' ') {
            cout << "Invalid command" << endl;
            continue;
          }
          istringstream iss{line.substr(2)};
          string s;
          if (iss >> dir && !(iss >> s) && dir_set.find(dir) != dir_set.end()) {
            f.attack(dir);
            if (f.is_moved()) f.TrollFeature();
            f.Eact();
            f.showStat();
            if (f.PCdies()) {
              cout << deadmsg;
              getline(cin, line);
              while((line != "r") && (line != "q")) {
                getline(cin, line);
                cout << "Invalid Command! Press again." << endl;
              }
              PlayAgain = (line == "r") ? true : false;
              break;
            } else {
              f.resetActed();
            }
          } else {
            cout << "Invalid direction: " << dir << endl;
          }
        } else if (line == "f") {
          f.freezeORunfreeze();
        } else if (line == "r") {
          PlayAgain = true;
          break;
        } else {
          cerr << "Invalid command" << endl;
        }
        if (f.is_win()) {
          ostringstream oss;
          int cur = f.get_Score();
          int record;
          string line;
          ifstream ifs{"./txtFiles/record.txt"};
          getline(ifs, line);
          istringstream iss{line};
          iss >> record;
          ifs.close();
          oss << setw(53) << right << "|      Your Score: ";
          oss << setw(10) << left << cur << '|' << endl;
          ofstream ofs{"./txtFiles/record.txt"};
          if (cur > record) {
            oss << setw(53) << right << "|      New Record: ";
            oss << setw(10) << left << cur << '|' << endl;
            ofs << cur << endl;
          } else {
            oss << setw(55) << right << "|     Highest Score: ";
            oss << setw(8) << left << record << '|' << endl;
            ofs << record << endl;
          }
          oss << setw(64) << right << "+----------------------------+" << endl;
          cout << winmsg << oss.str();
          break;
        }
      }
    }
  }
}
