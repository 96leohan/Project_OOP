#pragma once
#include <string>

class Position {
public:
    Position(int row, int col) : row(row), col(col) {}
    int getRow() const { return row; }
    int getCol() const { return col; }
    std::string toString() const {
        return std::string(1, 'a' + col) + std::to_string(row + 1);
    }
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

private:
    int row;
    int col;
};
