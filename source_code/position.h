#ifndef POSITION_H
#define POSITION_H

#include <string>

class Position
{
public:
    int _row; // 0-7 (8th rank to 1st rank)
    int _col; // 0-7 (a file to h file)

    Position(int row, int col);

    static Position fromAlgebraic(const std::string &algebraic);
    std::string toAlgebraic() const;
    bool isValid() const;
};

#endif // POSITION_H