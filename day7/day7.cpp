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

class MyFile {
 public:
  unsigned long size;
  bool file_type;  // true file / false directory
  std::string name;
};

std::ostream& operator<<(std::ostream& os, const MyFile& f) {
  os << f.name << ' ' << f.size << ' ' << f.file_type;
  return os;
}

template <class T>
class
    lstdTreeNode {  // class copied from here
                    // https://levelup.gitconnected.com/a-template-tree-class-in-c-7be9b4834e09
 public:
  lstdTreeNode() {}
  lstdTreeNode(const T& t) { this->t = t; }
  virtual ~lstdTreeNode() {}
  void addChild(const T& t) { this->children.push_back(lstdTreeNode(t)); }
  // remove a child by value, note: if the node has multiple children with the
  // same value, this will only delete the first child
  void removeChild(const T& t) {
    for (uint i = 0; i < this->children.size(); ++i) {
      if (this->children.at(i).t == t) {
        this->children.erase(this->children.begin() + i);
        return;
      }
    }
  }
  void removeChildByIndex(const int index) {
    this->children.erase(this->children.begin() + index);
  }
  void setValue(const T& t) { this->t = t; }
  T& getValue() { return this->t; }
  const T& getValue() const { return this->t; }
  std::vector<lstdTreeNode>& getChildren() { return this->children; }
  const std::vector<lstdTreeNode>& getChildren() const {
    return this->children;
  }
  // the type has to have an overloaded std::ostream << operator for print to
  // work
  void print(const int depth = 0) const {
    for (int i = 0; i < depth; ++i) {
      if (i != depth - 1)
        std::cout << "    ";
      else
        std::cout << "|-- ";
    }
    std::cout << this->t << std::endl;
    for (uint i = 0; i < this->children.size(); ++i) {
      this->children.at(i).print(depth + 1);
    }
    // std::cout << std::endl << std::endl << std::endl;
  }

 private:
  T t;
  std::vector<lstdTreeNode> children;
};

lstdTreeNode<MyFile> fs({0, 0, "/"});
unsigned long long sum_tot = 0;
unsigned long long total_space = 70000000;
unsigned long long used_space = 0;
unsigned long long needed_space = 0;

void sum(lstdTreeNode<MyFile>& fs) {
  // std::cout << "Initial size:" << fs.getValue().name << " "
  // << fs.getValue().size << std::endl;
  if (fs.getChildren().size() > 0) {
    for (auto el : fs.getChildren()) {
      if (el.getValue().file_type == false) {
        // std::cout << "Folder: " << el.getValue() << std::endl;
        sum(el);
        // std::cout << "Folder new val: " << el.getValue() << std::endl;
      } else {
        used_space += el.getValue().size;
        // std::cout << el.getValue() << " Computed used space: " << used_space
        //           << std::endl;
      }
      fs.getValue().size += el.getValue().size;
    }
  }
  if (fs.getValue().size <= 100000) {
    sum_tot += fs.getValue().size;
    // std::cout << fs.getValue().size << " " << sum_tot << std::endl;
  }
  // fs.print();
}

unsigned long long min = 0xffffffffffffffff;
unsigned long long val = 0;

void find(lstdTreeNode<MyFile>& fs) {
  // std::cout << "Initial size:" << fs.getValue().name << " "
  // << fs.getValue().size << std::endl;
  if (fs.getChildren().size() > 0) {
    for (auto el : fs.getChildren()) {
      if (el.getValue().file_type == false) {
        // std::cout << "Folder: " << el.getValue() << std::endl;
        find(el);
        // std::cout << "Folder new val: " << el.getValue() << std::endl;
        if (el.getValue().size >= needed_space) {
          if ((el.getValue().size - needed_space) < min) {
            min = el.getValue().size - needed_space;
            val = el.getValue().size;
          }
        }
      }
      fs.getValue().size += el.getValue().size;
    }
  }
  if (fs.getValue().size >= needed_space) {
    // std::cout << fs.getValue() << std::endl;
    if ((fs.getValue().size - needed_space) < min) {
      min = fs.getValue().size - needed_space;
      val = fs.getValue().size;
    }
  }
}

int main() {
  std::ifstream input;
  input.open("input.txt");

  std::string line;
  if (input.is_open()) {
    auto current = &fs;
    std::stack<lstdTreeNode<MyFile>*> parent;
    while (getline(input, line)) {
      MyFile f;
      if (line == "$ cd /") {
        // std::cout << "cd / found:" << std::endl;
      } else if (line == "$ ls") {
        // std::cout << "ls found:" << std::endl;
      } else if (line == "$ cd ..") {
        // std::cout << "cd .. found:" << std::endl;
        current = parent.top();
        parent.pop();
      } else if (line.rfind("$ cd ", 0) == 0) {
        // std::cout << "cd found:" << std::endl;
        line = line.erase(0, 5);
        f.name = line;
        f.size = 0;
        f.file_type = false;
        // std::cout << "dir name " << f << std::endl;
        // current->print();
        current->addChild(f);
        // current->print();
        // std::cout << current->getChildren().size() << std::endl;
        parent.push(current);
        current = &(current->getChildren()[current->getChildren().size() - 1]);
        // std::cout << current->getChildren().size() << std::endl;
        // current->print();

      } else {
        if (line.rfind("dir ", 0) == 0) {
          line = line.erase(0, 4);
          // std::cout << "dir found: " << line << std::endl;
        } else {
          auto it = line.find_first_of(' ');
          f.name = line.substr(it + 1, line.size());
          f.size = std::stoi(line.substr(0, it));
          f.file_type = true;
          current->addChild(f);
          // std::cout << "file found: " << f << std::endl;
        }
      }
    }
    fs.print();
    sum(fs);
    std::cout << sum_tot << std::endl;
    std::cout << used_space << std::endl;
    long long free_space = total_space - used_space;
    needed_space = 30000000 - free_space;
    std::cout << needed_space << std::endl;
    sum_tot = 0;
    find(fs);
    std::cout << val << " " << min << std::endl;
  }
  return 0;
}