#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T>
class MinHeap {
 public:
  void Push(T value);
  T PopMin();
  T GetMin();
  size_t Size();

 private:
  std::vector<T> data_;
  void SiftUp(int currindex);
  void SiftDown();
  void ChangeHigh();
  size_t height_ = 0;
};

template <typename T>
void MinHeap<T>::SiftDown() {
  if (data_.size() <= 1) return;
  int curr_index = 0;  // start on the top
  for (int i = 0, j = 1; i < height_ - 1; ++i, j = 2 * i + 1) {
    if (data_[j] < data_[j + 1] && data_[j] < data_[i]) {
      std::swap(data_[curr_index], data_[j]);
      curr_index = j;
    } else if (data_[j] > data_[j + 1] && data_[j + 1] < data_[i]) {
      T temp = data_[curr_index];
      data_[curr_index] = data_[j + 1];
      data_[j + 1] = temp;
      curr_index = j + 1;
    } else
      break;  // as low as possible
  }
}

template <typename T>
void MinHeap<T>::SiftUp(int curr_index) {
  if (data_.size() <= 1) return;
  for (int i = height_; i > 0; ++i) {
    if (data_[curr_index] < data_[(curr_index - 1) / 2]) {
      T temp = data_[curr_index];
      data_[curr_index] = data_[(curr_index - 1) / 2];
      data_[(curr_index - 1) / 2] = temp;
      curr_index = (curr_index - 1) / 2;
    } else
      break;
  }
}

template <typename T>
void MinHeap<T>::Push(T n) {
  data_.push_back(n);
  ChangeHigh();
  SiftUp(data_.size() - 1);
}

template <typename T>
T MinHeap<T>::PopMin() {
  if (data_.empty()) throw std::out_of_range("Empty heap");
  auto result = data_[0];
  data_[0] = data_.back();
  data_.pop_back();
  ChangeHigh();
  SiftDown();
  return result;
}

template <typename T>
size_t MinHeap<T>::Size() {
  return data_.size();
}

template <typename T>
void MinHeap<T>::ChangeHigh() {
  if (data_.size() <= 2) {
    height_ = data_.size();
    return;
  }
  height_ = static_cast<int>(floor(log2(data_.size() - 1)) + 1);
}

template <typename T>
T MinHeap<T>::GetMin() {
  if (data_.empty()) throw std::out_of_range("Empty heap");
  return data_[0];
}