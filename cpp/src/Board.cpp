#include "../include/Board.hpp"

//private

const u64 Board::MASK_BORDER[] = {
  0b00000100000000010000000001000000000100000000011111,
  0b00001000000000100000000010000000001000000000111111,
  0b11111000000000100000000010000000001000000000100000,
  0b11111100000000010000000001000000000100000000010000
};
const u64 Board::MASK_MOVER_MEN[] = {
  0b00000111111111011111111101111111110111111111011111,
  0b00000011111111101111111110111111111011111111101111,
  0b11111011111111101111111110111111111011111111100000,
  0b11110111111111011111111101111111110111111111000000
};
const u64 Board::MASK_JUMPER_MEN[] = {
  0b00000000001111011110111101111011110111101111011110,
  0b00000000000111101111011110111101111011110111101111,
  0b01111011110111101111011110111101111011110000000000,
  0b11110111101111011110111101111011110111100000000000
};
const std::map<u64, std::vector<u64>> Board::MASK_KING_ATTACK = {
{0x1, {0b0,0b0,0b0,0b100001000001000010000010000100000100001000000}},
{0x2, {0b0,0b0,0b1000010001000000,0b10000100000100001000001000010000000}},
{0x4, {0b0,0b0,0b10000100010000100010000000,0b1000010000010000100000000}},
{0x8, {0b0,0b0,0b100001000100001000100001000100000000,0b100001000000000}},
{0x10, {0b0,0b0,0b1000010001000010001000010001000010001000000000,0b0}},
{0x20, {0b1,0b0,0b0,0b10000010000100000100001000001000010000010000000000}},
{0x40, {0b10,0b1,0b1000010000000000,0b100001000001000010000010000100000100000000000}},
{0x80, {0b100,0b10,0b10000100010000100000000000,0b10000100000100001000001000000000000}},
{0x100, {0b1000,0b100,0b100001000100001000100001000000000000,0b1000010000010000000000000}},
{0x200, {0b10000,0b1000,0b1000010001000010001000010001000010000000000000,0b100000000000000}},
{0x400, {0b1000010,0b100000,0b1000000000000000,0b10000010000100000100001000001000010000000000000000}},
{0x800, {0b10000100,0b1000001,0b10000100010000000000000000,0b100001000001000010000010000100000000000000000}},
{0x1000, {0b100001000,0b10000010,0b100001000100001000100000000000000000,0b10000100000100001000000000000000000}},
{0x2000, {0b1000010000,0b100000100,0b1000010001000010001000010001000000000000000000,0b1000010000000000000000000}},
{0x4000, {0b0,0b1000001000,0b10000100010000100010000100010000000000000000000,0b0}},
{0x8000, {0b10001000010,0b0,0b0,0b1000001000010000010000100000100000000000000000000}},
{0x10000, {0b100010000100,0b10000100000,0b10000100000000000000000000,0b10000010000100000100001000001000000000000000000000}},
{0x20000, {0b1000100001000,0b100001000001,0b100001000100001000000000000000000000,0b100001000001000010000010000000000000000000000}},
{0x40000, {0b10001000010000,0b1000010000010,0b1000010001000010001000010000000000000000000000,0b10000100000100000000000000000000000}},
{0x80000, {0b100000000000000,0b10000100000100,0b10000100010000100010000100000000000000000000000,0b1000000000000000000000000}},
{0x100000, {0b10000100010000100,0b1000000000000000,0b10000000000000000000000000,0b1000001000010000010000100000000000000000000000000}},
{0x200000, {0b100001000100001000,0b10000010000100000,0b100001000100000000000000000000000000,0b10000010000100000100001000000000000000000000000000}},
{0x400000, {0b1000010001000010000,0b100000100001000001,0b1000010001000010001000000000000000000000000000,0b100001000001000010000000000000000000000000000}},
{0x800000, {0b10000100000000000000,0b1000001000010000010,0b10000100010000100010000000000000000000000000000,0b10000100000000000000000000000000000}},
{0x1000000, {0b0,0b10000010000100000100,0b100001000100001000100000000000000000000000000000,0b0}},
{0x2000000, {0b100010000100010000100,0b0,0b0,0b100000100001000001000000000000000000000000000000}},
{0x4000000, {0b1000100001000100001000,0b100001000000000000000,0b100001000000000000000000000000000000,0b1000001000010000010000000000000000000000000000000}},
{0x8000000, {0b10001000010001000010000,0b1000010000010000100000,0b1000010001000010000000000000000000000000000000,0b10000010000100000100000000000000000000000000000000}},
{0x10000000, {0b100010000100000000000000,0b10000100000100001000001,0b10000100010000100000000000000000000000000000000,0b100001000001000000000000000000000000000000000}},
{0x20000000, {0b1000000000000000000000000,0b100001000001000010000010,0b100001000100001000000000000000000000000000000000,0b10000000000000000000000000000000000}},
{0x40000000, {0b100001000100001000100001000,0b10000000000000000000000000,0b100000000000000000000000000000000000,0b100000100001000000000000000000000000000000000000}},
{0x80000000, {0b1000010001000010001000010000,0b100000100001000000000000000,0b1000010001000000000000000000000000000000000000,0b1000001000010000000000000000000000000000000000000}},
{0x100000000, {0b10000100010000100000000000000,0b1000001000010000010000100000,0b10000100010000000000000000000000000000000000000,0b10000010000100000000000000000000000000000000000000}},
{0x200000000, {0b100001000000000000000000000000,0b10000010000100000100001000001,0b100001000100000000000000000000000000000000000000,0b100001000000000000000000000000000000000000000}},
{0x400000000, {0b0,0b100000100001000001000010000010,0b1000010001000000000000000000000000000000000000000,0b0}},
{0x800000000, {0b1000100001000100001000100001000,0b0,0b0,0b10000010000000000000000000000000000000000000000}},
{0x1000000000, {0b10001000010001000010001000010000,0b1000010000000000000000000000000,0b1000010000000000000000000000000000000000000000,0b100000100000000000000000000000000000000000000000}},
{0x2000000000, {0b100010000100010000100000000000000,0b10000100000100001000000000000000,0b10000100000000000000000000000000000000000000000,0b1000001000000000000000000000000000000000000000000}},
{0x4000000000, {0b1000100001000000000000000000000000,0b100001000001000010000010000100000,0b100001000000000000000000000000000000000000000000,0b10000010000000000000000000000000000000000000000000}},
{0x8000000000, {0b10000000000000000000000000000000000,0b1000010000010000100000100001000001,0b1000010000000000000000000000000000000000000000000,0b100000000000000000000000000000000000000000000}},
{0x10000000000, {0b1000010001000010001000010001000010000,0b100000000000000000000000000000000000,0b1000000000000000000000000000000000000000000000,0b10000000000000000000000000000000000000000000000}},
{0x20000000000, {0b10000100010000100010000100000000000000,0b1000001000010000000000000000000000000,0b10000000000000000000000000000000000000000000000,0b100000000000000000000000000000000000000000000000}},
{0x40000000000, {0b100001000100001000000000000000000000000,0b10000010000100000100001000000000000000,0b100000000000000000000000000000000000000000000000,0b1000000000000000000000000000000000000000000000000}},
{0x80000000000, {0b1000010000000000000000000000000000000000,0b100000100001000001000010000010000100000,0b1000000000000000000000000000000000000000000000000,0b10000000000000000000000000000000000000000000000000}},
{0x100000000000, {0b0,0b1000001000010000010000100000100001000001,0b10000000000000000000000000000000000000000000000000,0b0}},
{0x200000000000, {0b10001000010001000010001000010001000010000,0b0,0b0,0b0}},
{0x400000000000, {0b100010000100010000100010000100000000000000,0b10000100000000000000000000000000000000000,0b0,0b0}},
{0x800000000000, {0b1000100001000100001000000000000000000000000,0b100001000001000010000000000000000000000000,0b0,0b0}},
{0x1000000000000, {0b10001000010000000000000000000000000000000000,0b1000010000010000100000100001000000000000000,0b0,0b0}},
{0x2000000000000, {0b100000000000000000000000000000000000000000000,0b10000100000100001000001000010000010000100000,0b0,0b0}}
};
const std::map<u64, std::vector<u64>> Board::MASK_KING_ATTACK_WITHOUT_BORDER = {
  {0x1, {0b0,0b0,0b0,0b1000001000010000010000100000100001000000}},
  {0x2, {0b0,0b0,0b10001000000,0b100000100001000001000010000000}},
  {0x4, {0b0,0b0,0b100010000100010000000,0b10000010000100000000}},
  {0x8, {0b0,0b0,0b1000100001000100001000100000000,0b1000000000}},
  {0x10, {0b0,0b0,0b10001000010001000010001000010001000000000,0b0}},
  {0x20, {0b0,0b0,0b0,0b10000100000100001000001000010000010000000000}},
  {0x40, {0b0,0b0,0b10000000000,0b1000001000010000010000100000100000000000}},
  {0x80, {0b0,0b0,0b100010000100000000000,0b100000100001000001000000000000}},
  {0x100, {0b0,0b0,0b1000100001000100001000000000000,0b10000010000000000000}},
  {0x200, {0b0,0b0,0b10001000010001000010001000010000000000000,0b0}},
  {0x400, {0b1000000,0b0,0b0,0b10000100000100001000001000010000000000000000}},
  {0x800, {0b10000000,0b1000000,0b100010000000000000000,0b1000001000010000010000100000000000000000}},
  {0x1000, {0b100000000,0b10000000,0b1000100001000100000000000000000,0b100000100001000000000000000000}},
  {0x2000, {0b1000000000,0b100000000,0b10001000010001000010001000000000000000000,0b10000000000000000000}},
  {0x4000, {0b0,0b1000000000,0b100010000100010000100010000000000000000000,0b0}},
  {0x8000, {0b10001000000,0b0,0b0,0b1000010000010000100000100000000000000000000}},
  {0x10000, {0b100010000000,0b10000000000,0b100000000000000000000,0b10000100000100001000001000000000000000000000}},
  {0x20000, {0b1000100000000,0b100001000000,0b1000100001000000000000000000000,0b1000001000010000010000000000000000000000}},
  {0x40000, {0b10001000000000,0b1000010000000,0b10001000010001000010000000000000000000000,0b100000100000000000000000000000}},
  {0x80000, {0b0,0b10000100000000,0b100010000100010000100000000000000000000000,0b0}},
  {0x100000, {0b10000100010000000,0b0,0b0,0b1000010000010000100000000000000000000000000}},
  {0x200000, {0b100001000100000000,0b10000010000000000,0b1000100000000000000000000000000,0b10000100000100001000000000000000000000000000}},
  {0x400000, {0b1000010001000000000,0b100000100001000000,0b10001000010001000000000000000000000000000,0b1000001000010000000000000000000000000000}},
  {0x800000, {0b10000000000000000000,0b1000001000010000000,0b100010000100010000000000000000000000000000,0b100000000000000000000000000000}},
  {0x1000000, {0b0,0b10000010000100000000,0b1000100001000100000000000000000000000000000,0b0}},
  {0x2000000, {0b100010000100010000000,0b0,0b0,0b100001000001000000000000000000000000000000}},
  {0x4000000, {0b1000100001000100000000,0b100000000000000000000,0b1000000000000000000000000000000,0b1000010000010000000000000000000000000000000}},
  {0x8000000, {0b10001000010001000000000,0b1000010000010000000000,0b10001000010000000000000000000000000000000,0b10000100000100000000000000000000000000000000}},
  {0x10000000, {0b100010000000000000000000,0b10000100000100001000000,0b100010000100000000000000000000000000000000,0b1000001000000000000000000000000000000000}},
  {0x20000000, {0b0,0b100001000001000010000000,0b1000100001000000000000000000000000000000000,0b0}},
  {0x40000000, {0b100001000100001000100000000,0b0,0b0,0b100001000000000000000000000000000000000000}},
  {0x80000000, {0b1000010001000010001000000000,0b100000100000000000000000000,0b10001000000000000000000000000000000000000,0b1000010000000000000000000000000000000000000}},
  {0x100000000, {0b10000100010000000000000000000,0b1000001000010000010000000000,0b100010000000000000000000000000000000000000,0b10000100000000000000000000000000000000000000}},
  {0x200000000, {0b100000000000000000000000000000,0b10000010000100000100001000000,0b1000100000000000000000000000000000000000000,0b1000000000000000000000000000000000000000}},
  {0x400000000, {0b0,0b100000100001000001000010000000,0b10001000000000000000000000000000000000000000,0b0}},
  {0x800000000, {0b1000100001000100001000100000000,0b0,0b0,0b10000000000000000000000000000000000000000}},
  {0x1000000000, {0b10001000010001000010001000000000,0b1000000000000000000000000000000,0b10000000000000000000000000000000000000000,0b100000000000000000000000000000000000000000}},
  {0x2000000000, {0b100010000100010000000000000000000,0b10000100000100000000000000000000,0b100000000000000000000000000000000000000000,0b1000000000000000000000000000000000000000000}},
  {0x4000000000, {0b1000100000000000000000000000000000,0b100001000001000010000010000000000,0b1000000000000000000000000000000000000000000,0b10000000000000000000000000000000000000000000}},
  {0x8000000000, {0b0,0b1000010000010000100000100001000000,0b10000000000000000000000000000000000000000000,0b0}},
  {0x10000000000, {0b1000010001000010001000010001000000000,0b0,0b0,0b0}},
  {0x20000000000, {0b10000100010000100010000000000000000000,0b1000001000000000000000000000000000000,0b0,0b0}},
  {0x40000000000, {0b100001000100000000000000000000000000000,0b10000010000100000100000000000000000000,0b0,0b0}},
  {0x80000000000, {0b1000000000000000000000000000000000000000,0b100000100001000001000010000010000000000,0b0,0b0}},
  {0x100000000000, {0b0,0b1000001000010000010000100000100001000000,0b0,0b0}},
  {0x200000000000, {0b10001000010001000010001000010001000000000,0b0,0b0,0b0}},
  {0x400000000000, {0b100010000100010000100010000000000000000000,0b10000000000000000000000000000000000000000,0b0,0b0}},
  {0x800000000000, {0b1000100001000100000000000000000000000000000,0b100001000001000000000000000000000000000000,0b0,0b0}},
  {0x1000000000000, {0b10001000000000000000000000000000000000000000,0b1000010000010000100000100000000000000000000,0b0,0b0}},
  {0x2000000000000, {0b0,0b10000100000100001000001000010000010000000000,0b0,0b0}}
};
const u64 Board::BYTE_REVERSE[] = {
  0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
  0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
  0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
  0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
  0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
  0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
  0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
  0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
  0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
  0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
  0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
  0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
  0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
  0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
  0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
  0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
  0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
  0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
  0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
  0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
  0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
  0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
  0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
  0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
  0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
  0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
  0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
  0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
  0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
  0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
  0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
  0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};
