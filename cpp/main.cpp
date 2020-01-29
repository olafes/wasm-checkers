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

  // u64 x = 0b01001110011000;
  // u64 lsb = x&(~x+1);
  // std::cout << lsb-1 << std::endl;

  // u64 bitboard = 0b00000100111000010111;
  //                       111111111111111
  // bitboard|=(bitboard>>1);
  // bitboard|=(bitboard>>2);
  // bitboard|=(bitboard>>4);
  // bitboard|=(bitboard>>8);
  // bitboard|=(bitboard>>16);
  // bitboard|=(bitboard>>32);
  // std::cout << bitboard << std::endl;



  // 1111011110111101111011110111101110011110


  // 100 00000 00000 00000 00000
  u64 whiteMen = 0b0000000000000000000000000000000000000000000000000000010000000000;
  u64 whiteKings = 0b0000000000000000000000000000000000000000010000000000000000000000;
  u64 blackMen = 0b0000000000000000000000000000000000000000000001100000000111000000;
  u64 blackKings = 0b0000000000000000000000000000000000000000000000000000000000000000;

  u64 menMovers0 = Board::getMenMovers(whiteMen, whiteKings, blackMen, blackKings, 0);
  u64 menMovers1 = Board::getMenMovers(whiteMen, whiteKings, blackMen, blackKings, 1);
  std::vector<kingMoveChunk> kingMovers[] = {
    Board::getKingsMovers(whiteMen, whiteKings, blackMen, blackKings, 0),
    Board::getKingsMovers(whiteMen, whiteKings, blackMen, blackKings, 1),
    Board::getKingsMovers(whiteMen, whiteKings, blackMen, blackKings, 2),
    Board::getKingsMovers(whiteMen, whiteKings, blackMen, blackKings, 3),
  };
  std::cout << "Movers 0: " << menMovers0 << std::endl;
  std::cout << "Movers 1: " << menMovers1 << std::endl;

  for (u8 i=0; i<4; i++) {
    std::cout << "King direction " << (int)i << std::endl;
    for (auto& king : kingMovers[i]) {
      std::cout << "King " << king.from << std::endl;
      std::cout << "LANDING SIZE: " << king.landing.size() << std::endl;
      for (auto& landing: king.landing) {
        std::cout << "landing " << landing << std::endl;
      }
    }
  }

  // std::vector<std::vector<u64>> captures = Board::getKingsCaptures(whiteMen, whiteKings, blackMen, blackKings);
  // std::cout << "size of captures: " << captures.size() << std::endl;
  // for (auto& capture : captures) {
  //   std::cout << "capture" << std::endl;
  //   for (auto& move : capture) {
  //     std::cout << move << std::endl;
  //   }
  // }

  // Node tree(10);
  // std::cout << tree.position << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 0) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 1) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 2) << std::endl;
  // std::cout << Board::getJumperMen(whiteMen, whiteKings, blackMen, blackKings, 3) << std::endl;
  return 0;
}
