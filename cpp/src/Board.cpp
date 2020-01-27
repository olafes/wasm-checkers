#include "../include/Board.hpp"
//private
const u8 Board::JUMPER_MEN_OPPOSITE_DIRECTIONS[] = {2, 3, 0, 1};
const u64 Board::MASK_JUMPER_MEN_BORDER[] = {
  0b01111011110111101111011110111101111011110000000000,
  0b11110111101111011110111101111011110111100000000000,
  0b00000000001111011110111101111011110111101111011110,
  0b00000000000111101111011110111101111011110111101111
};
// const u8 Board::SHIFT_ODD_MOVE[] = {};

u64 Board::getEmpty(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings) {
  return (~(whiteMen|whiteKings|blackMen|blackKings))&Board::MASK_BOARD;
}
u64 Board::moveEvenSquares(u64 bitboard, u8 direction) {
  bitboard &= Board::MASK_EVEN_ROW;
  switch (direction) {
    case 0:
      bitboard = bitboard >> 4;
      break;
    case 1:
      bitboard = bitboard >> 5;
      break;
    case 2:
      bitboard = bitboard << 5;
      break;
    case 3:
      bitboard = bitboard << 6;
      break;
    return bitboard;
  }
}
u64 Board::moveOddSquares(u64 bitboard, u8 direction) {
  bitboard &= Board::MASK_ODD_ROW;
  switch (direction) {
    case 0:
      bitboard = bitboard >> 5;
      break;
    case 1:
      bitboard = bitboard >> 6;
      break;
    case 2:
      bitboard = bitboard << 4;
      break;
    case 3:
      bitboard = bitboard << 5;
      break;
    return bitboard;
  }
}
u64 Board::getJumperMen(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  u64 tmp = Board::getEmpty(whiteMen, whiteKings, blackMen, blackKings)&Board::MASK_JUMPER_MEN_BORDER[direction];
  u8 oppositeDirection = BOARD::JUMPER_MEN_OPPOSITE_DIRECTIONS[direction];
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);
  tmp &= blackMen|blackKings;
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);
  tmp &= whiteMen;
  return tmp;
}
u64 Board::getJumperKings(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  return 0;
}

//public
void init(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, bool playerToMove) {
  Board::whiteMen = whiteMen;
  Board::whiteKings = whiteKings;
  Board::blackMen = blackMen;
  Board::blackKings = blackKings;
  Board::playerToMove = playerToMove;
}
u64 Board::getWhiteMen() {
  return Board::whiteMen;
}
u64 Board::getWhiteKings() {
  return Board::whiteKings;
}
u64 Board::getBlack() {
  return Board::blackMen;
}
u64 Board::getBlackKings() {
  return Board::blackKings;
}
bool Board::getPlayerToMove() {
  return Board::playerToMove;
}
void Board::setWhiteMen(u64 whiteMen) {
  Board::whiteMen = whiteMen;
}
void Board::setWhiteKings(u64 whiteKings) {
  Board::whiteKings = whiteKings;
}
void Board::setBlackMen(u64 blackMen) {
  Board::blackMen = blackMen;
}
void Board::setBlackKings(u64 blackKings) {
  Board::blackKings = blackKings;
}
void Board::setPlayerToMove(bool playerToMove) {
  Board::playerToMove = playerToMove;
}
