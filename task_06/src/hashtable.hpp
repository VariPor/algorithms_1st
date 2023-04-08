#pragma once

#include <cstddef>
#include <string>
#include <vector>

class HashTable {
 public:
  HashTable(int k = 20);
  bool Insert(const std::string& key, int value);
  void InsertOrUpdate(const std::string& key, int value);
  void Remove(const std::string& key);
  int Find(const std::string& key) const;
  size_t Size() const;
  bool Contains(const std::string& key);

 private:
  std::vector<std::vector<std::pair<std::string, int>>> data_;
  std::hash<std::string> hasher_;
  size_t keys_count_ = 0;
};
