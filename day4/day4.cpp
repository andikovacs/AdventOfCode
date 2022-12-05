#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

void get_pair(const std::string& s, long& n1, long& n2) {
  auto cursor = s.find_first_of("-");
  n1 = stoi(s.substr(0, cursor));
  n2 = stoi(s.substr(cursor + 1, s.size()));
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  std::string line;
  unsigned long count = 0;
  unsigned long overlaps = 0;
  if (input.is_open()) {
    while (getline(input, line)) {
      auto sep = line.find_first_of(",");
      std::string str1 = line.substr(0, sep);
      std::string str2 = line.substr(sep + 1, line.size());
      long p11, p12, p21, p22;
      get_pair(str1, p11, p12);
      get_pair(str2, p21, p22);

      std::vector<int> first(p12 - p11 + 1);
      std::generate(begin(first), end(first),
                    [el = p11]() mutable { return el++; });

      std::vector<int> second(p22 - p21 + 1);
      std::generate(begin(second), end(second),
                    [el = p21]() mutable { return el++; });

      if (std::includes(begin(first), end(first), begin(second), end(second)) ||
          std::includes(begin(second), end(second), begin(first), end(first))) {
        count++;
      }

      auto it = std::find_first_of(begin(first), end(first), begin(second),
                                   end(second));
      if (it != end(first)) {
        overlaps++;
      }
    }
    std::cout << count << std::endl;
    std::cout << overlaps << std::endl;

    return 0;
  }
}
