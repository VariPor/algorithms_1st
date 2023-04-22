#include "utils.hpp"

#include <algorithm>
#include <stack>
#include <utility>

struct Day {
  float temperature;
  int index;
  Day(float temperature, int index) : temperature{temperature}, index{index} {}
};

std::vector<int> CalculateDaysBeforWarmup(
    const std::vector<float>& temperature) {
  size_t size = temperature.size();
  std::stack<Day> add_stack;
  std::vector<int> res(size);

  for (int i = size - 1; i > -1; --i) {
    if (add_stack.empty()) {
      add_stack.push(Day(temperature.at(i), i));
      res[i] = 0;
      continue;
    }
    if (temperature[i] < add_stack.top().temperature) {
      res[i] = add_stack.top().index - i;
      add_stack.push(Day(temperature.at(i), i));
      continue;
    }
    if (temperature[i] >= add_stack.top().temperature) {
      while (!add_stack.empty() &&
             temperature[i] > add_stack.top().temperature) {
        add_stack.pop();
      }
      if (add_stack.empty()) {
        add_stack.push(Day(temperature.at(i), i));
        res[i] = 0;
        continue;
      }
      res[i] = add_stack.top().index - i;
      add_stack.push(Day(temperature.at(i), i));
      continue;
    }
  }
  return res;
}
