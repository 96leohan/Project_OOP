#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "chess_piece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class ChessBoard
{
private:
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> _board; // Biểu diễn bàn cờ dưới dạng một vector 2D chứa các con trỏ thông minh đến các quân cờ
    Color _currentTurn;                                           // Lưu trữ màu của người chơi hiện tại (WHITE hoặc BLACK)
    bool _gameOver;                                               // Biến boolean để theo dõi trạng thái kết thúc của trò chơi

    // Các phương thức hỗ trợ (private helper methods)
    bool isInCheck(Color color) const;   // Phương thức kiểm tra xem vua của một màu cụ thể có đang bị chiếu hay không
    bool isCheckmate(Color color) const; // Phương thức kiểm tra xem vua của một màu cụ thể có bị chiếu hết hay không

public:
    ChessBoard();            // constructor của lớp ChessBoard
    ~ChessBoard() = default; // Sử dụng hàm hủy mặc định (không cần quản lý bộ nhớ thủ công do dùng unique_ptr)
    // Copy constructor
    ChessBoard(const ChessBoard& other);
    // Assignment operator
    ChessBoard& operator=(const ChessBoard& other);

    void initializeBoard(); // Phương thức để thiết lập bàn cờ với các quân cờ ở vị trí bắt đầu
    void display() const;   // Phương thức để hiển thị trạng thái hiện tại của bàn cờ ra màn hình console
    
    ChessPiece *getPiece(const Position &pos) const;          // Phương thức để lấy con trỏ (thô) đến quân cờ tại một vị trí nhất định
    bool movePiece(const Position &from, const Position &to); // Phương thức để thực hiện một nước đi từ vị trí 'from' đến vị trí 'to'
    Color getCurrentTurn() const;                             // Phương thức để lấy màu của người chơi hiện tại
    bool isGameOver() const;                                  // Phương thức để kiểm tra xem trò chơi đã kết thúc chưa
    void promotePawn(const Position &pos);                    // Phương thức để xử lý việc phong cấp tốt tại một vị trí nhất định
};

#endif // CHESS_BOARD_H