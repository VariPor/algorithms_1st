#include "sort.hpp"

#include <vector>

std::vector<int> Sort(const std::vector<int>& input) {
  if (input.size() <= 1) return input;
  std::vector<int> output;
  std::vector<int> smaller_part;
  std::vector<int> bigger_part;
  for (int i = 0; i < input.size() / 2 + input.size() % 2; ++i) {
    if (i == input.size() / 2 && input.size() % 2 == 1) {
      smaller_part.push_back(input[i]);
      break;
    }
    smaller_part.push_back(input[i]);
    bigger_part.push_back(input[i + input.size() / 2 + input.size() % 2]);
  }
  smaller_part = Sort(smaller_part);
  bigger_part = Sort(bigger_part);
  for (int i = 0, j = 0; i < smaller_part.size() || j < bigger_part.size();) {
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