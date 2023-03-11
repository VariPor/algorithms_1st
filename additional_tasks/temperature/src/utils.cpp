#include "utils.hpp"

#include <algorithm>
#include <stack>
#include <utility>

std::vector<int> CalculateDaysBeforWarmup(
    const std::vector<float>& temperature) {
  int n = temperature.size();
  std::stack<std::pair<float, int>> add_stack;
  std::vector<int> res(n);

  for (int i = n - 1; i > -1; --i) {
    if (add_stack.empty()) {
      add_stack.push(std::pair<float, int> (temperature.at(i), i));
      res[i] = 0;
      continue;
    }
    if (temperature[i] < add_stack.top().first) {
      res[i] = add_stack.top().second - i;
      add_stack.push(std::pair<float, int> (temperature.at(i), i));
      continue;
    } 
    if (temperature[i] >= add_stack.top().first) {
      while (!add_stack.empty() && temperature[i] > add_stack.top().first) {
        add_stack.pop();        
      }
      if (add_stack.empty()) {
      add_stack.push(std::pair<float, int> (temperature.at(i), i));
      res[i] = 0;
      continue;
    }
      res[i] = add_stack.top().second - i;
      add_stack.push(std::pair<float, int> (temperature.at(i), i));
      continue;
    }
  }
  return res;
}
