#include "../include/Tree.hpp"

u8 Node::getFrom() { return this->from; }
u8 Node::getTo() { return this->to; }
void Node::setFrom(u8 from) { this->from = from; }
void Node::setTo(u8 to) { this->to = to; }
std::vector<Node*>* Node::getChildren() { return &this->children; }
void Node::addChild(Node* child) { this->children.push_back(child); }
