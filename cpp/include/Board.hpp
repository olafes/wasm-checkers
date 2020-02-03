#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>
#include "../include/Utils.hpp"

typedef char u8;
typedef unsigned long long int u64;

class Board {
public:
  struct move {
    std::vector<u64> positions;
    std::vector<u64> captures;
  };
  struct board {
    u64 whiteMen;
    u64 whiteKings;
    u64 blackMen;
    u64 blackKings;
    u64 playerToMove;
  };
private:
  struct kingMoveChunk {
    u64 from;
    u64 capture;
    std::vector<u64> landing;
  };
  static const u64 MASK_BOARD;
  static const u64 MASK_BORDER[];
  static const u64 MASK_MOVER_MEN[];
  static const u64 MASK_JUMPER_MEN[];
  static const std::map<u64, std::vector<u64>> MASK_KING_ATTACK;
  static const std::map<u64, std::vector<u64>> MASK_KING_ATTACK_WITHOUT_BORDER;
  static const u8 OPPOSITE_DIRECTIONS[];

  static u64 getEmpty(Board::board state);
  static u64 getMenMovers(Board::board state, u8 direction);
  static u64 getKingMoves(u64 king, Board::board state, u8 direction);
  static std::vector<Board::move> getKingsMovers(Board::board state, u8 direction);
  static Board::kingMoveChunk getJumperKing (u64 king, Board::board state, u64 alreadyCaptured, u8 direction);
  static std::vector<Board::kingMoveChunk> getJumperKings(Board::board state, u64 alreadyCaptured, u8 direction);
  static u64 getJumperMen(Board::board state, u8 direction);
  static void makeManMove(u64* man, Board::board* state, u8 direction);
  static u64 makeManCapture(u64* man, Board::board* state, u8 direction);
  static void makeKingMove(u64* king, Board::board* state, u64 landing);
  static void makeKingCapture(u64* king, Board::board* state, u64 landing, u64 target);
  static void calculateManCaptures(u64 man, Board::board state, u8 count, u8* n, Board::move mv, std::vector<Board::move>* found);
  static std::vector<move> getMenCaptures(Board::board state, u8* depth);
  static void calculateKingCaptures(u64 king, Board::board state, u64 alreadyCaptured, u8 count, u8* n, Board::move mv, std::vector<Board::move>* found);
  static std::vector<Board::move> getKingsCaptures(Board::board state, u8* depth);

  Board::board state;
  std::vector<Board::board> history;
public:
  Board(Board::board state): state{state} {};
  Board::board getState();
  u64 getWhiteMen();
  u64 getWhiteKings();
  u64 getBlackMen();
  u64 getBlackKings();
  bool getPlayerToMove();
  void setState(Board::board state);
  void setWhiteMen(u64 whiteMen);
  void setWhiteKings(u64 whiteKings);
  void setBlackMen(u64 blackMen);
  void setBlackKings(u64 blackKings);
  void setPlayerToMove(bool playerToMove);

  std::vector<move> getLegalPushes();
  std::vector<move> getLegalCaptures();
  std::vector<move> getLegalMoves();
  void makeMove(Board::move mv);
  u8 getResult();
};

bool operator==(const Board::board& a, const Board::board& b);

#endif
