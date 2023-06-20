#include "order_statistics.hpp"

#include <random>
#include <stdexcept>

size_t GenRandIndex(const size_t n) {
  std::random_device rd;   // non-deterministic generator
  std::mt19937 gen(rd());  // to seed mersenne twister.
  std::uniform_int_distribution<> dist(0, n - 1);
  return dist(gen);
}

int QuickSelect(const std::vector<int>& input, const size_t k) {
  if (input.size() < k) throw std::out_of_range("Too big statistic");
  std::vector<int> data{input};
  if (data.size() == 1) return data[0];
  size_t pivot = GenRandIndex(data.size());

  size_t start = 0;
  size_t end = data.size();
  std::swap(data[pivot], data[end - 1]);
  pivot = end - 1;
  size_t i = start, j = start;

  while (true) {
    for (; j + 1 < end;) {
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
