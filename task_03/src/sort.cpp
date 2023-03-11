#include "sort.hpp"

#include <vector>

std::vector<int> Sort(const std::vector<int>& data) {
  if (data.size() <= 1) return data;
  std::vector<int> result;
  std::vector<int> v1;
  std::vector<int> v2;
  for (int i = 0; i < data.size() / 2 + data.size() % 2; ++i) {
    if (i == data.size() / 2 && data.size() % 2 == 1) {
      v1.push_back(data[i]);
      break;
    }
    v1.push_back(data[i]);
    v2.push_back(data[i + data.size() / 2 + data.size() % 2]);
  }
  v1 = Sort(v1);
  v2 = Sort(v2);
  for (int i = 0, j = 0; i < v1.size() || j < v2.size();) {
    if (v1[i] <= v2[j]) {
      result.push_back(v1[i]);
      ++i;
      if (i == v1.size()) {
        result.insert(result.end(), v2.begin() + j, v2.end());
        break;
      }
    } else {
      result.push_back(v2[j]);
      ++j;
      if (j == v2.size()) {
        result.insert(result.end(), v1.begin() + i, v1.end());
        break;
      }
    }
  }
  return result;
}