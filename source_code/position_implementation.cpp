#include "position.h"
#include <stdexcept>
#include <cctype>

Position::Position(int row, int col) : _row(row), _col(col) {}

Position Position::fromAlgebraic(const std::string &algebraic)
{
    if (algebraic.length() != 2)
    {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    char file = std::tolower(algebraic[0]);
    char rank = algebraic[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
    {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    int col = file - 'a';
    int row = '8' - rank;

    return Position(row, col);
}

std::string Position::toAlgebraic() const
{
    char file = 'a' + _col;
    char rank = '8' - _row;
    return std::string(1, file) + std::string(1, rank);
}

bool Position::isValid() const
{
    return _row >= 0 && _row < 8 && _col >= 0 && _col < 8;
}