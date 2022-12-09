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

void appendNode(std::vector<std::pair<long, long>>& v,
                const std::pair<long, long>& val) {
  if (find(begin(v), end(v), val) == end(v)) {
    v.push_back(val);
  }
}

void computeHeadPosition(std::pair<long, long>& head, const char dir) {
  switch (dir) {
    case 'R':
      head.second++;
      break;
    case 'L':
      head.second--;
      break;
    case 'U':
      head.first--;
      break;
    case 'D':
      head.first++;
      break;
  }
}

void computeTailNewPosition(std::pair<long, long>& head,
                            std::pair<long, long>& tail) {
  long line_diff = head.first - tail.first;
  long col_diff = head.second - tail.second;
  if ((line_diff == 0) && (abs(col_diff) > 1)) {
    if (col_diff > 0) {
      tail.second++;
    } else {
      tail.second--;
    }
  } else if ((col_diff == 0) && (abs(line_diff) > 1)) {
    if (line_diff > 0) {
      tail.first++;
    } else {
      tail.first--;
    }
  } else if ((line_diff != 0) && (col_diff != 0)) {
    if (abs(line_diff) > 1) {
      tail.second = head.second;
      if (line_diff > 0) {
        tail.first++;
      } else {
        tail.first--;
      }
    }
    if (abs(col_diff) > 1) {
      tail.first = head.first;
      if (col_diff > 0) {
        tail.second++;
      } else {
        tail.second--;
      }
    }
  }
}

void computeAndAddTailPositions(std::pair<long, long>& head,
                                std::pair<long, long>& tail,
                                const std::string& move,
                                std::vector<std::pair<long, long>>& v,
                                std::vector<std::pair<long, long>>& head_pos) {
  // std::cout << move << std::endl;
  long nSteps = stoi(move.substr(2, move.size()));
  for (long i = 0; i < nSteps; i++) {
    // std::cout << "START" << std::endl;
    // std::cout << head.first << " " << head.second << std::endl;
    // std::cout << tail.first << " " << tail.second << std::endl;
    computeHeadPosition(head, move[0]);
    head_pos.push_back(head);
    computeTailNewPosition(head, tail);
    appendNode(v, tail);
    // std::cout << "END" << std::endl;
    // std::cout << "H " << head.first << " " << head.second << std::endl;
    // std::cout << "T " << tail.first << " " << tail.second << std::endl;
  }
}

void createTailsPositionsLog(std::vector<std::pair<long, long>>& head_pos) {
  std::vector<std::pair<long, long>> tail_pos;
  std::pair<long, long> x = {0, 0};
  for (int i = 0; i < 8; i++) {
    for (auto e : head_pos) {
      computeTailNewPosition(e, x);
      // std::cout << "H:" << e.first << " " << e.second << std::endl;
      // std::cout << "T:" << x.first << " " << x.second << std::endl;
      tail_pos.push_back(x);
    }
    // std::cout << std::endl << std::endl;
    std::cout << tail_pos.size() << std::endl;
    head_pos = std::move(tail_pos);
    tail_pos.clear();
    // tail_pos.push_back({0, 0});
  }
  for (auto e : head_pos) {
    computeTailNewPosition(e, x);
    appendNode(tail_pos, x);
  }
  std::cout << tail_pos.size() << std::endl;
}

int main() {
  std::ifstream input;
  std::pair<long, long> pos_t = {0, 0};
  std::pair<long, long> pos_h = {0, 0};
  std::vector<std::pair<long, long>> head_pos;
  std::vector<std::pair<long, long>> visited;
  input.open("input.txt");
  if (input.is_open()) {
    visited.push_back({0, 0});
    std::string line;
    unsigned long long visible_count = 0;
    while (getline(input, line)) {
      computeAndAddTailPositions(pos_h, pos_t, line, visited, head_pos);
    }
    // for (auto e : visited) {
    //   std::cout << e.first << "," << e.second << "    ";
    // }
    // std::cout << std::endl;
    std::cout << visited.size() << std::endl << std::endl;

    std::cout << "HPL " << head_pos.size() << std::endl << std::endl;

    createTailsPositionsLog(head_pos);
  }
  return 0;
}