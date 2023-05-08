#include "hashtable.hpp"

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>

HashTable::HashTable(size_t width, size_t height)
    : width_(width), height_(height) {
  for (int i = 0; i < width; ++i)
    data_.push_back(std::vector<std::pair<std::string, int>>(height));
}

bool HashTable::Contains(const std::string& key) {
  int hash_w = hasher_(key) % width_;
  int hash_h = hasher_(key) % height_;
  if (data_[hash_w][hash_h].first == key) return true;
  return false;
}

bool HashTable::Insert(const std::string& key, int value) {
  int hash_w = hasher_(key) % width_;
  int hash_h = hasher_(key) % height_;
  if (Contains(key)) return false;
  data_[hash_w][hash_h] = std::pair<std::string, int>(key, value);
  keys_count_ += 1;
  return true;
}

void HashTable::InsertOrUpdate(const std::string& key, int value) {
  int hash_w = hasher_(key) % width_;
  int hash_h = hasher_(key) % height_;
  if (!Contains(key)) keys_count_ += 1;
  data_[hash_w][hash_h] = std::pair<std::string, int>(key, value);
}

void HashTable::Remove(const std::string& key) {
  int hash_w = hasher_(key) % width_;
  int hash_h = hasher_(key) % height_;
  if (!Contains(key)) throw std::out_of_range("no such key");
  keys_count_ -= 1;
  data_[hash_w][hash_h] = std::pair<std::string, int>();
}

int HashTable::Find(const std::string& key) const {
  int hash_w = hasher_(key) % width_;
  int hash_h = hasher_(key) % height_;
  return data_.at(hash_w).at(hash_h).second;
}

size_t HashTable::Size() const { return keys_count_; }

void HashTable::Rehash() {
  if (keys_count_ < width_ * height_ * 0.8 &&
      (keys_count_ > width_ * height_ * 0.2 || width_ <= 20 && height_ <= 10))
    return;

  HashTable new_hash_table;
  if (keys_count_ >= width_ * height_ * 0.8)
    new_hash_table = HashTable(width_ * 2, height_ * 2);

  for (int i = 0; i < width_; ++i)
    for (int j = 0; j < height_; ++j)
      new_hash_table.Insert(data_.at(i).at(j).first, data_.at(i).at(j).second);
  
  *this = new_hash_table;
}
