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

std::size_t replace_all(std::string& inout, std::string what,
                        std::string with) {
  std::size_t count{};
  for (std::string::size_type pos{};
       inout.npos != (pos = inout.find(what.data(), pos, what.length()));
       pos += with.length(), ++count) {
    inout.replace(pos, what.length(), with.data(), with.length());
  }
  return count;
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  std::string line;
  char matrix[50][50];
  std::vector<std::string> vect;

  if (input.is_open()) {
    int matrix_line = 0;
    int matrix_col = 0;
    bool create_matrix = true;
    int lineno = 0;
    int colno = 0;
    while (getline(input, line)) {
      if (line.find("[") != std::string::npos) {
        replace_all(line, "    ", "*");
        replace_all(line, " ", "");
        line.erase(remove(line.begin(), line.end(), '['), line.end());
        line.erase(remove(line.begin(), line.end(), ']'), line.end());
        int i = 0;
        for (auto ch : line) {
          matrix[lineno][i] = ch;
          i++;
          colno = i;
        }
        lineno++;
      } else if (line.empty()) {
        for (int i = 0; i < colno; i++) {
          std::string s;
          for (int j = lineno - 1; j > -1; j--) {
            if (matrix[j][i] != '*') {
              s.push_back(matrix[j][i]);
            }
          }
          // std::cout << s << std::endl;
          vect.push_back(s);
        }
      } else if (line.find("move") != std::string::npos) {
        replace_all(line, "move", "");
        replace_all(line, "from", "");
        replace_all(line, "to", "");
        int x, y, z;
        std::stringstream ss;
        ss << line;
        std::string s;
        ss >> s;
        std::stringstream(s) >> x;
        ss >> s;
        std::stringstream(s) >> y;
        ss >> s;
        std::stringstream(s) >> z;
        // std::cout << x << " " << y << " " << z << std::endl;
        // std::cout << std::endl << std::endl;
        for (int i = 0; i < x; i++) {
          vect[z - 1].push_back(vect[y - 1][vect[y - 1].size() - x + i]);
          // std::cout << vect[z] << std::endl;
          // std::cout << vect[y] << std::endl;
        }
        vect[y - 1] = vect[y - 1].substr(0, vect[y - 1].size() - x);
        // for (int i = 0; i < colno; i++) {
        //   std::cout << vect[i] << std::endl;
        // }
      }
    }
    for (int i = 0; i < colno; i++) {
      std::cout << vect[i][vect[i].size() - 1];
    }
    std::cout << std::endl;
  }
  return 0;
}