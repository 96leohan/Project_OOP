#include "RookValidator.h"

bool RookValidator::isValid(const Position& from, const Position& to, const Board& board) const {
    if (from.getRow() == to.getRow() || from.getCol() == to.getCol()) {
        if (board.isPathClear(from, to)) {
            auto target = board.getPiece(to);
            return !target || target->getColor() != board.getPiece(from)->getColor();
        }
    }
    return false;
}
