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
u64 Board::getJumperMen(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  u64 tmp = Board::getEmpty(whiteMen, whiteKings, blackMen, blackKings)&Board::MASK_JUMPER_MEN_BORDER[direction];
  u8 oppositeDirection = Board::JUMPER_MEN_OPPOSITE_DIRECTIONS[direction];
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);

  tmp &= blackMen|blackKings;
  tmp = moveEvenSquares(tmp, oppositeDirection)|moveOddSquares(tmp, oppositeDirection);
  tmp &= whiteMen;
  return tmp;
}
std::vector<kingMoveChunk> Board::getJumperKings(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 direction) {
  std::vector<kingMoveChunk> data;
  u64 occupied = (whiteMen|whiteKings|blackMen|blackKings)&Board::MASK_BOARD;
  u64 empty = (~occupied)&Board::MASK_BOARD;
  u64 x = 0;
  u64 target = 0;
  u64 landing = 0;
  while (whiteKings) {
    x = Board::getLSB(whiteKings);
    whiteKings &= ~x;
    target = (blackMen|blackKings)&Board::MASK_KING_ATTACK.at(x)[direction];
    if (!target)
      continue;
    if (direction <= 1)
      target = Board::getLSB(target);
    else
      target = Board::getMSB(target);
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
      kingMoveChunk kmc = {x, target, tmp};
      data.push_back(kmc);
    }
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
void Board::calculateManCaptures(u64 man, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, Node* tree, std::vector<Node*>* found) {
  u64 jumpers[] = {
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3),
  };
  std::cout << "Man before if " << man << std::endl;
  if (!(man&(jumpers[0]|jumpers[1]|jumpers[2]|jumpers[3]))) {
    std::cout << "calculation has finished with count: " << (int)count << std::endl;
    std::cout << "curremt n: " << (int)(*n) << std::endl;
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(tree);
  } else {
    for (u8 i=0; i<4; i++) {
      if (!(man&jumpers[i]))
        continue;
      Board::makeManCapture(&man, &whiteMen, &blackMen, &blackKings, i);
      Node* branch = tree->addChild(man);
      Board::calculateManCaptures(man, whiteMen, whiteKings, blackMen, blackKings, count+1, n, branch, found);
    }
  }
}
void Board::getMenCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, std::vector<std::vector<u64>*>* captures) {
  u64 jumpers[] = {
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3),
  };

  u8 n = 0;
  std::vector<Node*> found;
  std::vector<Node*> trees;
  u64 x = 0;
  u64 wm = 0;
  u64 wk = 0;
  u64 bm = 0;
  u64 bk = 0;
  Node* root;
  Node* branch;
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
      root = new Node(x);
      trees.push_back(root);
      Board::makeManCapture(&x, &wm, &bm, &bk, i);
      branch = root->addChild(x);
      Board::calculateManCaptures(x, wm, wk, bm, bk, 0, &n, branch, &found);
    }
  }
  std::cout << "size of found " << found.size() << std::endl;
  for (auto& node : found) {
    std::vector<u64>* moves = new std::vector<u64>;
    node->populate(moves);
    captures->push_back(moves);
  }
}
void Board::calculateKingCaptures(u64 king, u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, u8 count, u8* n, Node* tree, std::vector<Node*>* found) {
  std::vector<kingMoveChunk> jumperKings[] = {
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 3)
  };
  if (jumperKings[0].empty() && jumperKings[1].empty() && jumperKings[2].empty() && jumperKings[3].empty()) {
    if (count > *n) {
      *n = count;
      found->clear();
    }
    if (count == *n)
      found->push_back(tree);
  } else {
    for (u8 i=0; i<4; i++) {
      if (jumperKings[i].empty())
        continue;
      u64 wm = 0;
      u64 wk = 0;
      u64 bm = 0;
      u64 bk = 0;
      for (auto& jumperKing : jumperKings[i]) {
        for (auto& landing : jumperKing.landing) {
          wm = whiteMen;
          wk = whiteKings;
          bm = blackMen;
          bk = blackKings;
          Board::makeKingCapture(&(jumperKing.from), &wk, &bm, &bk, landing, jumperKing.capture);
          Node* branch = tree->addChild(landing);
          Board::calculateKingCaptures(jumperKing.from, wm, wk, bm, bk, count+1, n, branch, found);
        }
      }
    }
  }
}
void Board::getKingsCaptures(u64 whiteMen, u64 whiteKings, u64 blackMen, u64 blackKings, std::vector<std::vector<u64>*>* captures) {
  std::vector<kingMoveChunk> jumperKings[] = {
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getJumperKings(whiteMen, whiteKings, blackMen, blackKings, 3)
  };
  u8 n = 0;
  std::vector<Node*> found;
  std::vector<Node*> trees;
  u64 wm = 0;
  u64 wk = 0;
  u64 bm = 0;
  u64 bk = 0;
  Node* root;
  Node* branch;
  for (u8 i=0; i<4; i++) {
    for (auto& jumperKing : jumperKings[i]) {
      for (auto& landing : jumperKing.landing) {
        wm = whiteMen;
        wk = whiteKings;
        bm = blackMen;
        bk = blackKings;
        root = new Node(jumperKing.from);
        trees.push_back(root);
        Board::makeKingCapture(&(jumperKing.from), &wk, &bm, &bk, landing, jumperKing.capture);
        branch = root->addChild(landing);
        Board::calculateKingCaptures(jumperKing.from, wm, wk, bm, bk, 0, &n, branch, &found);
      }
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
