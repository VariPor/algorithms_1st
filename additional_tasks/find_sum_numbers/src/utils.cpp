#include "utils.hpp"

#include <algorithm>

std::pair<int, int> GetNumbersOfSum(const std::vector<int>& numbers, int sum) {
  if (numbers.empty()) throw std::out_of_range("Empty list of numbers");
  int i = 0;
  int j = numbers.size() - 1;
  while (i < j) {
    if (numbers.at(i) + numbers.at(j) == sum)
      return std::pair<int, int>(numbers.at(i), numbers.at(j));
    if (numbers.at(i) + numbers.at(j) < sum) ++i;
    if (numbers.at(i) + numbers.at(j) > sum) --j;
  }
  return std::pair<int, int>(0, 0);
}