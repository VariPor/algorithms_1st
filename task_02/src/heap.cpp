#include "heap.hpp"

#include <cstddef>
#include <stdexcept>

void MinHeap::SiftDown() {
  if (data_.size() <= 1) return;
  int ind_num_down = 0;   //start on the top
  for (int i = 0; i < high_ - 1; ++i) {
    if (data_[2 * i + 1] < data_[2 * i + 2] && data_[2 * i + 1] < data_[i]) {
      int temp = data_[ind_num_down];
      data_[ind_num_down] = data_[2 * i + 1];
      data_[2 * i + 1] = temp;
      ind_num_down = 2 * i + 1;
    } else if (data_[2 * i + 1] > data_[2 * i + 2] && data_[2 * i + 2] < data_[i]) {
      int temp = data_[ind_num_down];
      data_[ind_num_down] = data_[2 * i + 2];
      data_[2 * i + 2] = temp;
      ind_num_down = 2 * i + 2;
    } else break; // as low as possible
  }
}

void MinHeap::SiftUp(int ind_num_up) {
  if (data_.size() <= 1) return;
  for (int i = high_; i > 0; ++i) {
    if (data_[ind_num_up] < data_[(ind_num_up - 1) / 2]) {
      int temp = data_[ind_num_up];
      data_[ind_num_up] = data_[(ind_num_up - 1) / 2];
      data_[(ind_num_up - 1) / 2] = temp;
      ind_num_up = (ind_num_up - 1) / 2;
    } else break;
  }
}

void MinHeap::Push(int n) { 
  data_.push_back(n);
  ChangeHigh();
  SiftUp(data_.size() - 1);
}

int MinHeap::PopMin() {
  if (data_.empty()) throw std::out_of_range("Empty heap");
  auto result = data_[0];
  data_[0] = data_[data_.size() - 1];
  data_.pop_back();
  ChangeHigh();
  SiftDown();
  return result;
}

size_t MinHeap::Size() { return data_.size(); }

void MinHeap::ChangeHigh() {
  if (data_.size() <= 2) {
    high_ = data_.size();
    return;
  }
  high_ = static_cast<int>(floor(log2(data_.size() - 1)) + 1); 
}