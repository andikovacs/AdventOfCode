#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

long fAdd(long op1, long op2) {
  if (op2 == 0xffffffff) {
    return op1 + op1;
  }
  return op1 + op2;
}
long fMultiply(long op1, long op2) {
  if (op2 == 0xffffffff) {
    return op1 * op1;
  }
  return op1 * op2;
}

class Item {
 public:
  Item() { worry_level = 0; }
  long worry_level;
};

class Monkey {
 public:
  void initItems(std::string s) {
    std::stringstream ss;
    s = s.substr(18, s.size());
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    ss << s;
    while (!ss.eof()) {
      long x;
      Item item;
      ss >> x;
      item.worry_level = x;
      items.push_back(item);
    }
  }
  void initOperation(std::string s) {
    s = s.substr(23, s.size());
    switch (s[0]) {
      case '+':
        operation = fAdd;
        break;
      case '*':
        operation = fMultiply;
        break;
    }
    s = s.substr(2, s.size());
    if (s == "old") {
      param = 0xffffffff;
    } else {
      param = stoi(s);
    }
  }
  void initDivider(std::string s) { divider = stoi(s.substr(21, s.size())); }
  void initTrueNeighbour(std::string s) {
    true_neighbour = stoi(s.substr(29, s.size()));
  }
  void initFalseNeighbour(std::string s) {
    false_neighbour = stoi(s.substr(30, s.size()));
  }

  void print() {
    std::cout << "Monkey" << std::endl;
    std::cout << "Has items: ";
    for (auto e : items) {
      std::cout << e.worry_level << " ";
    }
    std::cout << std::endl << "Div: " << divider << std::endl;
    std::cout << "Param: " << param << std::endl;
    std::cout << "True n: " << true_neighbour << std::endl;
    std::cout << "False n: " << false_neighbour << std::endl;
    std::cout << "Inspection count: " << inspection_count << std::endl
              << std::endl;
  }

  void inspectItems(long p) {
    for (auto it : items) {
      std::pair<long, long> x;
      x.first = inspectItem(it.worry_level, x.second, p);
      thrown_items.push_back(x);
    }
    items.clear();
  }

  void catchItem(Item item) { items.push_back(item); }

  std::vector<std::pair<long, long>> thrown_items;
  long inspection_count;
  long divider;

 private:
  std::vector<Item> items;
  std::function<long(long, long)> operation;
  long param;
  long true_neighbour;
  long false_neighbour;

  long inspectItem(long old_value, long& new_value, long p) {
    inspection_count++;
    new_value = operation(old_value, param);
    // new_value /= 3;
    new_value %= p;
    if (new_value % divider == 0) {
      return true_neighbour;
    }
    return false_neighbour;
  }
};

bool operator<(Monkey const& m1, Monkey const& m2) {
  return m1.inspection_count < m2.inspection_count;
}

void createMonkey() {}

int main() {
  std::ifstream input;
  input.open("input.txt");
  if (input.is_open()) {
    std::string line;
    long prod = 1;
    std::vector<Monkey> monkeys;
    while (getline(input, line)) {
      if (line.rfind("Monkey ", 0) == 0) {
        Monkey m;
        getline(input, line);
        m.initItems(line);
        getline(input, line);
        m.initOperation(line);
        getline(input, line);
        m.initDivider(line);
        prod *= m.divider;
        getline(input, line);
        m.initTrueNeighbour(line);
        getline(input, line);
        m.initFalseNeighbour(line);
        monkeys.push_back(m);
      }
    }
    for (auto i = 0; i < 10000; i++) {
      for (auto& monkey : monkeys) {
        monkey.inspectItems(prod);
        for (auto el : monkey.thrown_items) {
          Item y;
          y.worry_level = el.second;
          monkeys[el.first].catchItem(y);
        }
        monkey.thrown_items.clear();
      }
    }
    std::sort(begin(monkeys), end(monkeys));
    std::cout << monkeys[monkeys.size() - 1].inspection_count *
                     monkeys[monkeys.size() - 2].inspection_count
              << std::endl;
    return 0;
  }
}