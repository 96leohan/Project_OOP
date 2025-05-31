#include <gtest/gtest.h>
#include "Pawn.h"
#include "Board.h"

TEST(PawnValidatorTest, ValidForwardMove) {
    Board board;
    auto pawn = std::make_unique<Pawn>(Color::White);
    Position from(1, 0), to(2, 0);
    board.placePiece(std::move(pawn), from);
    EXPECT_TRUE(board.isValidMove(from, to));
}
