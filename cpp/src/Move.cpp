#include <initializer_list>
#include "../include/Move.hpp"

Move::Move(std::initializer_list<u8> indices) {
  for (auto const& index : indices) {
    this->indices.push_back(index);
  }
}
