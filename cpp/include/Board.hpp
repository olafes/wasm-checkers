#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>

typedef char u8;
typedef unsigned long long int u64;

class Board {
private:
  static const u64 MASK_BOARD = 0b11111111111111111111111111111111111111111111111111;
  static const u64 MASK_EVEN_ROW = 0b00000111110000011111000001111100000111110000011111;
  static const u64 MASK_ODD_ROW = 0b11111000001111100000111110000011111000001111100000;
  static const u8 MASK_JUMPER_MEN_BORDER[];
  static const std::map<u64, std::vector<u64>> MASK_KING_ATTACK;
  static const u8 JUMPER_MEN_OPPOSITE_DIRECTIONS[];
  static u64 getEmpty(u64 white, u64 black);
  static u64 moveEvenSquares(u64 bitboard, u8 direction);
  static u64 moveOddSquares(u64 bitboard, u8 direction);
  static u64 getJumperMen(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static u64 getJumperKings(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static u64 whiteMen;
  static u64 whiteKings;
  static u64 blackMen;
  static u64 blackKings;
  static bool whiteToMove;

public:
  void init(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, bool playerToMove);
  u64 getWhiteMen();
  u64 getWhiteKings();
  u64 getBlackMen();
  u64 getBlackKings();
  bool getPlayerToMove();
  void setWhiteMen(u64 whiteMen);
  void setWhiteKings(u64 whiteKings);
  void setBlackMen(u64 blackMen);
  void setBlackKings(u64 blackKings);
  void setPlayerToMove(bool playerToMove);
};

#endif
