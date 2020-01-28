#include "../include/Node.hpp"

Node* Node::addChild(u64 position) {
  // std::cout << "Add child called with position: " << position << std::endl;
  // std::cout << "On node with numer of children: " << this->children.size() << std::endl;
  // std::cout
  Node* child = new Node(position);
  child->setParent(this);
  this->children.push_back(child);
  return child;
}
void Node::setParent(Node* parent) {
  this->root = false;
  this->parent = parent;
}
void Node::populate(std::vector<u64>* moves) {
  // std::cout << "Node with position: " << this->position << std::endl;
  moves->push_back(this->position);
  if (!this->root)
    this->parent->populate(moves);
}



// u8 Node::getFrom() { return this->from; }
// u8 Node::getTo() { return this->to; }
// void Node::setFrom(u8 from) { this->from = from; }
// void Node::setTo(u8 to) { this->to = to; }
// std::vector<Node*>* Node::getChildren() { return &this->children; }
// void Node::addChild(Node* child) { this->children.push_back(child); }
