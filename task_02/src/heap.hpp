#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include <cmath>

class MinHeap {
 public:
  void Push(int value);
  int PopMin();
  int GetMin();
  size_t Size();


 private:
  std::vector<int> data_ ;
  void SiftUp(int);
  void SiftDown();
  int high_ = 0;
  void ChangeHigh();
};
