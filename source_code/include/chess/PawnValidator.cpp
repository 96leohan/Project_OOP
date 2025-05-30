#include "PawnValidator.h"

PawnValidator::PawnValidator(Color color) : color_(color) {}

bool PawnValidator::isValid(const Position& from, const Position& to, const Board& board) const {
    int direction = (color_ == Color::White) ? 1 : -1;
    int startRow = (color_ == Color::White) ? 1 : 6;

    // Forward move
    if (from.getCol() == to.getCol()) {
        if (to.getRow() == from.getRow() + direction && !board.getPiece(to)) {
            return true;
        }
        if (from.getRow() == startRow && to.getRow() == from.getRow() + 2 * direction && !board.getPiece(to)) {
            return isDoubleMove(from, to);
        }
    }
    // Capture move
    if (abs(to.getCol() - from.getCol()) == 1 && to.getRow() == from.getRow() + direction) {
        return isCapture(from, to, board);
    }
    return false;
}

bool PawnValidator::isDoubleMove(const Position& from, const Position& to) const {
    int midRow = (from.getRow() + to.getRow()) / 2;
    Position midPos(midRow, from.getCol());
    return true; // Placeholder for checking if the middle position is empty
}

bool PawnValidator::isCapture(const Position& from, const Position& to, const Board& board) const {
    auto target = board.getPiece(to);
    return target && target->getColor() != color_;
}
