#include "../include/Board.hpp"
//private
u64 Board::state = { 0ULL, 0ULL, 0ULL, 0ULL };
bool Board::playerToMove = 0;

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
u64 Board::getEmpty(board state) {
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
u64 Board::getMenMovers(board state, u8 direction) {
  u64 empty = Board::MASK_MOVER_MEN[direction]&Board::getEmpty(state);
  u8 oppositeDirection = Board::OPPOSITE_DIRECTIONS[direction];
  u64 movers = state.whiteMen&Board::moveSquares(empty, oppositeDirection);
  return movers;
}
u64 Board::getKingMoves(u64 king, board state, u8 direction) {
  u64 empty = Board::getEmpty(state);
  u64 mask = Board::MASK_KING_ATTACK.at(king)[direction];
  u64 target = (~empty)&mask;
  if (direction <= 1)
    target = Board::setLeftSideOfMSB(target);
  else
    target = Board::setRightSideOfLSB(target);
  return target&mask;
}
std::vector<moves> Board::getKingsMovers(board state, u8 direction) {
  std::vector<moves> moves;
  u64 kings = state.whiteKings;
  while (kings) {
    u64 king = Board::getLSB(kings);
    kings &= ~x;
    u64 landings = Board::getKingMoves(king, state, direction);
    while (landings) {
      u64 landing = Board::getLSB(landings);
      landings &= ~landing;
      move mv = {{king, landing}, {0ULL, 0ULL}};
      moves.push_back(mv);
    }
  }
  return moves;
}
u64 Board::getJumperMen(board state, u8 direction) {
  u64 jumpers = Board::getEmpty(state)&Board::MASK_JUMPER_MEN[direction];
  u8 oppositeDirection = Board::OPPOSITE_DIRECTIONS[direction];
  jumpers = Board::moveSquares(jumpers, oppositeDirection);
  jumpers &= state.blackMen|state.blackKings;
  jumpers = Board::moveSquares(jumpers, oppositeDirection);
  return jumpers&state.whiteMen;
}
kingMoveChunk Board::getJumperKing (u64 king, board state, u64 alreadyCaptured, u8 direction) {
  u64 empty = Board::getEmpty(state);
  u64 mask = Board::MASK_KING_ATTACK_WITHOUT_BORDER.at(king)[direction];
  u64 black = (state.blackMen|state.blackKings)
  u64 target = black&mask;
  if (target) {
    if (direction <= 1)
      target = Board::getMSB(target);
    else
      target = Board::getLSB(target);
    if (target&black&(~alreadyCaptured)) {
      u64 landing = Board::setRightSideOfMSB(target)&empty&mask;
      std::vector<u64> landings = {};
      while (landing) {
        u64 x = Board::getLSB(landing);
        landing &= ~x;
        landings.push_back(x);
      }
      if (landings.size()) {
        kingMoveChunk result = {king, target, landings};
        return result;
      }
    }
  }
  throw std::invalid_argument("");
}
std::vector<kingMoveChunk> Board::getJumperKings(board state, u64 alreadyCaptured, u8 direction) {
  std::vector<kingMoveChunk> data;
  u64 empty = Board::getEmpty(state);
  u64 whiteKings = state.whiteKings;
  while (whiteKings) {
    u64 king = Board::getLSB(whiteKings);
    whiteKings &= ~king;
    try {
      kingMoveChunk kmc = Board::getJumperKing(king, state, alreadyCaptured, direction);
      data.push_back(kmc);
    } catch (const std::invalid_argument& e) {};
  }
  return data;
}
void Board::init(board state, bool playerToMove) {
  Board::state = state;
  Board::playerToMove = playerToMove;
}
void Board::makeManMove(u64* man, board* state, u8 direction) {
  state->whiteMen &= ~(*man);
  *man = Board::moveSquares(*man, direction);
  state->whiteMen |= *man;
}
void Board::makeManCapture(u64* man, board* state, u8 direction) {
  Board::makeManMove(man, state, direction);
  state->blackMen &= ~(*man);
  state->blackKings &= ~(*man);
  *man = Board::moveSquares(*man, direction);
  state->blackMen |= *man;
}
void Board::makeKingMove(u64*king, board* state, u64 landing) {
  state->whiteKings &= ~(*king);
  *king = landing;
  state->whiteKings |= *king;
}
void Board::makeKingCapture(u64*king, board* state, u64 landing, u64 target) {
  state->blackMen &= ~target;
  state->blackKings &= ~target;
  Board::makeKingMove(king, state, landing);
}
void Board::calculateManCaptures(u64 man, board state, u8 count, u8* n, std::vector<u64> moves, std::vector<std::vector<u64>>* found) {
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
      std::vector<u64> _moves = moves;
      Board::makeManCapture(&_man, &_state, i);
      mv.push_back(_man);
      Board::calculateManCaptures(_man, _state, count+1, n, _moves, found);
    }
  } else {
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(moves);
  }
}
std::vector<std::vector<u64>> Board::getMenCaptures(board state) {
  u64 jumpers[] = {
    Board::getJumperMen(state, 0),
    Board::getJumperMen(state, 1),
    Board::getJumperMen(state, 2),
    Board::getJumperMen(state, 3),
  };
  u8 n = 0;
  std::vector<std::vector<u64>> found;
  for (u8 i=0; i<4; i++) {
    if (!jumpers[i])
      continue;
    while (jumpers[i]) {
      u64 _man = Board::getLSB(jumpers[i]);
      jumpers[i] &= ~x;
      board _state = state;
      std::vector<u64> move = {_man};
      Board::makeManCapture(&_man, &_state, i);
      move.push_back(x);
      Board::calculateManCaptures(_man, _state, 0, &n, move, &found);
    }
  }
  return found;
}
void Board::calculateKingCaptures(u64 king, u64 state, u64 alreadyCaptured, u8 count, u8* n, std::vector<u64> moves, std::vector<std::vector<u64>>* found) {
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
      found->push_back(moves);
  } else {
    for (auto& jumperKing : jumperKings) {
      for (auto& landing : jumperKing.landing) {
        u64 _king = king;
        board _state = state;
        u64 _alreadyCaptured = alreadyCaptured|jumperKing.capture;
        Board::makeKingMove(&x, &state, landing);
        std::vector<u64> _moves = moves;
        _moves.push_back(_king);
        Board::calculateKingCaptures(_king, _state, _alreadyCaptured, count+1, n, _moves, found);
      }
    }
  }
}
std::vector<move> Board::getKingsCaptures(u64 state) {
  std::vector<kingMoveChunk> jumperKings[] = {
    Board::getJumperKings(state, 0ULL, 0),
    Board::getJumperKings(state, 0ULL, 1),
    Board::getJumperKings(state, 0ULL, 2),
    Board::getJumperKings(state, 0ULL, 3)
  };
  u8 n = 0;
  std::vector<move> found;
  u64 x = 0;
  u64 wm = 0;
  u64 wk = 0;
  u64 bm = 0;
  u64 bk = 0;
  u64 bmAfter = 0;
  u64 bkAfter = 0;
  for (u8 i=0; i<4; i++) {
    std::cout << "Jumper kings size " << jumperKings[i].size() << std::endl;
    for (auto& jumperKing : jumperKings[i]) {
      std::cout << ">>>>>>>Jumper king data: " << std::endl;
      std::cout << "from: " << jumperKing.from << std::endl;
      std::cout << "capture: " << jumperKing.capture << std::endl;
      std::cout << "landing size: " << jumperKing.landing.size() << std::endl;
      for (auto& landing : jumperKing.landing) {
        std::cout << "Checking landing: " << landing << std::endl;
        x = jumperKing.from;
        wm = whiteMen;
        wk = whiteKings;
        bm = blackMen;
        bk = blackKings;
        bmAfter = blackMen;
        bkAfter = blackKings;
        std::cout << "Before capture: " << x << std::endl;
        std::vector<u64> move = {x};
        Board::makeKingCapture(&x, &wk, &bmAfter, &bkAfter, landing, jumperKing.capture);
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << bmAfter << std::endl;
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << bkAfter << std::endl;
        move.push_back(x);
        std::cout << "After capture: " << x << std::endl;
        // branch = root->addChild(landing);
        Board::calculateKingCaptures(x, wm, wk, bm, bk, 0, &n, move, &found, bmAfter, bkAfter);
      }
    }
  }
  return found;
}

std::vector<move> getLegalMoves(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings) {
  std::vector<move> moves;
  std::vector<std::vector<u64>> captures[] {
    Board::getMenCaptures(whiteMen, whiteKings, blackMen, blackKings),
    Board::getKingsCaptures(whiteMen, whiteKings, blackMen, blackKings)
  };
  if (captures[0].size() && captures[1].size()) {
    for (auto& capture: captures[0]) {
      move_struct m = {capture[0], capture[1], 0ULL}
    }
  }
}

u64 Board::getWhiteMen() {
  return Board::whiteMen;
}
u64 Board::getWhiteKings() {
  return Board::whiteKings;
}
u64 Board::getBlackMen() {
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
