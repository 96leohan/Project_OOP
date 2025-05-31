#include <gtest/gtest.h>
#include "Board.h"
#include "PieceFactory.h"

TEST(BoardTest, MovePiece) {
    Board board;
    board.placePiece(PieceFactory::createPiece(PieceType::Pawn, Color::White), Position(1, 0));
    EXPECT_TRUE(board.movePiece(Position(1, 0), Position(2, 0)));
    EXPECT_FALSE(board.getPiece(Position(1, 0)));
    EXPECT_TRUE(board.getPiece(Position(2, 0)));
}

