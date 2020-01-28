#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>

typedef char u8;
typedef unsigned long long int u64;

class Node {
private:
  Node* parent;
  bool root;
  std::vector<Node*> children;
public:
  u64 position = 69;
  Node(u64 position) : position{position}, parent{NULL}, root{true} {};
  Node* addChild(u64 position);
  void setParent(Node* parent);
  void populate(std::vector<u64>* moves);
};
#endif
