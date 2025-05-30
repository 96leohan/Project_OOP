#pragma once
#include "Position.h"
#include "MoveValidator.h"
#include <memory>
#include <string>

enum class Color { White, Black };
enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King };

class Piece {
public:
    Piece(Color color, std::unique_ptr<MoveValidator> validator);
    virtual ~Piece() = default;
    virtual std::unique_ptr<Piece> clone() const = 0;
    virtual std::string getSymbol() const = 0;
    bool validateMove(const Position& from, const Position& to, const Board& board) const;
    Color getColor() const { return color_; }

protected:
    Color color_;
    std::unique_ptr<MoveValidator> validator_;
};
