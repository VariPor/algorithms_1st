#include "tree.hpp"

#include "exception"

struct Tree::Node {
  std::shared_ptr<Node> parent = nullptr;
  std::shared_ptr<Node> leftChild = nullptr;
  std::shared_ptr<Node> rightChild = nullptr;
  int value;
  int key;
  Node(int k, int v) : key{k}, value{v} {}
};

Tree::Tree() {}

bool Tree::Insert(int key, int value) {
  if (root == nullptr) {
    root = std::shared_ptr<Node>(std::make_shared<Node>(Node(key, value)));
    return true;
  }
  if (root->key < key) return Tree(root->leftChild).Insert(key, value);
  if (root->key > key) return Tree(root->rightChild).Insert(key, value);
  if (root->key == key) return false;
}

void Tree::InsertOrUpdate(int key, int value) {
  if (root == nullptr)
    root = std::shared_ptr<Node>(std::make_shared<Node>(Node(key, value)));
  if (root->key < key) Tree(root->leftChild).InsertOrUpdate(key, value);
  if (root->key > key) Tree(root->rightChild).InsertOrUpdate(key, value);
  if (root->key == key) root->value = value;
}

int Tree::Find(int key) const {
  if (root == nullptr) throw std::out_of_range("No such key\n");
  if (root->key < key) Tree(root->leftChild).Find(key);
  if (root->key > key) Tree(root->rightChild).Find(key);
  if (root->key == key) return root->value;
}

void Tree::Delete(int key) {}