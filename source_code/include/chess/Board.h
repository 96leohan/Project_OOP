#pragma once
#include "Piece.h"
#include <vector>
#include <memory>

class Board {
public:
    Board();
    void placePiece(std::unique_ptr<Piece> piece, const Position& pos);
    bool movePiece(const Position& from, const Position& to);
    bool isValidMove(const Position& from, const Position& to) const;
    std::unique_ptr<Piece> getPiece(const Position& pos) const;
    void initializeBoard();

private:
    std::vector<std::vector<std::unique_ptr<Piece>>> grid_;
};
