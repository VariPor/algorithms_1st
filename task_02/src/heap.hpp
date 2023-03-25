#pragma once

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
  void SiftUp(int);
  void SiftDown();
  int height_ = 0;
  void ChangeHigh();
};

template <typename T>
void MinHeap<T>::SiftDown() {
  if (data_.size() <= 1) return;
  int curr_ind = 0;  // start on the top
  for (int i = 0, j = 1; i < height_ - 1; ++i, j = 2 * i + 1) {
    if (data_[j] < data_[j + 1] && data_[j] < data_[i]) {
      T temp = data_[curr_ind];
      data_[curr_ind] = data_[j];
      data_[j] = temp;
      curr_ind = j;
    } else if (data_[j] > data_[j + 1] && data_[j + 1] < data_[i]) {
      T temp = data_[curr_ind];
      data_[curr_ind] = data_[j + 1];
      data_[j + 1] = temp;
      curr_ind = j + 1;
    } else
      break;  // as low as possible
  }
}

template <typename T>
void MinHeap<T>::SiftUp(int ind_num_up) {
  if (data_.size() <= 1) return;
  for (int i = height_; i > 0; ++i) {
    if (data_[ind_num_up] < data_[(ind_num_up - 1) / 2]) {
      T temp = data_[ind_num_up];
      data_[ind_num_up] = data_[(ind_num_up - 1) / 2];
      data_[(ind_num_up - 1) / 2] = temp;
      ind_num_up = (ind_num_up - 1) / 2;
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
  return data_[0];
}