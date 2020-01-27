#include <iostream>

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
