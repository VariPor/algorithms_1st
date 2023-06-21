#include "sort.hpp"

#include <vector>

std::vector<int> Sort(const std::vector<int>& input) {
  if (input.size() <= 1) return input;
  std::vector<int> output;
  size_t middle = input.size() / 2 + input.size() % 2;
  std::vector<int> smaller_part(input.begin(), input.begin() + middle);
  std::vector<int> bigger_part(input.begin() + middle, input.end());

  smaller_part = Sort(smaller_part);
  bigger_part = Sort(bigger_part);  
  for (size_t i = 0, j = 0; i < smaller_part.size() || j < bigger_part.size();) {
    if (smaller_part[i] <= bigger_part[j]) {
      output.push_back(smaller_part[i]);
      ++i;
      if (i == smaller_part.size()) {
        output.insert(output.end(), bigger_part.begin() + j, bigger_part.end());
        break;
      }
    } else {
      output.push_back(bigger_part[j]);
      ++j;
      if (j == bigger_part.size()) {
        output.insert(output.end(), smaller_part.begin() + i,
                      smaller_part.end());
        break;
      }
    }
  }
  return output;
}