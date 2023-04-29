#include "order_statistics.hpp"

#include <random>

size_t GenRandIndex(const size_t n) {
  std::random_device rd;   // non-deterministic generator
  std::mt19937 gen(rd());  // to seed mersenne twister.
  std::uniform_int_distribution<> dist(0, n - 1);
  return dist(gen);
}

int QuickSelect(const std::vector<int>& input, const size_t k) {
  std::vector<int> data{input};
  if (data.size() == 1) return data[0];
  int pivot = GenRandIndex(data.size());

  int start = 0;
  int end = data.size();
  std::swap(data[pivot], data[end - 1]);
  pivot = end - 1;
  int i = start, j = start;

  while (true) {
    for (; j < end - 1;) {
      if (data[j] <= data[pivot]) {
        std::swap(data[i], data[j]);
        ++i;
        ++j;
      }
      if (data[j] > data[pivot]) ++j;
    }
    std::swap(data[i], data[pivot]);
    if (i == k) return data[i];
    if (i > k)
      end = i;
    else if (i < k)
      start = i;

    pivot = start + GenRandIndex(end - start);
    std::swap(data[pivot], data[end - 1]);
    pivot = end - 1;
    i = start;
    j = start;
  }
}

int GetOrderStatistics(const std::vector<int>& data, size_t n) {
  int temp = QuickSelect(data, n);

  return temp;
}
