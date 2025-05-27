// queen.cpp
#include "queen.h"
#include "chess_board.h"
#include <cmath>

// Constructor cho lớp Queen, nhận màu sắc và vị trí khởi tạo.
Queen::Queen(Color color, const Position &pos)
    : ChessPiece(PieceType::QUEEN, color, pos) {}

// Phương thức trả về một vector chứa tất cả các vị trí mà quân Hậu có thể di chuyển đến từ vị trí hiện tại trên bàn cờ.
std::vector<Position> Queen::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Tám hướng di chuyển của quân Hậu: ngang, dọc và chéo.
    const int directions[8][2] = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}, // Di chuyển như quân Xe
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1} // Di chuyển như quân Tượng
    };

    // Duyệt qua từng hướng di chuyển.
    for (const auto &dir : directions)
    {
        // Quân Hậu có thể di chuyển tối đa 7 ô theo một hướng.
        for (int i = 1; i < 8; ++i)
        {
            // Tính toán vị trí mới theo hướng và số bước di chuyển.
            Position newPos(_position._row + i * dir[0], _position._col + i * dir[1]);
            // Kiểm tra xem vị trí mới có nằm trong bàn cờ hay không.
            if (!newPos.isValid())
            {
                break; // Ra khỏi bàn cờ, không xét các ô xa hơn theo hướng này.
            }

            // Lấy con cờ tại vị trí đích.
            ChessPiece *pieceAtDest = board.getPiece(newPos);
            // Nếu ô đích trống.
            if (pieceAtDest == nullptr)
            {
                moves.push_back(newPos); // Thêm vào danh sách các nước đi hợp lệ.
            }
            // Nếu có quân cờ ở ô đích.
            else
            {
                // Nếu là quân cờ của đối phương.
                if (pieceAtDest->getColor() != _color)
                {
                    moves.push_back(newPos); // Có thể ăn quân đối phương.
                }
                break; // Không thể di chuyển xa hơn theo hướng này vì có quân cản.
            }
        }
    }

    return moves;
}

// Phương thức kiểm tra xem một nước đi cụ thể đến vị trí 'dest' có hợp lệ đối với quân Hậu hay không.
bool Queen::isValidMove(const ChessBoard &board, const Position &dest) const
{
    // Tính toán sự khác biệt về hàng và cột giữa vị trí đích và vị trí hiện tại.
    int rowDiff = dest._row - _position._row;
    int colDiff = dest._col - _position._col;

    // Quân Hậu di chuyển theo hàng ngang, hàng dọc hoặc đường chéo.
    bool isHorizontalOrVertical = (rowDiff == 0 && colDiff != 0) || (rowDiff != 0 && colDiff == 0);
    bool isDiagonal = std::abs(rowDiff) == std::abs(colDiff) && rowDiff != 0;

    // Nếu không phải là di chuyển ngang, dọc hoặc chéo, thì không hợp lệ.
    if (!isHorizontalOrVertical && !isDiagonal)
    {
        return false;
    }

    // Kiểm tra xem đường đi có bị chặn bởi quân cờ khác không.
    int rowStep, colStep;
    if (rowDiff == 0)
    {
        rowStep = 0;
        colStep = (colDiff > 0) ? 1 : -1;
    }
    else if (colDiff == 0)
    {
        rowStep = (rowDiff > 0) ? 1 : -1;
        colStep = 0;
    }
    else
    {
        // Di chuyển chéo
        rowStep = (rowDiff > 0) ? 1 : -1;
        colStep = (colDiff > 0) ? 1 : -1;
    }

    // Số bước di chuyển tối đa.
    int steps = std::max(std::abs(rowDiff), std::abs(colDiff));
    // Duyệt qua các ô trên đường đi (trừ ô bắt đầu và ô đích).
    for (int i = 1; i < steps; ++i)
    {
        // Tính toán vị trí của ô trung gian trên đường đi.
        Position checkPos(_position._row + i * rowStep, _position._col + i * colStep);
        // Nếu có quân cờ ở ô trung gian, đường đi bị chặn.
        if (board.getPiece(checkPos) != nullptr)
        {
            return false; // Đường đi bị chặn.
        }
    }

    // Kiểm tra ô đích: phải trống hoặc chứa quân cờ của đối phương.
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color;
}