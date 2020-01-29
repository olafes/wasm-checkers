#include "../include/Board.hpp"
//private
u64 Board::whiteMen = 0ULL;
u64 Board::whiteKings = 0ULL;
u64 Board::blackMen = 0ULL;
u64 Board::blackKings = 0ULL;
bool Board::playerToMove = 0;

const u64 Board::MASK_JUMPER_MEN_BORDER[] = {
  0b00000000001111011110111101111011110111101111011110,
  0b00000000000111101111011110111101111011110111101111,
  0b01111011110111101111011110111101111011110000000000,
  0b11110111101111011110111101111011110111100000000000
};
const u64 Board::MASK_MOVER_MEN_BORDER[] = {
  0b0000000000000011111000000000100000000010000000001000000000100000,
  0b0000000000000011111100000000010000000001000000000100000000010000,
  0b0000000000000000000100000000010000000001000000000100000000011111,
  0b0000000000000000001000000000100000000010000000001000000000111111
};
const u64 Board::MASK_BORDER[] = {
  0b0000000000000000000100000000010000000001000000000100000000011111,
  0b0000000000000000001000000000100000000010000000001000000000111111,
  0b0000000000000011111000000000100000000010000000001000000000100000,
  0b0000000000000011111100000000010000000001000000000100000000010000
};

const std::map<u64, std::vector<u64>> Board::MASK_KING_ATTACK = {
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
const u8 Board::JUMPER_MEN_OPPOSITE_DIRECTIONS[] = {2, 3, 0, 1};

u64 Board::clearRightOfMSB(u64 bitboard) {
  u64 x = bitboard;
  bitboard|=(bitboard>>1);
  bitboard|=(bitboard>>2);
  bitboard|=(bitboard>>4);
  bitboard|=(bitboard>>8);
  bitboard|=(bitboard>>16);
  bitboard|=(bitboard>>32);
  return x&(~bitboard);
}
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
u64 Board::getMenMovers(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  u64 empty = (~Board::MASK_MOVER_MEN_BORDER[direction])&Board::getEmpty(whiteMen, whiteKings, blackMen, blackKings);
  // std::cout << "men empty: " << empty << std::endl;
  u8 oppositeDirection = Board::JUMPER_MEN_OPPOSITE_DIRECTIONS[direction];
  // std::cout << "opposite "
  u64 movers = whiteMen&(Board::moveEvenSquares(empty, oppositeDirection)|Board::moveOddSquares(empty, oppositeDirection));
  return movers;
}
u64 Board::getKingMoves(u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  u64 empty = Board::getEmpty(whiteMen, whiteKings, blackMen, blackKings);
  // u64 occupied = (~empty)&Board::MASK_KING_ATTACK.at(king)[direction];
  u64 mask = Board::MASK_KING_ATTACK.at(king)[direction];
  u64 target = (~empty)&mask;
  std::cout << "found target bitboard " << target << std::endl;
  if (direction <= 1) {
    target|=(target>>1);
    target|=(target>>2);
    target|=(target>>4);
    target|=(target>>8);
    target|=(target>>16);
    target|=(target>>32);
    target = (~target)&mask;
  } else {
    target = Board::getLSB(target)-1;
    target &= mask;
  }
  std::cout << "after target " << target << std::endl;
  return target;
}
std::vector<kingMoveChunk> Board::getKingsMovers(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  std::vector<kingMoveChunk> kingsMovers;
  u64 x = 0;
  u64 wk = whiteKings;
  while (wk) {
    x = Board::getLSB(wk);
    std::cout << (int)direction << " calculating king: " << x << std::endl;
    wk &= ~x;
    u64 landingBitboard = Board::getKingMoves(x, whiteMen, whiteKings, blackMen, blackKings, direction);
    std::vector<u64> landing;
    u64 y = 0;
    while (landingBitboard) {
      y = Board::getLSB(landingBitboard);
      landingBitboard &= ~y;
      landing.push_back(y);
    }
    kingMoveChunk kmc = {x, 0ULL, landing};
    kingsMovers.push_back(kmc);
  }
  return kingsMovers;
}
u64 Board::getJumperMen(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  u64 tmp = Board::getEmpty(whiteMen, whiteKings, blackMen, blackKings)&Board::MASK_JUMPER_MEN_BORDER[direction];
  u8 oppositeDirection = Board::JUMPER_MEN_OPPOSITE_DIRECTIONS[direction];
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);

  tmp &= blackMen|blackKings;
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);
  tmp &= whiteMen;
  return tmp;
}
kingMoveChunk Board::getJumperKing (u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction, u64 blackMenAfterCapture, u64 blackKingsAfterCapture) {
  u64 occupied = (whiteMen|whiteKings|blackMen|blackKings)&Board::MASK_BOARD;
  u64 empty = (~occupied)&Board::MASK_BOARD;
  u64 target = 0;
  u64 landing = 0;
  target = ((blackMen)|(blackKings))&Board::MASK_KING_ATTACK.at(king)[direction];
  if (target) {
    if (direction <= 1)
      target = Board::getMSB(target);
    else
      target = Board::getLSB(target);
    if (target&(blackMenAfterCapture|blackKingsAfterCapture)) {
      landing = Board::moveEvenSquares(target, direction)|Board::moveOddSquares(target, direction);
      if (landing&empty) {
        std::vector<u64> tmp = {landing};
        u64 BORDER = Board::MASK_BORDER[direction];
        while (!(landing&BORDER)) {
          landing = Board::moveEvenSquares(landing, direction)|Board::moveOddSquares(landing, direction);
          if (!(landing&empty))
            break;
          tmp.push_back(landing);
        }
        kingMoveChunk kmc = {king, target, tmp};
        return kmc;
      }
    }
  }
  throw std::invalid_argument("");
}
std::vector<kingMoveChunk> Board::getJumperKings(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction, u64 blackMenAfterCapture, u64 blackKingsAfterCapture) {
  std::vector<kingMoveChunk> data;
  u64 occupied = (whiteMen|whiteKings|blackMen|blackKings)&Board::MASK_BOARD;
  u64 empty = (~occupied)&Board::MASK_BOARD;
  u64 x = 0;
  u64 target = 0;
  u64 landing = 0;
  u64 wk = whiteKings;
  while (wk) {
    x = Board::getLSB(wk);
    wk &= ~x;
    try {
      kingMoveChunk kmc = Board::getJumperKing(x, whiteMen, whiteKings, blackMen, blackKings, direction, blackMenAfterCapture, blackKingsAfterCapture);
      data.push_back(kmc);
    } catch (const std::invalid_argument& e) {};
  }
  return data;
}

