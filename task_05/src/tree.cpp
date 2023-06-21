#include "tree.hpp"

#include "exception"

bool operator==(const Tree::Node &left, const Tree::Node &right) {
  if (left.parent.lock() != right.parent.lock()) return false;
  if (left.left_child != right.left_child) return false;
  if (left.right_child != right.right_child) return false;
  return true;
}

bool operator!=(const Tree::Node &left, const Tree::Node &right) {
  return !(left == right);
}

Tree::Node::Node(const Node &node)
    : parent{node.parent},
      left_child{node.left_child},
      right_child{node.right_child},
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
    root = std::make_shared<Node>(Node(key, value));
    return std::pair<Tree::Node &, bool>(*(root.get()), true);
  }
  if (root->key < key)
    return (Tree(root->left_child).InsertWithoutSplay(key, value));
  if (root->key > key)
    return Tree(root->right_child).InsertWithoutSplay(key, value);
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
    return Tree(root->left_child).InsertOrUpdateWithoutSplay(key, value);
  if (root->key > key)
    return Tree(root->right_child).InsertOrUpdateWithoutSplay(key, value);
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
  if (root->key < key) Tree(root->left_child).Find(key);
  if (root->key > key) Tree(root->right_child).Find(key);
  if (root->key == key)
    return std::pair<Node &, int>(*(root.get()), root->value);
}

void Tree::Delete(int key) {
  auto deleting_node = FindWithoutSplay(key).first;

  if (deleting_node.left_child == nullptr &&
      deleting_node.right_child == nullptr) {
    if (*(root.get()) != deleting_node) {
      if (IsLeftChild(deleting_node))
        deleting_node.parent.lock()->left_child = nullptr;
      else
        deleting_node.parent.lock()->right_child = nullptr;
    }
  } else
    root = nullptr;

  if (deleting_node.left_child == nullptr &&
      deleting_node.right_child != nullptr) {
    if (*(root.get()) != deleting_node) {
      if (IsLeftChild(deleting_node))
        deleting_node.parent.lock()->left_child = deleting_node.right_child;
      else
        deleting_node.parent.lock()->right_child = deleting_node.right_child;
      deleting_node.right_child = deleting_node.parent.lock();
    }
  }

  if (deleting_node.left_child != nullptr &&
      deleting_node.right_child == nullptr) {
    if (*(root.get()) != deleting_node) {
      if (IsLeftChild(deleting_node))
        deleting_node.parent.lock()->left_child = deleting_node.left_child;
      else
        deleting_node.parent.lock()->right_child = deleting_node.left_child;
      deleting_node.left_child = deleting_node.parent.lock();
    }
  }

  if (deleting_node.left_child != nullptr &&
      deleting_node.right_child != nullptr) {
    auto new_node = deleting_node.right_child;
    while (new_node->left_child != nullptr) new_node = new_node->left_child;
    if (IsLeftChild(*(new_node.get())))
      new_node->parent.lock()->left_child = nullptr;
    else
      new_node->parent.lock()->right_child = nullptr;
    new_node->parent = deleting_node.parent;
    new_node->left_child = deleting_node.left_child;
    new_node->right_child = deleting_node.right_child;
    if (IsLeftChild(*(new_node.get())))
      deleting_node.parent.lock()->left_child = new_node;
    else
      deleting_node.parent.lock()->right_child = new_node;
    deleting_node.left_child->parent = new_node;
    deleting_node.right_child->parent = new_node;
  }
}

void Tree::Zig(Node &element) {
  if (!element.parent.lock()) return;
  if (element == *(element.parent.lock()->left_child.get())) {
    auto old_parent = element.parent;
    auto old_left_child = element.left_child;
    auto old_right_child = element.right_child;
    *(element.parent.lock()->parent.lock()) = element;
    element.right_child = element.parent.lock();
    element.parent = old_parent.lock()->parent;
    *(old_parent.lock()->left_child) = element;
    old_parent.lock()->left_child = old_right_child;
    old_right_child->parent = old_parent;
  }
  if (element == *(element.parent.lock()->right_child.get())) {
    auto old_parent = element.parent;
    auto old_right_child = element.right_child;
    auto old_left_child = element.left_child;
    *(element.parent.lock()->parent.lock()) = element;
    element.left_child = element.parent.lock();
    element.parent = old_parent.lock()->parent;
    *(old_parent.lock()->right_child) = element;
    old_parent.lock()->right_child = old_left_child;
    old_left_child->parent = old_parent;
  }
}

void Tree::ZigZig(Node &element) {
  Zig(*element.parent.lock());
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
  if (IsLeftChild(element) && IsLeftChild(*(element.parent.lock()))) return true;
  if (IsRightChild(element) && IsRightChild(*(element.parent.lock()))) return true;
  return false;
}

bool Tree::IsLeftChild(const Node &element) {
  if (element.parent.lock() == nullptr) return false;
  if (element == *(element.parent.lock()->left_child.get())) return true;
  return false;
}

bool Tree::IsRightChild(const Node &element) {
  if (element.parent.lock() == nullptr) return false;
  if (element == *(element.parent.lock()->right_child.get())) return true;
  return false;
}

bool Tree::HaveGrandpa(const Node &element) {
  if (element.parent.lock() == nullptr) return false;
  if (element.parent.lock()->parent.lock() != nullptr) return true;
  return false;
}