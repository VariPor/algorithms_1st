#pragma once

#include <vector>

class Stack {
 public:
  virtual void Push(int value);
  virtual int Pop();
  bool IsEmpty();

  int GetLast();

 protected:
  std::vector<int> data_;
};

class MinStack : Stack {
 public:
  void Push(int value) override;
  int Pop() override;
  int GetMin();

 private:
  Stack minimums_;
};