#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream input;
  input.open("input.txt");
  unsigned int val;
  std::string line;
  unsigned long sum = 0;
  unsigned long sum1 = 0;
  std::vector<unsigned int> elfs;

  int result_matrix[3][3] = {{4, 8, 3}, {1, 5, 9}, {7, 2, 6}};

  int result_matrix1[3][3] = {{3, 4, 8}, {1, 5, 9}, {2, 6, 7}};

  if (input.is_open()) {
    while (getline(input, line)) {
      int my = line[2] - 'X';
      int his = line[0] - 'A';
      sum += result_matrix[his][my];
      sum1 += result_matrix1[his][my];
    }
  }

  std::cout << sum << std::endl;
  std::cout << sum1 << std::endl;

  return 0;
}
