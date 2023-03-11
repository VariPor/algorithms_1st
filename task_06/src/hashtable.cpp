#include "hashtable.hpp"

#include <cstddef>
#include <string>

HashTable::HashTable() {}

bool HashTable::Insert(const std::string& key, int value) {
  if (data_.contains(key)) return false;
  data_[key] = value;
  return true;
}

void HashTable::InsertOrUpdate(const std::string& key, int value) {
  data_[key] = value;
}

void HashTable::Remove(const std::string& key) {
  auto it = data_.find(key);
  data_.erase(it);
}

int HashTable::Find(const std::string& key) const { return data_.at(key); }

size_t HashTable::Size() const { return data_.size(); }
