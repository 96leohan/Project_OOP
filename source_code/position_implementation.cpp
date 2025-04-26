#include "position.h"
#include <stdexcept>
#include <cctype>
#include <string>

// Constructor của lớp Position, nhận số hàng và số cột làm đối số và khởi tạo các thuộc tính tương ứng.
Position::Position(int row, int col) : _row(row), _col(col) {}

// Phương thức static để tạo một đối tượng Position từ ký hiệu đại số (ví dụ: "a1", "h8").
Position Position::fromAlgebraic(const std::string &algebraic)
{
    // Kiểm tra độ dài của ký hiệu đại số, phải là 2 ký tự (ví dụ: "a1").
    if (algebraic.length() != 2)
    {
        // Ném ra ngoại lệ nếu định dạng không hợp lệ.
        throw std::invalid_argument("Invalid algebraic notation");
    }

    // Lấy ký tự biểu diễn cột (file) và chuyển về chữ thường.
    char file = std::tolower(algebraic[0]);
    // Lấy ký tự biểu diễn hàng (rank).
    char rank = algebraic[1];

    // Kiểm tra xem ký tự cột có nằm trong khoảng 'a' đến 'h' và ký tự hàng có nằm trong khoảng '1' đến '8' hay không.
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
    {
        // Ném ra ngoại lệ nếu ký hiệu đại số không hợp lệ.
        throw std::invalid_argument("Invalid algebraic notation");
    }

    // Chuyển đổi ký tự cột sang số cột (0-7).
    int col = file - 'a';
    // Chuyển đổi ký tự hàng sang số hàng (0-7, với hàng 8 là 0 và hàng 1 là 7).
    int row = '8' - rank;

    // Trả về một đối tượng Position mới với số hàng và số cột đã được chuyển đổi.
    return Position(row, col);
}

// Phương thức trả về ký hiệu đại số của vị trí hiện tại (ví dụ: "a1", "h8").
std::string Position::toAlgebraic() const
{
    // Chuyển đổi số cột (0-7) sang ký tự cột ('a'-'h').
    char file = 'a' + _col;
    // Chuyển đổi số hàng (0-7) sang ký tự hàng ('8'-'1').
    char rank = '8' - _row;
    // Tạo một chuỗi từ ký tự cột và ký tự hàng và trả về.
    return std::string(1, file) + std::string(1, rank);
}

// Phương thức kiểm tra xem vị trí hiện tại có nằm trong phạm vi hợp lệ của bàn cờ (0-7 cho cả hàng và cột) hay không.
bool Position::isValid() const
{
    // Trả về true nếu cả số hàng và số cột đều nằm trong khoảng từ 0 đến 7, ngược lại trả về false.
    return _row >= 0 && _row < 8 && _col >= 0 && _col < 8;
}