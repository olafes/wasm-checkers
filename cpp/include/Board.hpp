#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>
#include "./Node.hpp"

typedef char u8;
typedef unsigned long long int u64;

struct kingMoveChunk {
  u64 from;
  u64 capture;
  std::vector<u64> landing;
};

class Board {
private:
  static const u64 MASK_BOARD = 0b11111111111111111111111111111111111111111111111111;
  static const u64 MASK_EVEN_ROW = 0b00000111110000011111000001111100000111110000011111;
  static const u64 MASK_ODD_ROW = 0b11111000001111100000111110000011111000001111100000;
  static const u64 MASK_JUMPER_MEN_BORDER[];
  static const u64 MASK_MOVER_MEN_BORDER[];
  static const u64 MASK_BORDER[];
  static const std::map<u64, std::vector<u64>> MASK_KING_ATTACK;
  static const u8 JUMPER_MEN_OPPOSITE_DIRECTIONS[];
  static u64 getMSB(u64 bitboard);
  static u64 getLSB(u64 bitboard);
  static u64 clearRightOfMSB(u64 bitboard);
  static u64 getEmpty(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings);
  static u64 whiteMen;
  static u64 whiteKings;
  static u64 blackMen;
  static u64 blackKings;
  static bool playerToMove;

public:
  // moved to public for testing
  static u64 moveEvenSquares(u64 bitboard, u8 direction);
  static u64 moveOddSquares(u64 bitboard, u8 direction);
  static u64 getMenMovers(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static u64 getKingMoves(u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static std::vector<kingMoveChunk> getKingsMovers(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static kingMoveChunk getJumperKing (u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction, u64 blackMenAfterCapture, u64 blackKingsAfterCapture);
  static std::vector<kingMoveChunk> getJumperKings(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction,  u64 blackMenAfterCapture, u64 blackKingsAfterCapture);
  static u64 getJumperMen(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction);
  static void init(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, bool playerToMove);
  static void makeManMove(u64* man, u64* whiteMen, u8 direction);
  static void makeManCapture(u64* man, u64* whiteMen, u64* blackMen, u64* blackKings, u8 direction);
  static void makeKingMove(u64*king, u64* whiteKings, u64 landing);
  static void makeKingCapture(u64*king, u64* whiteKings, u64* blackMen, u64* blackKings, u64 landing, u64 target);

  static void calculateManCaptures(u64 man, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, std::vector<u64> move, std::vector<std::vector<u64>>* found);
  static std::vector<std::vector<u64>> getMenCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings);
  static void calculateKingCaptures(u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, std::vector<u64> move, std::vector<std::vector<u64>>* found, u64 blackMenAfterCapture, u64 blackKingsAfterCapture);
  static std::vector<std::vector<u64>> getKingsCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings);
  // real public
  static u64 getWhiteMen();
  static u64 getWhiteKings();
  static u64 getBlackMen();
  static u64 getBlackKings();
  static bool getPlayerToMove();
  static void setWhiteMen(u64 whiteMen);
  static void setWhiteKings(u64 whiteKings);
  static void setBlackMen(u64 blackMen);
  static void setBlackKings(u64 blackKings);
  static void setPlayerToMove(bool playerToMove);
};

#endif
