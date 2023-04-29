#include "stack.hpp"

#include <algorithm>
#include <stdexcept>

void Stack::Push(int value) { data_.push_back(value); }

int Stack::Pop() {
  if (data_.empty()) throw std::out_of_range{"Empty stack"};
  auto result = data_.back();
  data_.pop_back();
  return result;
}

bool Stack::IsEmpty() { return data_.empty(); }

void MinStack::Push(int value) {
  if (minimums_.IsEmpty()) {
    minimums_.Push(value);
  } else if (value <= data_.back()) {
    minimums_.Push(value);
  }
  data_.push_back(value);
}

int MinStack::Pop() {
  if (data_.empty()) throw std::out_of_range{"Empty stack"};
  auto result = data_.back();
  data_.pop_back();
  if (result == minimums_.GetLast()) {
    minimums_.Pop();
  }
  return result;
}

int Stack::GetLast() { return data_.back(); }

int MinStack::GetMin() { return minimums_.GetLast(); }