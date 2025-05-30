#include "KnightValidator.h"

bool KnightValidator::isValid(const Position& from, const Position& to, const Board& board) const {
    int rowDiff = abs(to.getRow() - from.getRow());
    int colDiff = abs(to.getCol() - from.getCol());
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        auto target = board.getPiece(to);
        return !target || target->getColor() != board.getPiece(from)->getColor();
    }
    return false;
}
