#pragma once
#include <memory>

class Tree {
 public:
  struct Node {
    std::shared_ptr<Node> parent = nullptr;
    std::shared_ptr<Node> leftChild = nullptr;
    std::shared_ptr<Node> rightChild = nullptr;
    int value;
    int key;
    Node(int k, int v);
    Node(Node& node);

    Node(const Node& other) = default;
    Node& operator=(const Node& rhs) = default;

    Node(Node&& other) = default;
    Node& operator=(Node&& rhs) = default;
  };

 private:
  void Zig(Node& element);
  void ZigZig(Node& element);
  void ZigZag(Node& element);
  void Splay(Node& element);
  std::pair<Node&, bool> InsertWithoutSplay(int key, int value);
  Node& InsertOrUpdateWithoutSplay(int key, int value);
  std::pair<Node&, int> FindWithoutSplay(int key);

 public:
  std::shared_ptr<Node> root = nullptr;
  Tree();
  Tree(std::shared_ptr<Node> r) : root{r} {};

  bool Insert(int key, int value);
  void InsertOrUpdate(int key, int value);
  int Find(int key);
  void Delete(int key);

  bool IsLeftChild(const Node& element);
  bool IsRightChild(const Node& element);
  bool IsDirectChild(const Node& element);
  bool HaveGrandpa(const Node& element);
};
