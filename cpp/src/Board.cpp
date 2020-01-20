#include "../include/Board.hpp"
#include <iostream>

Board::Board() {
  this->white = 0b11111111111111111111000100000000000000000000000000;
          //0b 11111 11111 11111 11111 00010 00000 00000 00000 00000 00000
  this->black = 0b00000000000000000000000000001011110111111111111111;
          //0b 00000 00000 00000 00000 00000 00010 11110 11111 11111 11111
  this->tour = 1;
  this->white_to_move = true;
};

u64 Board::getEmpty(u64 white, u64 black) {
  return (~(white|black))&BOARD;
}
std::vector<u64> Board::getWhiteJumpers(u64 white, u64 black) {
  u64 empty = getEmpty();

  u64 empty_jumpers0 = empty&MASK_JUMPERS_0;
  u64 empty_jumpers1 = empty&MASK_JUMPERS_1;
  u64 empty_jumpers2 = empty&MASK_JUMPERS_2;
  u64 empty_jumpers3 = empty&MASK_JUMPERS_3;

  std::vector<u64> jumpers {
    (((((empty_jumpers0&MASK_EVEN_ROW)<<6)&black)<<5)&white)|(((((empty_jumpers0&MASK_EVEN_ROW)<<5)&black)<<6)&white),
    (((((empty_jumpers1&MASK_EVEN_ROW)<<5)&black)<<4)&white)|(((((empty_jumpers1&MASK_EVEN_ROW)<<4)&black)<<5)&white),
    (((((empty_jumpers2&MASK_EVEN_ROW)>>5)&black)>>6)&white)|(((((empty_jumpers2&MASK_EVEN_ROW)>>6)&black)>>5)&white),
    (((((empty_jumpers3&MASK_EVEN_ROW)>>4)&black)>>5)&white)|(((((empty_jumpers3&MASK_EVEN_ROW)>>5)&black)>>4)&white)
  };

  return jumpers;
}
std::vector<u64> Board::getBlackJumpers(u64 white, u64 black) {
  u64 empty = getEmpty();

  u64 empty_jumpers0 = empty&MASK_JUMPERS_0;
  u64 empty_jumpers1 = empty&MASK_JUMPERS_1;
  u64 empty_jumpers2 = empty&MASK_JUMPERS_2;
  u64 empty_jumpers3 = empty&MASK_JUMPERS_3;

  std::vector<u64> jumpers {
    (((((empty_jumpers0&MASK_EVEN_ROW)<<6)&white)<<5)&black)|(((((empty_jumpers0&MASK_EVEN_ROW)<<5)&white)<<6)&black),
    (((((empty_jumpers1&MASK_EVEN_ROW)<<5)&white)<<4)&black)|(((((empty_jumpers1&MASK_EVEN_ROW)<<4)&white)<<5)&black),
    (((((empty_jumpers2&MASK_EVEN_ROW)>>5)&white)>>6)&black)|(((((empty_jumpers2&MASK_EVEN_ROW)>>6)&white)>>5)&black),
    (((((empty_jumpers3&MASK_EVEN_ROW)>>4)&white)>>5)&black)|(((((empty_jumpers3&MASK_EVEN_ROW)>>5)&white)>>4)&black)
  };

  return jumpers;
}
std::vector<u64> Board::getWhiteMovers(u64 white, u64 black) {
  u64 empty = getEmpty();

  std::vector<u64> movers {
    (((empty&MASK_WHITE_MOVERS_EVEN0)<<6)&white)|(((empty&MASK_ODD_ROW)<<5)&white),
    (((empty&MASK_EVEN_ROW)<<5)&white)|(((empty&MASK_WHITE_MOVERS_EVEN1)<<4)&white)
  };

  return movers;
}
std::vector<u64> Board::getBlackMovers() {
  u64 empty = getEmpty();

  std::vector<u64> movers;

  //todo nie chce mi sie na razie tego robic
  return movers;
}
u64 Board::getWhite() {
  return this->white;
}
u64 Board::getBlack() {
  return this->black;
}

std::vector<Move> Board::getLegalCaptures(u64 white, u64 black) {
  std::vector<Move> moves;
  std::vector<u64> jumpers = getWhiteJumpers(white, black);

  u64 sum = jumpers[0]|jumpers[1]|jumpers[2]|jumpers[3]
  if (!sum)
    return moves;

  if (jumpers[0]) {
    do {
      u64 x = jumpers[0]&(~(jumpers[0]-1));
      jumpers[0] &= ~x;
      white &= ~x;
      white |= x>>11;
      black &= ~((((x&MASK_EVEN_ROW)>>5))||((x&MASK_ODD_ROW)>>6));
    } while (x);
  }

  return moves;
}
