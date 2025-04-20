
// king.cpp
#include "king.h"
#include "chess_board.h"
#include <cmath>

King::King(Color color, const Position &pos)
    : ChessPiece(PieceType::KING, color, pos), _hasMoved(false) {}

std::vector<Position> King::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Eight adjacent squares
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int colOffset = -1; colOffset <= 1; ++colOffset)
        {
            // Skip current position
            if (rowOffset == 0 && colOffset == 0)
            {
                continue;
            }

            Position newPos(_position._row + rowOffset, _position._col + colOffset);
            if (newPos.isValid())
            {
                ChessPiece *pieceAtDest = board.getPiece(newPos);
                if (pieceAtDest == nullptr || pieceAtDest->getColor() != _color)
                {
                    moves.push_back(newPos);
                }
            }
        }
    }

    // TODO: Add castling moves

    return moves;
}

bool King::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = std::abs(dest._row - _position._row);
    int colDiff = std::abs(dest._col - _position._col);

    // Normal king move: one square in any direction
    bool isNormalMove = rowDiff <= 1 && colDiff <= 1 && (rowDiff != 0 || colDiff != 0);

    // TODO: Add castling validation

    if (!isNormalMove)
    {
        return false;
    }

    // Check destination: empty or opponent's piece
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}

bool King::hasMoved() const
{
    return _hasMoved;
}

// Các phương thức nhập thành
bool King::canCastleKingside(const ChessBoard &board) const
{
    if (_hasMoved)
        return false;

    // Kiểm tra nếu xe ở vị trí h1/h8 và chưa di chuyển
    int row = (_color == Color::WHITE) ? 7 : 0;
    Position rookPos(row, 7);
    ChessPiece *rook = board.getPiece(rookPos);

    if (rook == nullptr || rook->getType() != PieceType::ROOK ||
        rook->getColor() != _color || dynamic_cast<Rook *>(rook)->hasMoved())
    {
        return false;
    }

    // Kiểm tra nếu đường đi trống
    for (int col = 5; col < 7; ++col)
    {
        if (board.getPiece(Position(row, col)) != nullptr)
        {
            return false;
        }
    }

    // Kiểm tra nếu vua không bị chiếu và các ô đi qua không bị tấn công
    for (int col = 4; col <= 6; ++col)
    {
        Position checkPos(row, col);
        // Giả lập vị trí vua tại mỗi ô để kiểm tra xem có bị chiếu không
        // (Cần cài đặt phương thức isSquareAttacked trong ChessBoard)

        // Đây là code giả:
        // if (board.isSquareAttacked(checkPos, _color)) {
        //     return false;
        // }
    }

    return true;
}

bool King::canCastleQueenside(const ChessBoard &board) const
{
    if (_hasMoved)
        return false;

    // Kiểm tra nếu xe ở vị trí a1/a8 và chưa di chuyển
    int row = (_color == Color::WHITE) ? 7 : 0;
    Position rookPos(row, 0);
    ChessPiece *rook = board.getPiece(rookPos);

    if (rook == nullptr || rook->getType() != PieceType::ROOK ||
        rook->getColor() != _color || dynamic_cast<Rook *>(rook)->hasMoved())
    {
        return false;
    }

    // Kiểm tra nếu đường đi trống
    for (int col = 1; col < 4; ++col)
    {
        if (board.getPiece(Position(row, col)) != nullptr)
        {
            return false;
        }
    }

    // Kiểm tra nếu vua không bị chiếu và các ô đi qua không bị tấn công
    for (int col = 2; col <= 4; ++col)
    {
        Position checkPos(row, col);
        // Tương tự như canCastleKingside
    }

    return true;
}

bool King::isCastlingMove(const Position &dest) const
{
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Vua di chuyển 2 ô theo chiều ngang
    return rowDiff == 0 && std::abs(colDiff) == 2;
}

// Cập nhật getPossibleMoves để bao gồm nước nhập thành
std::vector<Position> King::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Eight adjacent squares (code đã có)

    // Add castling moves
    int row = (_color == Color::WHITE) ? 7 : 0;
    if (canCastleKingside(board))
    {
        moves.push_back(Position(row, 6));
    }
    if (canCastleQueenside(board))
    {
        moves.push_back(Position(row, 2));
    }

    return moves;
}

// Cập nhật isValidMove để kiểm tra nước nhập thành
bool King::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = std::abs(dest._row - _position._row);
    int colDiff = std::abs(dest._col - _position._col);

    // Normal king move: one square in any direction
    bool isNormalMove = rowDiff <= 1 && colDiff <= 1 && (rowDiff != 0 || colDiff != 0);

    // Castling move
    bool isCastling = isCastlingMove(dest);
    if (isCastling)
    {
        bool isKingside = dest._col > _position._col;
        return isKingside ? canCastleKingside(board) : canCastleQueenside(board);
    }

    if (!isNormalMove && !isCastling)
    {
        return false;
    }

    // Check destination: empty or opponent's piece
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}
