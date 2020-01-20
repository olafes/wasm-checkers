#ifndef TREE_HPP
#define TREE_HPP
#include <vector>

typedef unsigned long long int u64;
typedef unsigned short int u8;

class Node {
private:
  std::vector<Node*> children;
  Move move;
public:
  Node(Move move);
};
#endif
