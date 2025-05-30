#pragma once
#include "Position.h"
#include "Board.h"

class Board;

class MoveValidator {
public:
    virtual ~MoveValidator() = default;
    virtual bool isValid(const Position& from, const Position& to, const Board& board) const = 0;
};
