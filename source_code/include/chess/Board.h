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
    bool isCheckmate(Color color) const;
    bool isCheck(Color color) const;

private:
    std::vector<std::vector<std::unique_ptr<Piece>>> grid_;
    bool isPathClear(const Position& from, const Position& to) const;
    bool isKingUnderAttack(const Position& kingPos, Color kingColor) const;
};
