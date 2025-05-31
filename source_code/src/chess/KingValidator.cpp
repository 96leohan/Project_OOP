#include "KingValidator.h"

bool KingValidator::isValid(const Position& from, const Position& to, const Board& board) const {
    int rowDiff = abs(to.getRow() - from.getRow());
    int colDiff = abs(to.getCol() - from.getCol());
    if (rowDiff <= 1 && colDiff <= 1) {
        auto target = board.getPiece(to);
        if (!target || target->getColor() != board.getPiece(from)->getColor()) {
            Board tempBoard = board;
            tempBoard.movePiece(from, to);
            return !tempBoard.isKingUnderAttack(to, board.getPiece(from)->getColor());
        }
    }
    return false;
}