const u8 Board::OPPOSITE_DIRECTIONS[] = {2, 3, 0, 1};

u64 Board::getMSB(u64 bitboard) {
  bitboard|=(bitboard>>1);
  bitboard|=(bitboard>>2);
  bitboard|=(bitboard>>4);
  bitboard|=(bitboard>>8);
  bitboard|=(bitboard>>16);
  bitboard|=(bitboard>>32);
  bitboard++;
  bitboard>>=1;
  return bitboard;
}
u64 Board::getLSB(u64 bitboard) {
  return bitboard&(~bitboard+1);
}
u64 Board::setRightSideOfMSB(u64 bitboard) {
  bitboard|=(bitboard>>1);
  bitboard|=(bitboard>>2);
  bitboard|=(bitboard>>4);
  bitboard|=(bitboard>>8);
  bitboard|=(bitboard>>16);
  bitboard|=(bitboard>>32);
  return bitboard;
}
u64 Board::setLeftSideOfMSB(u64 bitboard) {
  return ~Board::setRightSideOfMSB(bitboard);
}
u64 Board::setRightSideOfLSB(u64 bitboard) {
  return Board::getLSB(bitboard)-1;
}
u64 Board::setLeftSideOfLSB(u64 bitboard) {
  return ~Board::setLeftSideOfLSB(bitboard);
}
u64 Board::reverse(u64 n) {
  return Board::BYTE_REVERSE[n&0xff]<<56|Board::BYTE_REVERSE[(n>>8)&0xff]<<48|Board::BYTE_REVERSE[(n>>16)&0xff]<<40|Board::BYTE_REVERSE[(n>>24)&0xff]<<32|Board::BYTE_REVERSE[(n>>32)&0xff]<<24|Board::BYTE_REVERSE[(n>>40)]<<16|Board::BYTE_REVERSE[(n>>48)&0xff]<<8|Board::BYTE_REVERSE[(n>>56)&0xff];
}
u64 Board::getEmpty(Board::board state) {
  return (~(state.whiteMen|state.whiteKings|state.blackMen|state.blackKings))&Board::MASK_BOARD;
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
  }
  return bitboard;
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
  }
  return bitboard;
}
u64 Board::moveSquares(u64 bitboard, u8 direction) {
  return Board::moveEvenSquares(bitboard, direction)|Board::moveOddSquares(bitboard, direction);
}
u64 Board::getMenMovers(Board::board state, u8 direction) {
  std::vector<Board::move> movers;
  u64 empty = Board::MASK_MOVER_MEN[direction]&Board::getEmpty(state);
  u8 oppositeDirection = Board::OPPOSITE_DIRECTIONS[direction];
  return state.whiteMen&Board::moveSquares(empty, oppositeDirection);
}
u64 Board::getKingMoves(u64 king, Board::board state, u8 direction) {
  u64 empty = Board::getEmpty(state);
  u64 mask = Board::MASK_KING_ATTACK.at(king)[direction];
  u64 target = (~empty)&mask;
  if (direction <= 1)
    target = Board::setLeftSideOfMSB(target);
  else
    target = Board::setRightSideOfLSB(target);
  return target&mask;
}
std::vector<Board::move> Board::getKingsMovers(Board::board state, u8 direction) {
  std::vector<Board::move> moves;
  u64 kings = state.whiteKings;
  while (kings) {
    u64 king = Board::getLSB(kings);
    kings &= ~king;
    u64 landings = Board::getKingMoves(king, state, direction);
    while (landings) {
      u64 landing = Board::getLSB(landings);
      landings &= ~landing;
      Board::move mv = {{king, landing}, {0ULL, 0ULL}};
      moves.push_back(mv);
    }
  }
  return moves;
}
u64 Board::getJumperMen(Board::board state, u8 direction) {
  u64 jumpers = Board::getEmpty(state)&Board::MASK_JUMPER_MEN[direction];
  u8 oppositeDirection = Board::OPPOSITE_DIRECTIONS[direction];
  jumpers = Board::moveSquares(jumpers, oppositeDirection);
  jumpers &= state.blackMen|state.blackKings;
  jumpers = Board::moveSquares(jumpers, oppositeDirection);
  return jumpers&state.whiteMen;
}
Board::kingMoveChunk Board::getJumperKing (u64 king, Board::board state, u64 alreadyCaptured, u8 direction) {
  u64 black = state.blackMen|state.blackKings;
  state.blackMen |= alreadyCaptured;
  u64 empty = Board::getEmpty(state);
  u64 occupied = ~empty;
  u64 mask = Board::MASK_KING_ATTACK_WITHOUT_BORDER.at(king)[direction];
  u64 target = occupied&mask;
  if (target) {
    if (direction <= 1)
      target = Board::getMSB(target);
    else
      target = Board::getLSB(target);
    u64 next = Board::moveSquares(target, direction);
    if (target&black && next&empty) {
      std::vector<u64> landings = {next};
      while (next&mask) {
        next = Board::moveSquares(next, direction);
        if (next&occupied)
          break;
        landings.push_back(next);
      }
      Board::kingMoveChunk result = {king, target, landings};
      return result;
    }
  }
  throw std::invalid_argument("");
}
std::vector<Board::kingMoveChunk> Board::getJumperKings(Board::board state, u64 alreadyCaptured, u8 direction) {
  std::vector<Board::kingMoveChunk> data;
  u64 empty = Board::getEmpty(state);
  u64 whiteKings = state.whiteKings;
  while (whiteKings) {
    u64 king = Board::getLSB(whiteKings);
    whiteKings &= ~king;
    try {
      Board::kingMoveChunk kmc = Board::getJumperKing(king, state, alreadyCaptured, direction);
      data.push_back(kmc);
    } catch (const std::invalid_argument& e) {};
  }
  return data;
}
void Board::makeManMove(u64* man, Board::board* state, u8 direction) {
  state->whiteMen &= ~(*man);
  *man = Board::moveSquares(*man, direction);
  state->whiteMen |= *man;
}
u64 Board::makeManCapture(u64* man, Board::board* state, u8 direction) {
  Board::makeManMove(man, state, direction);
  u64 capture = *man;
  state->blackMen &= ~(capture);
  state->blackKings &= ~(capture);
  *man = Board::moveSquares(*man, direction);
  state->whiteMen |= *man;
  return capture;
}
void Board::makeKingMove(u64*king, Board::board* state, u64 landing) {
  state->whiteKings &= ~(*king);
  *king = landing;
  state->whiteKings |= *king;
}
void Board::makeKingCapture(u64*king, Board::board* state, u64 landing, u64 target) {
  state->blackMen &= ~target;
  state->blackKings &= ~target;
  Board::makeKingMove(king, state, landing);
}
void Board::calculateManCaptures(u64 man, Board::board state, u8 count, u8* n, Board::move mv, std::vector<Board::move>* found) {
  u64 jumpers[] = {
    Board::getJumperMen(state, 0),
    Board::getJumperMen(state, 1),
    Board::getJumperMen(state, 2),
    Board::getJumperMen(state, 3),
  };
  if (man&(jumpers[0]|jumpers[1]|jumpers[2]|jumpers[3])) {
    for (u8 i=0; i<4; i++) {
      if (!(man&jumpers[i]))
        continue;
      u64 _man = man;
      board _state = state;
      move _mv = mv;
      _mv.captures.push_back(Board::makeManCapture(&_man, &_state, i));
      _mv.positions.push_back(_man);
      Board::calculateManCaptures(_man, _state, count+1, n, _mv, found);
    }
  } else {
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(mv);
  }
}
std::vector<Board::move> Board::getMenCaptures(Board::board state, u8* depth) {
  u64 jumpers[] = {
    Board::getJumperMen(state, 0),
    Board::getJumperMen(state, 1),
    Board::getJumperMen(state, 2),
    Board::getJumperMen(state, 3),
  };
  std::vector<move> found;
  for (u8 i=0; i<4; i++) {
    if (!jumpers[i])
      continue;
    while (jumpers[i]) {
      u64 man = Board::getLSB(jumpers[i]);
      u64 _man = man;
      jumpers[i] &= ~_man;
      board _state = state;
      u64 capture = Board::makeManCapture(&_man, &_state, i);
      move _mv = {{man, _man}, {capture}};
      Board::calculateManCaptures(_man, _state, 0, depth, _mv, &found);
    }
  }
  return found;
}
void Board::calculateKingCaptures(u64 king, Board::board state, u64 alreadyCaptured, u8 count, u8* n, Board::move mv, std::vector<Board::move>* found) {
  std::vector<kingMoveChunk> jumperKings;
  for (u8 i=0; i<4; i++) {
    try {
      jumperKings.push_back(Board::getJumperKing(king, state, alreadyCaptured, i));
    } catch (const std::invalid_argument& e) {};
  }
  if (jumperKings.size() == 0) {
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(mv);
  } else {
    for (auto& jumperKing : jumperKings) {
      for (auto& landing : jumperKing.landing) {
        u64 _king = king;
        board _state = state;
        u64 _alreadyCaptured = alreadyCaptured|jumperKing.capture;
        Board::makeKingCapture(&_king, &_state, landing, jumperKing.capture);
        Board::move _mv = mv;
        _mv.positions.push_back(_king);
        _mv.captures.push_back(jumperKing.capture);
        Board::calculateKingCaptures(_king, _state, _alreadyCaptured, count+1, n, _mv, found);
      }
    }
  }
}
std::vector<Board::move> Board::getKingsCaptures(Board::board state, u8* depth) {
  std::vector<kingMoveChunk> jumperKings[] = {
    Board::getJumperKings(state, 0ULL, 0),
    Board::getJumperKings(state, 0ULL, 1),
    Board::getJumperKings(state, 0ULL, 2),
    Board::getJumperKings(state, 0ULL, 3)
  };
  std::vector<move> found;
  for (u8 i=0; i<4; i++) {
    for (auto& jumperKing : jumperKings[i]) {
      for (auto& landing : jumperKing.landing) {
        u64 _king = jumperKing.from;
        board _state = state;
        Board::makeKingCapture(&_king, &_state, landing, jumperKing.capture);
        u64 _alreadyCaptured = jumperKing.capture;
        move _mv = {{jumperKing.from, _king}, {jumperKing.capture}};
        Board::calculateKingCaptures(_king, _state, _alreadyCaptured, 0, depth, _mv, &found);
      }
    }
  }
  return found;
}

