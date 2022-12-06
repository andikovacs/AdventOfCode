#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::ifstream input;
  input.open("input.txt");
  std::string line;
  const int seq_len = 14;

  if (input.is_open()) {
    char ch;
    unsigned long count = 0;
    std::string seq;
    std::fstream fin("input.txt", std::fstream::in);
    while (fin >> ch) {
      count++;
      seq.push_back(ch);
      if (count > seq_len - 1) {
        // std::cout << seq << " " << count << std::endl;
        int i;
        for (i = 0; i < seq_len; i++) {
          auto n = std::count(seq.begin(), seq.end(), seq[i]);
          if (n > 1) {
            break;
          }
        }
        if (i == seq_len) {
          std::cout << count << std::endl;
          return 0;
        }
        seq.erase(0, 1);
      }
    }
  }
  return 0;
}