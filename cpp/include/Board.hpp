#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Move.hpp"
#include "Tree.hpp"

typedef unsigned long long int u64;
typedef unsigned short int u8;

class Board {
private:
  static const u64 BOARD = 0b11111111111111111111111111111111111111111111111111;
  static const u64 MASK_EVEN_ROW = 0b11111000001111100000111110000011111000001111100000;
  static const u64 MASK_ODD_ROW = 0b00000111110000011111000001111100000111110000011111;
  static const u64 MASK_JUMPERS_0 = 0b00000000000111101111011110111101111011110111101111;
  static const u64 MASK_JUMPERS_1 = 0b00000000001111011110111101111011110111101111011110;
  static const u64 MASK_JUMPERS_2 = 0b11111111111111011110111101111011110111101111011110;
  static const u64 MASK_JUMPERS_3 = 0b01111011110111101111011110111101111011110000000000;
  static const u64 MASK_WHITE_MOVERS_EVEN0 = 0b00000000000111100000011110000001111000000111100000;
  static const u64 MASK_WHITE_MOVERS_EVEN1 = 0b00000111100000011110000001111000000111100000011110;
  //todo mask white movers odd
  //todo mask black
  static u64 getEmpty(u64 white, u64 black);
  static std::vector<u64> getWhiteJumpers(u64 white, u64 black);
  static std::vector<u64> getBlackJumpers(u64 white, u64 black);
  static std::vector<u64> getWhiteMovers(u64 white, u64 black);
  static std::vector<u64> getBlackMovers(u64 white, u64 black);

  u64 white;
  u64 black;
  u8 tour;
  bool white_to_move;

public:
  Board();
  Board(u64 white, u64 black, bool white_to_move);
  u64 getWhite();
  u64 getBlack();
  std::vector<Move> getLegalCaptures();
  u64 move(Move move);
};

#endif
