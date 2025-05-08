#ifndef POSITION_H
#define POSITION_H

#include <string>

// Lớp Position đại diện cho một vị trí trên bàn cờ vua.
class Position
{
public:
    // Số hàng (0-7, tương ứng từ hàng 8 đến hàng 1).
    int _row;
    // Số cột (0-7, tương ứng từ cột a đến cột h).
    int _col;

    int getX() const { return _col; } // Map col to X
    int getY() const { return _row; } // Map row to Y

    bool operator==(const Position &other) const
    {
        return _row == other._row && _col == other._col;
    }

    // Constructor của lớp Position, nhận số hàng và số cột làm đối số.
    Position(int row, int col);

    // Phương thức static để tạo một đối tượng Position từ ký hiệu đại số
    static Position fromAlgebraic(const std::string &algebraic);

    // Phương thức trả về ký hiệu đại số của vị trí hiện tại
    std::string toAlgebraic() const;

    // Phương thức kiểm tra xem vị trí hiện tại có nằm trong phạm vi hợp lệ của bàn cờ (0-7 cho cả hàng và cột) hay không.
    bool isValid() const;
};

#endif // POSITION_H