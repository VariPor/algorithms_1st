#include "order_statistics.hpp"

#include <random>

size_t GenRandInd(const size_t n) {
  std::random_device rd;   // non-deterministic generator
  std::mt19937 gen(rd());  // to seed mersenne twister.
  std::uniform_int_distribution<> dist(0, n - 1);
  return dist(gen);
}

int QuickSelect(const std::vector<int>& input, const size_t n) {
  std::vector<int> data{input};
  if (data.size() == 1) return data[0];
  int pivot = GenRandInd(data.size());

  int i = 0;
  int j = data.size() - 1;
  while (i < pivot || j > pivot) {
    while (i < pivot && data[i] <= data[pivot]) ++i;
    while (data[j] >= data[pivot] && j > pivot) --j;
    if (i < pivot && j > pivot) {
      int temp = data[i];
      data[i] = data[j];
      data[j] = temp;
    }
    if (i == pivot && j > pivot) {
      int temp = data[pivot];
      data[pivot] = data[j];
      data[j] = temp;
      i = 0;
    }

    if (j == pivot && i < pivot) {
      int temp = data[pivot];
      data[pivot] = data[i];
      data[i] = temp;
      j = data.size() - 1;
    }
  }

  if (pivot == n) return data[pivot];

  if (n < pivot) {
    std::vector<int> temp(pivot);
    std::copy(data.begin(), data.begin() + pivot, temp.begin());
    return QuickSelect(temp, n);
  }

  if (n > pivot) {
    std::vector<int> temp(input.size() - pivot - 1);
    std::copy(data.begin() + pivot + 1, data.end(), temp.begin());
    return QuickSelect(temp, n - pivot - 1);
  }
}

int GetOrderStatistics(const std::vector<int>& data, size_t n) {
  int temp = QuickSelect(data, n);

  return temp;
}
