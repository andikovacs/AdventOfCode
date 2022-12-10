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

long long powerVal(long instr_index, long rv) {
  static long pos_index = 20;
  long long powerVal = 0;
  if (instr_index == pos_index) {
    powerVal = instr_index * rv;
    pos_index += 40;
  }
  return powerVal;
}

void drawPixel(long instr_index, long rv) {
  auto pixel_counter = (instr_index - 1) % 40;
  if (pixel_counter == 0) {
    std::cout << std::endl;
  }
  if ((pixel_counter == rv) || (pixel_counter == rv + 1) ||
      (pixel_counter == rv - 1)) {
    std::cout << '#';
  } else {
    std::cout << '.';
  }
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  if (input.is_open()) {
    std::string line;
    long instructionIndex = 1;
    long regVal = 1;
    long long power = 0;
    while (getline(input, line)) {
      if (line.substr(0, 4) == "noop") {
        drawPixel(instructionIndex, regVal);
        instructionIndex++;
        power += powerVal(instructionIndex, regVal);
      } else if (line.substr(0, 4) == "addx") {
        drawPixel(instructionIndex, regVal);
        instructionIndex++;
        drawPixel(instructionIndex, regVal);
        power += powerVal(instructionIndex, regVal);
        regVal += stoi(line.substr(5, line.size()));
        instructionIndex++;
        power += powerVal(instructionIndex, regVal);
      }
    }
    std::cout << std::endl << "Power: " << power << std::endl;
  }
  return 0;
}