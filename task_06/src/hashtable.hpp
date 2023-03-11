#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

class HashTable {
 public:
  HashTable();
  bool Insert(const std::string& key, int value);
  void InsertOrUpdate(const std::string& key, int value);
  void Remove(const std::string& key);
  int Find(const std::string& key) const;
  size_t Size() const;

 private:
  std::unordered_map<std::string, int> data_;
};
