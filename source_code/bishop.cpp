// bishop.cpp
#include "bishop.h"
#include "chess_board.h"
#include <cmath>

Bishop::Bishop(Color color, const Position &pos)
    : ChessPiece(PieceType::BISHOP, color, pos) {} // Constructor: Khởi tạo một quân Tượng với màu sắc và vị trí cho trước, gọi constructor của lớp cha ChessPiece.

std::vector<Position> Bishop::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves; // Vector để lưu trữ các nước đi khả thi.

    // Bốn hướng đi chéo của quân Tượng: (-1,-1), (-1,1), (1,-1), (1,1) tương ứng với lên trái, lên phải, xuống trái, xuống phải.
    const int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (const auto &dir : directions) // Duyệt qua từng hướng đi.
    {
        for (int i = 1; i < 8; ++i) // Kiểm tra tối đa 7 ô theo hướng hiện tại (bàn cờ 8x8).
        {
            Position newPos(_position._row + i * dir[0], _position._col + i * dir[1]); // Tính toán vị trí mới theo hướng và khoảng cách i.
            if (!newPos.isValid())                                                     // Kiểm tra xem vị trí mới có nằm trên bàn cờ không.
            {
                break; // Nếu ra khỏi bàn cờ, không thể đi tiếp theo hướng này.
            }

            ChessPiece *pieceAtDest = board.getPiece(newPos); // Lấy quân cờ tại vị trí mới trên bàn cờ.
            if (pieceAtDest == nullptr)
            {
                moves.push_back(newPos); // Nếu ô trống, đây là một nước đi hợp lệ.
            }
            else
            {
                if (pieceAtDest->getColor() != _color) // Kiểm tra xem quân cờ ở đích có phải của đối phương không.
                {
                    moves.push_back(newPos); // Nếu là quân đối phương, đây là một nước đi "ăn" quân hợp lệ.
                }
                break; // Không thể đi xuyên qua một quân cờ, dù là quân mình hay quân đối phương. Dừng kiểm tra theo hướng này.
            }
        }
    }

    return moves; // Trả về vector chứa tất cả các nước đi khả thi.
}

bool Bishop::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = dest._row - _position._row; // Tính sự khác biệt về hàng giữa vị trí đích và vị trí hiện tại.
    int colDiff = dest._col - _position._col; // Tính sự khác biệt về cột giữa vị trí đích và vị trí hiện tại.

    // Quân Tượng chỉ di chuyển theo đường chéo. Điều này có nghĩa là sự thay đổi tuyệt đối về hàng phải bằng sự thay đổi tuyệt đối về cột,
    // và vị trí đích không được trùng với vị trí hiện tại.
    if (std::abs(rowDiff) != std::abs(colDiff) || (rowDiff == 0 && colDiff == 0))
    {
        return false; // Nếu không phải đường chéo hoặc không di chuyển, nước đi không hợp lệ.
    }

    // Kiểm tra xem đường đi có bị chặn bởi quân cờ khác không.
    int rowStep = (rowDiff > 0) ? 1 : -1; // Xác định bước di chuyển theo hàng (+1 nếu xuống, -1 nếu lên).
    int colStep = (colDiff > 0) ? 1 : -1; // Xác định bước di chuyển theo cột (+1 nếu sang phải, -1 nếu sang trái).

    for (int i = 1; i < std::abs(rowDiff); ++i) // Duyệt qua các ô nằm giữa vị trí hiện tại và vị trí đích.
    {
        Position checkPos(_position._row + i * rowStep, _position._col + i * colStep); // Tính toán vị trí của ô trung gian.
        if (board.getPiece(checkPos) != nullptr)                                       // Kiểm tra xem có quân cờ nào ở ô trung gian không.
        {
            return false; // Nếu có quân cờ chặn đường, nước đi không hợp lệ.
        }
    }

    // Kiểm tra vị trí đích: có trống hoặc có quân cờ của đối phương không.
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color; // Hợp lệ nếu ô đích trống hoặc chứa quân cờ khác màu.
}