#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>
#include <initializer_list>

typedef unsigned long long int u64;
typedef unsigned short int u8;

class Move {
private:
  std::vector<u8> indices;
public:
  Move(std::initializer_list<u8> indices);
};

#endif
