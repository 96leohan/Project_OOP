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
    }// source_code/src/chess/Board.cpp
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
    for (int col = 0; col < 8; ++col) {
        placePiece(PieceFactory::createPiece(PieceType::Pawn, Color::White), Position(1, col));
        placePiece(PieceFactory::createPiece(PieceType::Pawn, Color::Black), Position(6, col));
    }
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 7));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 7));
    placePiece(PieceFactory::createPiece(PieceType::Knight, Color::White), Position(0, 1));
    placePiece(PieceFactory::createPiece(PieceType::Knight, Color::White), Position(0, 6));
    placePiece(PieceFactory::createPiece(PieceType::Knight, Color::Black), Position(7, 1));
    placePiece(PieceFactory::createPiece(PieceType::Knight, Color::Black), Position(7, 6));
    placePiece(PieceFactory::createPiece(PieceType::Bishop, Color::White), Position(0, 2));
    placePiece(PieceFactory::createPiece(PieceType::Bishop, Color::White), Position(0, 5));
    placePiece(PieceFactory::createPiece(PieceType::Bishop, Color::Black), Position(7, 2));
    placePiece(PieceFactory::createPiece(PieceType::Bishop, Color::Black), Position(7, 5));
    placePiece(PieceFactory::createPiece(PieceType::Queen, Color::White), Position(0, 3));
    placePiece(PieceFactory::createPiece(PieceType::Queen, Color::Black), Position(7, 3));
    placePiece(PieceFactory::createPiece(PieceType::King, Color::White), Position(0, 4));
    placePiece(PieceFactory::createPiece(PieceType::King, Color::Black), Position(7, 4));
}

bool Board::isPathClear(const Position& from, const Position& to) const {
    int rowStep = (to.getRow() > from.getRow()) ? 1 : (to.getRow() < from.getRow()) ? -1 : 0;
    int colStep = (to.getCol() > from.getCol()) ? 1 : (to.getCol() < from.getCol()) ? -1 : 0;
    int row = from.getRow() + rowStep;
    int col = from.getCol() + colStep;

    while (row != to.getRow() || col != to.getCol()) {
        if (getPiece(Position(row, col))) {
            return false;
        }
        row += rowStep;
        col += colStep;
    }
    return true;
}

bool Board::isKingUnderAttack(const Position& kingPos, Color kingColor) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = getPiece(Position(row, col));
            if (piece && piece->getColor() != kingColor) {
                if (piece->validateMove(Position(row, col), kingPos, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheck(Color color) const {
    Position kingPos(-1, -1);
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = getPiece(Position(row, col));
            if (piece && piece->getColor() == color && piece->getSymbol() == (color == Color::White ? "♔" : "♚")) {
                kingPos = Position(row, col);
                break;
            }
        }
        if (kingPos.getRow() != -1) break;
    }
    return isKingUnderAttack(kingPos, color);
}

bool Board::isCheckmate(Color color) const {
    if (!isCheck(color)) {
        return false;
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = getPiece(Position(row, col));
            if (piece && piece->getColor() == color) {
                for (int toRow = 0; toRow < 8; ++toRow) {
                    for (int toCol = 0; toCol < 8; ++toCol) {
                        Position from(row, col);
                        Position to(toRow, toCol);
                        if (isValidMove(from, to)) {
                            Board tempBoard = *this;
                            tempBoard.movePiece(from, to);
                            if (!tempBoard.isCheck(color)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
    // Initialize other pieces (simplified)
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::White), Position(0, 7));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 0));
    placePiece(PieceFactory::createPiece(PieceType::Rook, Color::Black), Position(7, 7));
}
