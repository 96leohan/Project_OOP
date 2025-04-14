#include "chess_piece.h"
#include <cctype>

ChessPiece::ChessPiece(PieceType type, Color color, const Position &pos)
    : _type(type), _color(color), _position(pos) {}

PieceType ChessPiece::getType() const
{
    return _type;
}

Color ChessPiece::getColor() const
{
    return _color;
}

Position ChessPiece::getPosition() const
{
    return _position;
}

void ChessPiece::setPosition(const Position &pos)
{
    _position = pos;
}

char ChessPiece::getSymbol() const
{
    char symbol;
    switch (_type)
    {
    case PieceType::PAWN:
        symbol = 'P';
        break;
    case PieceType::KNIGHT:
        symbol = 'N';
        break;
    case PieceType::BISHOP:
        symbol = 'B';
        break;
    case PieceType::ROOK:
        symbol = 'R';
        break;
    case PieceType::QUEEN:
        symbol = 'Q';
        break;
    case PieceType::KING:
        symbol = 'K';
        break;
    default:
        symbol = '?';
    }
    return _color == Color::WHITE ? symbol : std::tolower(symbol);
}