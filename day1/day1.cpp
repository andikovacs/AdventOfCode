#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

bool is_number(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  unsigned int val;
  std::string line;
  unsigned long sum = 0;
  unsigned long max_sum = 0;
  unsigned int elf_index = 0;
  unsigned int max_ind = 0;
  std::vector<unsigned int> elfs;

  if (input.is_open()) {
    while (getline(input, line)) {
      if (is_number(line)) {
        std::stringstream ss(line);
        ss >> val;
        // std::cout << val << std::endl;
        sum += val;
        if (sum > max_sum) {
          max_sum = sum;
          max_ind = elf_index;
        }
      } else {
        // std::cout << "New elf" << std::endl;
        elfs.push_back(sum);
        sum = 0;
        elf_index++;
      }
    }
  }
  std::cout << max_sum << std::endl;
  std::cout << max_ind << std::endl;

  std::sort(begin(elfs), end(elfs));
  if (elfs.size() > 3) {
    std::cout << elfs[elfs.size() - 1] + elfs[elfs.size() - 2] +
                     elfs[elfs.size() - 3]
              << std::endl;
  } else {
    std::cout << std::accumulate(elfs.begin(), elfs.end(), 0) << std::endl;
    ;
  }
  return 0;
}
