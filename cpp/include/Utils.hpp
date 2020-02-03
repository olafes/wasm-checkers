#ifndef UTILS_HPP
#define UTILS_HPP

typedef char u8;
typedef unsigned long long int u64;

class Utils {
private:
  static const u64 BYTE_REVERSE[];
public:
  static const u64 MASK_EVEN_ROW;
  static const u64 MASK_ODD_ROW;
  static u64 getMSB(u64 bitboard);
  static u64 getLSB(u64 bitboard);
  static u64 setLeftSideOfMSB(u64 bitboard);
  static u64 setRightSideOfMSB(u64 bitboard);
  static u64 setLeftSideOfLSB(u64 bitboard);
  static u64 setRightSideOfLSB(u64 bitboard);
  static u64 reverse(u64 bitboard);
  static u64 moveEvenSquares(u64 bitboard, u8 direction);
  static u64 moveOddSquares(u64 bitboard, u8 direction);
  static u64 moveSquares(u64 bitboard, u8 direction);
};

#endif
