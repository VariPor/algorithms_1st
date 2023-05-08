#pragma once

#include <cstddef>
#include <string>
#include <vector>

class HashTable {
 public:
  HashTable(size_t width = 20, size_t height = 10);
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
  size_t width_ = 20;              // count of vector in data
  size_t height_ = 10;              // count of numbers in each vector
  void Rehash();
};
