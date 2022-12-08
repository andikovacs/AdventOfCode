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

bool isVisible(const std::vector<std::string>& mat, unsigned long x,
               unsigned long y) {
  unsigned long opacity_counter = 0;
  for (unsigned long i = 0; i < x; i++) {  // up
    if (mat[i][y] >= mat[x][y]) {
      opacity_counter++;
      break;
    }
  }
  for (unsigned long i = x + 1; i < mat.size(); i++) {  // down
    if (mat[i][y] >= mat[x][y]) {
      opacity_counter++;
      break;
    }
  }

  for (unsigned long i = 0; i < y; i++) {  // left
    if (mat[x][i] >= mat[x][y]) {
      opacity_counter++;
      break;
    }
  }

  for (unsigned long i = y + 1; i < mat[0].size(); i++) {  // right
    if (mat[x][i] >= mat[x][y]) {
      opacity_counter++;
      break;
    }
  }

  return opacity_counter < 4;
}

unsigned long long calculateScenicScore(const std::vector<std::string>& mat,
                                        unsigned long x, unsigned long y) {
  unsigned long long score = 1;
  unsigned long score_dir = 0;
  for (long i = x - 1; i >= 0; i--) {  // up
    score_dir++;
    if (mat[i][y] >= mat[x][y]) {
      break;
    }
  }
  score *= score_dir;

  score_dir = 0;
  for (unsigned long i = x + 1; i < mat.size(); i++) {  // down
    score_dir++;
    if (mat[i][y] >= mat[x][y]) {
      break;
    }
  }
  score *= score_dir;

  score_dir = 0;
  for (long i = y - 1; i >= 0; i--) {  // left
    score_dir++;
    if (mat[x][i] >= mat[x][y]) {
      break;
    }
  }
  score *= score_dir;

  score_dir = 0;
  for (unsigned long i = y + 1; i < mat.size(); i++) {  // right
    score_dir++;
    if (mat[x][i] >= mat[x][y]) {
      break;
    }
  }
  score *= score_dir;

  return score;
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  std::vector<std::string> matrix;
  if (input.is_open()) {
    std::string line;
    unsigned long long visible_count = 0;
    while (getline(input, line)) {
      std::cout << line << std::endl;
      matrix.push_back(line);
    }
    unsigned long m = matrix.size();
    unsigned long n = line.size();
    // std::cout << m << " " << n << std::endl;
    visible_count = 2 * m + 2 * (n - 2);
    // std::cout << visible_count << std::endl;
    unsigned long long max = 0;
    unsigned long max_i = 0;
    unsigned long max_j = 0;
    for (unsigned long i = 1; i < m - 1; i++) {
      for (unsigned long j = 1; j < n - 1; j++) {
        auto num = calculateScenicScore(matrix, i, j);
        // std::cout << num << " " << i << " " << j << "" << std::endl;
        if (max < num) {
          max = num;
          max_i = i;
          max_j = j;
        }
        if (isVisible(matrix, i, j)) {
          // std::cout << i << " " << j << std::endl;
          visible_count++;
          // std::cout << i << " " << j << "" << std::endl;
        }
      }
    }
    std::cout << visible_count << std::endl;
    std::cout << max << std::endl;
  }
  return 0;
}