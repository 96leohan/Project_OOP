#include "QueenValidator.h"

bool QueenValidator::isValid(const Position& from, const Position& to, const Board& board) const {
    int rowDiff = abs(to.getRow() - from.getRow());
    int colDiff = abs(to.getCol() - from.getCol());
    if (from.getRow() == to.getRow() || from.getCol() == to.getCol() || rowDiff == colDiff) {
        if (board.isPathClear(from, to)) {
            auto target = board.getPiece(to);
            return !target || target->getColor() != board.getPiece(from)->getColor();
        }
    }
    return false;
}
