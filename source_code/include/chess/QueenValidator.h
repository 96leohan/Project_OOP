#pragma once
#include "MoveValidator.h"

class QueenValidator : public MoveValidator {
public:
    bool isValid(const Position& from, const Position& to, const Board& board) const override;
};
