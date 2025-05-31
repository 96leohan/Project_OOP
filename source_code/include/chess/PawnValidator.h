#pragma once
#include "MoveValidator.h"

class PawnValidator : public MoveValidator {
public:
    PawnValidator(Color color);
    bool isValid(const Position& from, const Position& to, const Board& board) const override;

private:
    Color color_;
};
