#include <iostream>
#include "./include/Board.hpp"

typedef char u8;
typedef unsigned long long int u64;

extern "C" {
  void init(u8 whiteMen[],
      u8 whiteMenLength,
      u8 whiteKings[],
      u8 whiteKingsLength,
      u8 blackMen[],
      u8 blackMenLength,
      u8 blackKings[],
      u8 blackKingsLength,
      bool playerToMove);
  u8* getWhiteMen();
  u8* getWhiteKings();
  u8* getBlackMen();
  u8* getBlackKings();
  bool getPlayerToMove();
  void setWhiteMen(u8 whiteMen[], u8 whiteMenLength);
  void setWhiteKings(u8 whiteKings[], u8 whiteKingsLength);
  void setBlackMen(u8 blackMen[], u8 blackMenLength);
  void setBlackKings(u8 blackKings[], u8 blackKingsLength);
  void setPlayerToMove(bool playerToMove);
  bool isLegalMove(u8 chunks[], u8 chunksLength);
  u8* getLegalMoves();
  u8* getLegalMovesFor(u8 from);
  void move(u8 chunks[], u8 chunksLength);
  u8 getResult();
};

int main() {
  // u64 x = 2ULL;
  // u64 y = Board::moveEvenSquares(x, 2);
  // u64 z = Board::moveOddSquares(x, 2);
  // std::cout << x << " " <<  y << " " << z << std::endl;


  // 1111011110111101111011110111101110011110



  u64 whiteMen = 0b0000000000000000000000000000000000000000000000010011000000000000;
  u64 whiteKings = 0b0000000000000000000000000000000000000000000000000000000000000000;
  u64 blackMen = 0b0000000000000000000000000000000100000000001000000000001011000000;
  u64 blackKings = 0b0000000000000000000000000000000000000000000000000000000000000000;
  std::vector<std::vector<u64>*> captures;
  Board::getMenCaptures(whiteMen, whiteKings, blackMen, blackKings, &captures);
  for (auto& capture : captures) {
    std::cout << "capture" << std::endl;
    for (auto& move : *capture) {
      std::cout << move << std::endl;
    }
  }

  // Node tree(10);
  // std::cout << tree.position << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3) << std::endl;
  return 0;
}
