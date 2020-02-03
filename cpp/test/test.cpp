#define CATCH_CONFIG_MAIN
#include <iostream>
#include "./catch.hpp"
#include "../include/Board.hpp"

TEST_CASE("") {
  Board::board state = {
    0x0,
    0x0,
    0x0,
    0x0,
    false
  };
  Board game(state);

  SECTION("White to move") {
    SECTION("getLegalPushes") {
      std::vector<Board::move> pushes = game.getLegalPushes();
      REQUIRE(pushes.size() == 0);
    }
    SECTION("getLegalCaptures") {
      std::vector<Board::move> captures = game.getLegalCaptures();
      REQUIRE(captures.size() == 0);
    }
    SECTION("getLegalMoves") {
      std::vector<Board::move> moves = game.getLegalMoves();
      REQUIRE(moves.size() == 0);
    }
    SECTION("makeMove") {
      Board::move mv = {{0, 5}, {0ULL}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
    }
    SECTION("getResult") {
      REQUIRE_THROWS_AS(game.getResult(), Board::InvalidPositionException);
    }
  }

  SECTION("Black to move") {
    game.setPlayerToMove(true);
    SECTION("getLegalPushes") {
      std::vector<Board::move> pushes = game.getLegalPushes();
      REQUIRE(pushes.size() == 0);
    }
    SECTION("getLegalCaptures") {
      std::vector<Board::move> captures = game.getLegalCaptures();
      REQUIRE(captures.size() == 0);
    }
    SECTION("getLegalMoves") {
      std::vector<Board::move> moves = game.getLegalMoves();
      REQUIRE(moves.size() == 0);
    }
    SECTION("makeMove") {
      Board::move mv = {{0, 5}, {0ULL}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
    }
    SECTION("getResult") {
      REQUIRE_THROWS_AS(game.getResult(), Board::InvalidPositionException);
    }
  }
}
TEST_CASE("W10,12:B6,8") {
  Board::board state = {
    0xa00,
    0x0,
    0xa0,
    0x0,
    false
  };
  Board game(state);

  SECTION("White to move") {
    SECTION("getLegalPushes") {
      std::vector<Board::move> pushes = game.getLegalPushes();
      std::vector<Board::move> correct = {
        {{0x800, 0x40}, {0x0}},
        {{0x200, 0x8}, {0x0}},
        {{0x200, 0x10}, {0x0}}
      };
      for (auto &mv : pushes) {
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
      }
    }
    SECTION("getLegalCaptures") {
      std::vector<Board::move> captures = game.getLegalCaptures();
      std::vector<Board::move> correct = {
        {{0x800, 0x4}, {0x80}}
      };
      for (auto &mv : captures) {
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
      }
    }
    SECTION("getLegalMoves") {
      std::vector<Board::move> moves = game.getLegalMoves();
      std::vector<Board::move> correct = {
        {{0x800, 0x4}, {0x80}}
      };
      for (auto &mv : moves)
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
    }
    SECTION("makeMove") {
      Board::board copyState = game.getState();
      Board::board correctState = {
        0x204,
        0x0,
        0x20,
        0x0,
        true
      };
      Board::move mv = {{0x0, 0x4}, {0x0}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
      REQUIRE(copyState == game.getState());
      mv = {{0x800, 0x40}, {0x0}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
      REQUIRE(copyState == game.getState());
      mv = {{0x800, 0x4}, {0x80}};
      game.makeMove(mv);
      REQUIRE(copyState == game.getState());
    }
    SECTION("getResult") {
      REQUIRE_THROWS_AS(game.getResult(), Board::InvalidPositionException);
    }
  }
  SECTION("Black to move") {
    game.setPlayerToMove(true);
    SECTION("getLegalPushes") {
      std::vector<Board::move> pushes = game.getLegalPushes();
      std::vector<Board::move> correct = {
        {{0x20, 0x400}, {0x0}},
        {{0x80, 0x1000}, {0x0}}
      };
      for (auto &mv : pushes)
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
    }
    SECTION("getLegalCaptures") {
      std::vector<Board::move> captures = game.getLegalCaptures();
      std::vector<Board::move> correct = {
        {{0x80, 0x10000}, {0x800}}
      };
      for (auto &mv : captures)
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
    }
    SECTION("getLegalMoves") {
      std::vector<Board::move> moves = game.getLegalMoves();
      std::vector<Board::move> correct = {
        {{0x80, 0x10000}, {0x800}}
      };
      for (auto &mv : moves)
        REQUIRE(std::find(correct.begin(), correct.end(), mv) != correct.end());
    }
    SECTION("makeMove") {
      Board::board copyState = game.getState();
      Board::board correctState = {
        0x200,
        0x0,
        0x10020,
        0x0,
        false
      };
      Board::move mv = {{0x0, 0x4}, {0x0}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
      REQUIRE(copyState == game.getState());
      mv = {{0x20, 0x400}, {0x0}};
      REQUIRE_THROWS_AS(game.makeMove(mv), Board::IllegalMoveException);
      REQUIRE(copyState == game.getState());
      mv = {{0x80, 0x10000}, {0x800}};
      game.makeMove(mv);
      REQUIRE(copyState == game.getState());
    }
    SECTION("getResult") {
      REQUIRE_THROWS_AS(game.getResult(), Board::InvalidPositionException);
    }
  }
}
