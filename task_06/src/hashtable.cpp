#include "hashtable.hpp"

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>

HashTable::HashTable(int k) : data_(k) {}

bool HashTable::Contains(const std::string& key) {
  int hash = hasher_(key) % data_.size();
  if (data_[hash].empty()) return false;
  for (int i = 0; i < data_[hash].size(); ++i)
    if (data_[hash][i].first == key) return true;
  return false;
}

bool HashTable::Insert(const std::string& key, int value) {
  int hash = hasher_(key) % data_.size();
  if (Contains(key)) return false;
  data_[hash].push_back(std::pair<std::string, int>(key, value));
  keys_count_ += 1;
  return true;
}

void HashTable::InsertOrUpdate(const std::string& key, int value) {
  int hash = hasher_(key) % data_.size();
  if (!Contains(key)) {
    keys_count_ += 1;
    data_[hash].push_back(std::pair<std::string, int>(key, value));
  } else
    for (int i = 0; i < data_[hash].size(); ++i)
      if (data_[hash][i].first == key) data_[hash][i].second = value;
}

void HashTable::Remove(const std::string& key) {
  int hash = hasher_(key) % data_.size();
  if (!Contains(key)) throw std::out_of_range("no such key");
  for (int i = 0; i < data_[hash].size(); ++i)
    if (data_[hash][i].first == key) data_[hash].erase(data_[hash].begin() + i);
}

int HashTable::Find(const std::string& key) const {
  int hash = hasher_(key) % data_.size();
  for (int i = 0; i < data_[hash].size(); ++i)
    if (data_[hash][i].first == key) return data_.at(hash).at(i).second;
}

size_t HashTable::Size() const { return keys_count_; }
