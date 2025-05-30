#include "Board.h"
#include "PieceFactory.h"

Board::Board() : grid_(8, std::vector<std::unique_ptr<Piece>>(8)) {}

void Board::placePiece(std::unique_ptr<Piece> piece, const Position& pos) {
    if (pos.getRow() >= 0 && pos.getRow() < 8 && pos.getCol() >= 0 && pos.getCol() < 8) {
        grid_[pos.getRow()][pos.getCol()] = std::move(piece);
    }
}

bool Board::movePiece(const Position& from, const Position& to) {
    if (!isValidMove(from, to)) {
        return false;
    }
    auto piece = std::move(grid_[from.getRow()][from.getCol()]);
    grid_[from.getRow()][from.getCol()] = nullptr;
    grid_[to.getRow()][to.getCol()] = std::move(piece);
    return true;
}

bool Board::isValidMove(const Position& from, const Position& to) const {
    if (from.getRow() < 0 || from.getRow() >= 8 || from.getCol() < 0 || from.getCol() >= 8 ||
        to.getRow() < 0 || to.getRow() >= 8 || to.getCol() < 0 || to.getCol() >= 8) {
        return false;
    }
    auto piece = getPiece(from);
    if (!piece) {
        return false;
    }
    return piece->validateMove(from, to, *this);
}

std::unique_ptr<Piece> Board::getPiece(const Position& pos) const {
    if (pos.getRow() >= 0 && pos.getRow() < 8 && pos.getCol() >= 0 && pos.getCol() < 8) {
        if (grid_[pos.getRow()][pos.getCol()]) {
            return grid_[pos.getRow()][pos.getCol()]->clone();
        }
    }
    return nullptr;
}

void Board::initializeBoard() {
    // Initialize pawns
    for (int col = 0; col < 8; ++col) {
        placePiece(PieceFactory::createPiece(PieceType::Pawn, Color::White), Position(1, col));
        placePiece(PieceFactory::createPiece(PieceType::Pawn, Color::Black), Position(6, col));
    }
    // Initialize other pieces (simplified)
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 7));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 7));
}
