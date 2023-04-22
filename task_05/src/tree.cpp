#include "tree.hpp"

#include "exception"

bool operator==(const Tree::Node &left, const Tree::Node &right) {
  if (left.parent != right.parent) return false;
  if (left.leftChild != right.leftChild) return false;
  if (left.rightChild != right.rightChild) return false;
  return true;
}

bool operator!=(const Tree::Node &left, const Tree::Node &right) {
  return !(left == right);
}

Tree::Node::Node(Node &node)
    : parent{node.parent},
      leftChild{node.leftChild},
      rightChild{node.rightChild},
      key{node.key},
      value{node.value} {}

Tree::Tree() {}

Tree::Node::Node(int k, int v) : key{k}, value{v} {}

bool Tree::Insert(int key, int value) {
  auto result = InsertWithoutSplay(key, value);
  Splay(result.first);
  return result.second;
}

std::pair<Tree::Node &, bool> Tree::InsertWithoutSplay(int key, int value) {
  if (root == nullptr) {
    root = std::shared_ptr<Node>(std::make_shared<Node>(Node(key, value)));
    return std::pair<Tree::Node &, bool>(*(root.get()), true);
  }
  if (root->key < key)
    return (Tree(root->leftChild).InsertWithoutSplay(key, value));
  if (root->key > key)
    return Tree(root->rightChild).InsertWithoutSplay(key, value);
  if (root->key == key)
    return std::pair<Tree::Node &, bool>(*(root.get()), false);
}

void Tree::InsertOrUpdate(int key, int value) {
  auto result = InsertOrUpdateWithoutSplay(key, value);
  Splay(result);
}

Tree::Node &Tree::InsertOrUpdateWithoutSplay(int key, int value) {
  if (root == nullptr) {
    root = std::shared_ptr<Node>(std::make_shared<Node>(Node(key, value)));
    return *(root.get());
  }
  if (root->key < key)
    return Tree(root->leftChild).InsertOrUpdateWithoutSplay(key, value);
  if (root->key > key)
    return Tree(root->rightChild).InsertOrUpdateWithoutSplay(key, value);
  if (root->key == key) {
    root->value = value;
    return *(root.get());
  }
}

int Tree::Find(int key) {
  auto result = FindWithoutSplay(key);
  Splay(result.first);
  return result.second;
}

std::pair<Tree::Node &, int> Tree::FindWithoutSplay(int key) {
  if (root == nullptr) throw std::out_of_range("No such key\n");
  if (root->key < key) Tree(root->leftChild).Find(key);
  if (root->key > key) Tree(root->rightChild).Find(key);
  if (root->key == key)
    return std::pair<Node &, int>(*(root.get()), root->value);
}

void Tree::Delete(int key) {}

void Tree::Zig(Node &element) {
  if (!element.parent) return;
  if (element == *(element.parent->leftChild.get())) {
    auto old_parent = element.parent;
    auto old_left_child = element.leftChild;
    auto old_right_child = element.rightChild;
    *(element.parent->parent) = element;
    element.rightChild = element.parent;
    element.parent = old_parent->parent;
    *(old_parent->leftChild) = element;
    old_parent->leftChild = old_right_child;
    old_right_child->parent = old_parent;
  }
  if (element == *(element.parent->rightChild.get())) {
    auto old_parent = element.parent;
    auto old_right_child = element.rightChild;
    auto old_left_child = element.leftChild;
    *(element.parent->parent) = element;
    element.leftChild = element.parent;
    element.parent = old_parent->parent;
    *(old_parent->rightChild) = element;
    old_parent->rightChild = old_left_child;
    old_left_child->parent = old_parent;
  }
}

void Tree::ZigZig(Node &element) {
  Zig(*element.parent);
  Zig(element);
}

void Tree::ZigZag(Node &element) {
  Zig(element);
  Zig(element);
}

void Tree::Splay(Node &element) {
  while (element != *(root.get())) {
    if (this->HaveGrandpa(element) && IsDirectChild(element)) ZigZig(element);
    if (this->HaveGrandpa(element) && !IsDirectChild(element)) ZigZag(element);
    if (!(this->HaveGrandpa(element))) Zig(element);
  }
}

bool Tree::IsDirectChild(const Node &element) {
  if (IsLeftChild(element) && IsLeftChild(*(element.parent))) return true;
  if (IsRightChild(element) && IsRightChild(*(element.parent))) return true;
  return false;
}

bool Tree::IsLeftChild(const Node &element) {
  if (element == *(element.parent->leftChild.get())) return true;
  return false;
}

bool Tree::IsRightChild(const Node &element) {
  if (element == *(element.parent->rightChild.get())) return true;
  return false;
}

bool Tree::HaveGrandpa(const Node &element) {
  if (element.parent == nullptr) return false;
  if (element.parent->parent != nullptr) return true;
  return false;
}