#include "hashtable.hpp"

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>

HashTable::HashTable(size_t width) : width_(width) {}

bool HashTable::Contains(const std::string& key) {
  int hash_w = hasher_(key) % width_;
  if (!data_[hash_w].empty() && data_[hash_w][0].first == key) return true;
  return false;
}

bool HashTable::Insert(const std::string& key, int value) {
  int hash_w = hasher_(key) % width_;
  if (Contains(key)) return false;
  data_[hash_w].push_back(std::pair<std::string, int>(key, value));
  keys_count_ += 1;
  this->Rehash();
  return true;
}

void HashTable::InsertOrUpdate(const std::string& key, int value) {
  int hash_w = hasher_(key) % width_;
  if (!Contains(key)) keys_count_ += 1;
  for (int i = 0; i < data_[hash_w].size(); ++i)
    if (data_[hash_w][i].first == key) {
      data_[hash_w][i].second = value;
      return;
    }
  data_[hash_w].push_back(std::pair<std::string, int>(key, value));
  this->Rehash();
}

void HashTable::Remove(const std::string& key) {
  int hash_w = hasher_(key) % width_;
  if (!Contains(key)) throw std::out_of_range("no such key");
  keys_count_ -= 1;
  for (int i = 0; i < data_[hash_w].size(); ++i)
    if (data_[hash_w][i].first == key) {
      data_[hash_w].erase(data_[hash_w].begin() + i);
      this->Rehash();
      return;
    }

}

int HashTable::Find(const std::string& key) const {
  int hash_w = hasher_(key) % width_;
  for (int i = 0; i < data_[hash_w].size(); ++i)
    if (data_[hash_w][i].first == key) 
      return data_.at(hash_w).at(i).second;
}

size_t HashTable::Size() const { return keys_count_; }

void HashTable::Rehash() {
  if (keys_count_ < width_ * 0.8 &&
      (keys_count_ > width_  * 0.2 || width_ <= 20))
    return;

  HashTable new_hash_table;
  if (keys_count_ >= width_  * 0.8)
    new_hash_table = HashTable(width_ * 2);

  for (int i = 0; i < width_; ++i)
    for (int j = 0; j < data_[i].size(); ++j)
      new_hash_table.Insert(data_.at(i).at(j).first, data_.at(i).at(j).second);

  *this = new_hash_table;
}