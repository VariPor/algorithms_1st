#pragma once

#include <vector>

class Stack {
 public:
  void Push(int value);
  int Pop();
  bool IsEmpty();

  int GetLast();

 private:
  std::vector<int> data_;
};

class MinStack : Stack {
 public:
  void Push(int value);
  int Pop();
  int GetMin();

 private:
  std::vector<int> data_;
  Stack minimums_;
};