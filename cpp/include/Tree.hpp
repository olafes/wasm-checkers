#ifndef TREE_HPP
#define TREE_HPP
#include <vector>

typedef unsigned long long int u64;
typedef unsigned short int u8;

class Node {
private:
  std::vector<Node*> children;
  u8 from;
  u8 to;
public:
  Node(u8 from, u8 to) : from{from}, to{to} {};
  u8 getFrom();
  u8 getTo();
  void setFrom(u8 from);
  void setTo(u8 to);
  std::vector<Node*>* getChildren();
  void addChild(Node* child);

};
#endif
