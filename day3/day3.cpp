#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

void add_prios(char ch, unsigned long &s) {
  if (isupper(ch)) {
    s += ch - 'A' + 27;
  } else if (islower(ch)) {
    s += ch - 'a' + 1;
  }
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  std::string line;
  unsigned long sum = 0;
  std::vector<std::string> bags;
  if (input.is_open()) {
    while (getline(input, line)) {
      bags.push_back(line);
      std::string str1 = line.substr(0, line.size() / 2);
      std::string str2 = line.substr(line.size() / 2);
      auto it = str1.find_first_of(str2);
      add_prios(str1[it], sum);
    }
  }

  unsigned long sum1 = 0;
  for (auto i = 0; i < bags.size() - 2; i += 3) {
    for (auto ch : bags[i]) {
      auto it1 = bags[i + 1].find_first_of(ch);
      auto it2 = bags[i + 2].find_first_of(ch);
      if ((it1 < bags[i + 1].size()) && (it2 < bags[i + 2].size())) {
        add_prios(ch, sum1);
        break;
      }
    }
  }
  std::cout << sum << std::endl;
  std::cout << sum1 << std::endl;

  return 0;
}