void Board::init(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, bool playerToMove) {
  Board::whiteMen = whiteMen;
  Board::whiteKings = whiteKings;
  Board::blackMen = blackMen;
  Board::blackKings = blackKings;
  Board::playerToMove = playerToMove;
}
void Board::makeManMove(u64* man, u64* whiteMen, u8 direction) {
  *whiteMen &= ~(*man);
  *man = Board::moveEvenSquares(*man, direction)|Board::moveOddSquares(*man, direction);
  *whiteMen |= *man;
}
void Board::makeManCapture(u64* man, u64* whiteMen, u64* blackMen, u64* blackKings, u8 direction) {
  Board::makeManMove(man, whiteMen, direction);
  *blackMen &= ~(*man);
  *blackKings &= ~(*man);
  *man = Board::moveEvenSquares(*man, direction)|Board::moveOddSquares(*man, direction);
  *whiteMen |= *man;
}
void Board::makeKingMove(u64*king, u64* whiteKings, u64 landing) {
  *whiteKings &= ~(*king);
  *king = 0ULL|landing;
  *whiteKings |= *king;
}
void Board::makeKingCapture(u64*king, u64* whiteKings, u64* blackMen, u64* blackKings, u64 landing, u64 target) {
  *blackMen &= ~target;
  *blackKings &= ~target;
  Board::makeKingMove(king, whiteKings, landing);
}
void Board::calculateManCaptures(u64 man, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, std::vector<u64> move, std::vector<std::vector<u64>>* found) {
  u64 jumpers[] = {
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3),
  };
  std::cout << "calculating caprues for position " << man << std::endl;
  std::cout << "---------- jumper men in 4 directions ----------" << std::endl;
  std::cout << jumpers[0] << std::endl;
  std::cout << jumpers[1] << std::endl;
  std::cout << jumpers[2] << std::endl;
  std::cout << jumpers[3] << std::endl;
  if (!(man&(jumpers[0]|jumpers[1]|jumpers[2]|jumpers[3]))) {
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(move);
  } else {
    u64 x = 0;
    u64 wm = 0;
    u64 wk = 0;
    u64 bm = 0;
    u64 bk = 0;
    for (u8 i=0; i<4; i++) {
      std::cout << "at position: " << man << std::endl;
      std::cout << "looking in direction: " << (int)i << std::endl;
      std::cout << "jumper at that direction " << jumpers[i] << std::endl;
      if (!(man&jumpers[i]))
        continue;
      std::cout << "found possible capture in direction: "<< (int)i << std::endl;
      x = man;
      wm = whiteMen;
      wk = whiteKings;
      bm = blackMen;
      bk = blackKings;
      std::vector<u64> mv = move;
      Board::makeManCapture(&x, &wm, &bm, &bk, i);
      mv.push_back(x);
      Board::calculateManCaptures(x, wm, wk, bm, bk, count+1, n, mv, found);
    }
  }
}
std::vector<std::vector<u64>> Board::getMenCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings) {
  u64 jumpers[] = {
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3),
  };

  u8 n = 0;
  std::vector<std::vector<u64>> found;
  u64 x = 0;
  u64 wm = 0;
  u64 wk = 0;
  u64 bm = 0;
  u64 bk = 0;
  for (u8 i=0; i<4; i++) {
    if (!jumpers[i])
      continue;
    while (jumpers[i]) {
      std::cout << "=================================================" << std::endl;
      x = Board::getLSB(jumpers[i]);
      std::cout << "Calculation started for " << x << std::endl;
      jumpers[i] &= ~x;
      wm = whiteMen;
      wk = whiteKings;
      bm = blackMen;
      bk = blackKings;
      std::vector<u64> move = {x};
      Board::makeManCapture(&x, &wm, &bm, &bk, i);
      move.push_back(x);
      Board::calculateManCaptures(x, wm, wk, bm, bk, 0, &n, move, &found);
    }
  }
  return found;
}
void Board::calculateKingCaptures(u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, std::vector<u64> move, std::vector<std::vector<u64>>* found, u64 blackMenAfterCapture, u64 blackKingsAfterCapture) {
  std::cout << "calculation started for: " << king << std::endl;
  std::vector<kingMoveChunk> jumperKings;
  for (u8 i=0; i<4; i++) {
    try {
      jumperKings.push_back(Board::getJumperKing(king, whiteMen, whiteKings, blackMen, blackKings, i, blackMenAfterCapture, blackKingsAfterCapture));
    } catch (const std::invalid_argument& e) {};
  }
  std::cout << "found caprues in " << jumperKings.size() << " directions" << std::endl;
  if (jumperKings.size() == 0) {
    std::cout << "==================calculation has finished with count: " << (int)count << std::endl;
    std::cout << "==================current n: " << (int)*n << std::endl;
    if (count > *n) {
      std::cout << "######################################## clearning found " << std::endl;
      *n = count;
      found->clear();
    }
    if (count == *n) {
      std::cout << "##### adding to found vector with size: " << move.size() << std::endl;
      found->push_back(move);
    }
  } else {
    for (auto& jumperKing : jumperKings) {
      u64 x = 0;
      u64 wm = 0;
      u64 wk = 0;
      u64 bm = 0;
      u64 bk = 0;
      u64 bkAfter = 0;
      u64 bmAfter = 0;
      for (auto& landing : jumperKing.landing) {
        x = jumperKing.from;
        wm = whiteMen;
        wk = whiteKings;
        bm = blackMen;
        bk = blackKings;
        bmAfter = blackMenAfterCapture;
        bkAfter = blackKingsAfterCapture;
        std::cout << "Making cpature on " << jumperKing.capture << std::endl;
        std::cout << "Landing on " << landing << std::endl;
        Board::makeKingCapture(&x, &wk, &bmAfter, &bkAfter, landing, jumperKing.capture);
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << bmAfter << std::endl;
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << bkAfter << std::endl;
        std::vector<u64> mv = move;
        mv.push_back(x);
        Board::calculateKingCaptures(x, wm, wk, bm, bk, count+1, n, mv, found, bmAfter, bkAfter);
      }
    }
  }
}
std::vector<std::vector<u64>> Board::getKingsCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings) {
  std::vector<kingMoveChunk> jumperKings[] = {
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 0, blackMen, blackKings),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 1, blackMen, blackKings),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 2, blackMen, blackKings),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 3, blackMen, blackKings)
  };
  u8 n = 0;
  std::vector<std::vector<u64>> found;
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