//public
Board::board Board::getState() {
  return this->state;
}
u64 Board::getWhiteMen() {
  return this->state.whiteMen;
}
u64 Board::getWhiteKings() {
  return this->state.whiteKings;
}
u64 Board::getBlackMen() {
  return this->state.blackMen;
}
u64 Board::getBlackKings() {
  return this->state.blackKings;
}
bool Board::getPlayerToMove() {
  return this->playerToMove;
}
void Board::setState(Board::board state) {
  this->state = state;
}
void Board::setWhiteMen(u64 whiteMen) {
  this->state.whiteMen = whiteMen;
}
void Board::setWhiteKings(u64 whiteKings) {
  this->state.whiteKings = whiteKings;
}
void Board::setBlackMen(u64 blackMen) {
  this->state.blackMen = blackMen;
}
void Board::setBlackKings(u64 blackKings) {
  this->state.blackKings = blackKings;
}
void Board::setPlayerToMove(bool playerToMove) {
  this->playerToMove = playerToMove;
}
Board::board Board::getPlayerState(bool player) {
  Board::board state = this->state;
  if (player) {
    state.whiteMen = Board::reverse(this->state.blackMen);
    state.whiteKings = Board::reverse(this->state.blackKings);
    state.blackMen = Board::reverse(this->state.whiteMen);
    state.blackKings = Board::reverse(this->state.whiteKings);
  }
  return state;
}
std::vector<Board::move> Board::getLegalPushes() {
  Board::board state = Board::getPlayerState(this->playerToMove);
  std::vector<Board::move> pushes;
  for (u8 i=0; i<4; i++) {
    u64 bitboard = Board::getMenMovers(state, i);
    while (bitboard) {
      u64 mover = Board::getLSB(bitboard);
      bitboard &= ~mover;
      u64 landing = Board::moveSquares(mover, i);
      Board::move mv = {{mover, landing}, {0ULL}};
      pushes.push_back(mv);
    }
    std::vector<Board::move> kingsPushes = Board::getKingsMovers(state, i);
    pushes.insert(pushes.end(), kingsPushes.begin(), kingsPushes.end());
  }
  return pushes;
}
std::vector<Board::move> Board::getLegalCaptures() {
  Board::board state = Board::getPlayerState(this->playerToMove);
  u8 depth = 0;
  std::vector<Board::move> kings = Board::getKingsCaptures(state, &depth);
  std::vector<Board::move> men = Board::getMenCaptures(state, &depth);
  men.insert(men.end(), kings.begin(), kings.end());
  return men;
}
std::vector<Board::move> Board::getLegalMoves() {
  std::vector<Board::move> captures = Board::getLegalCaptures();
  if (captures.size())
    return captures;
  return Board::getLegalPushes();
}
void Board::makeMove(Board::move mv) {
  Board::board state = Board::getPlayerState(this->playerToMove);
  u64 from = mv.positions.from();
  u64 to = mv.positions.back();
  if (state.whiteMen&from) {
    state.whiteMen &= ~from;
    state.whiteMen |= to;
  } else {
    state.whiteKings &= ~from;
    state.whiteKings |= to;
  }
  u64 sum = 0;
  for (auto& capture : mv.captures)
    sum |= capture;
  state.blackMen &= ~sum;
  state.blackKings &= ~sum;
  this->state = state;
  this->history.push_back(state);
  this->playerToMove = !this->playerToMove;
}
u8 Board::getResult() {
  u8 count = 0;
  for (auto& position : this->history) {
    if (position == this->state)
      count++;
    if (count == 3)
      return 0;
  }
  std::vector<Board::move> moves = this->getLegalMoves();
  if (moves.size() == 0)
    return this->playerToMove ? -1 : 1;
  this->setPlayerToMove(!this->playerToMove);
  moves = this->getLegalMoves();
  this->setPlayerToMove(!this->playerToMove)
  if (moves.size() == 0)
    return this->playerToMove ? 1 : -1;
  return NULL;

}
