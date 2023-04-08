#pragma once
#include <memory>

class Tree {
  struct Node;

 public:
  std::shared_ptr<Node> root = nullptr;
  Tree();
  Tree(std::shared_ptr<Node> r) : root{r} {};

  bool Insert(int key, int value);
  void InsertOrUpdate(int key, int value);
  int Find(int key) const;
  void Delete(int key);
};
