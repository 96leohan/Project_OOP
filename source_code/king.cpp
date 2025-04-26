// king.cpp
#include "king.h"
#include "chess_board.h"
#include <cmath>

// Hàm tạo (constructor) của lớp King
King::King(Color color, const Position &pos)
    : ChessPiece(PieceType::KING, color, pos), // Gọi constructor của lớp cơ sở ChessPiece
      _hasMoved(false)                         // Khởi tạo trạng thái đã di chuyển của vua là false
{
}

// Phương thức để lấy tất cả các nước đi có thể của vua
std::vector<Position> King::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves; // Vector để lưu trữ các vị trí có thể đi

    // Duyệt qua tám ô vuông lân cận
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int colOffset = -1; colOffset <= 1; ++colOffset)
        {
            // Bỏ qua vị trí hiện tại của vua
            if (rowOffset == 0 && colOffset == 0)
            {
                continue;
            }

            // Tính toán vị trí mới
            Position newPos(_position._row + rowOffset, _position._col + colOffset);
            // Kiểm tra xem vị trí mới có nằm trên bàn cờ không
            if (newPos.isValid())
            {
                // Lấy quân cờ tại vị trí đích
                ChessPiece *pieceAtDest = board.getPiece(newPos);
                // Nếu ô đích trống hoặc có quân cờ của đối phương
                if (pieceAtDest == nullptr || pieceAtDest->getColor() != _color)
                {
                    moves.push_back(newPos); // Thêm vị trí này vào danh sách các nước đi có thể
                }
            }
        }
    }

    // TODO: Thêm các nước đi nhập thành (castling)

    return moves; // Trả về danh sách các nước đi có thể
}

// Phương thức để kiểm tra xem một nước đi cụ thể của vua có hợp lệ không
bool King::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = std::abs(dest._row - _position._row); // Tính độ lệch hàng
    int colDiff = std::abs(dest._col - _position._col); // Tính độ lệch cột

    // Nước đi thông thường của vua: một ô theo bất kỳ hướng nào
    bool isNormalMove = rowDiff <= 1 && colDiff <= 1 && (rowDiff != 0 || colDiff != 0);

    // TODO: Thêm kiểm tra cho nhập thành

    if (!isNormalMove)
    {
        return false; // Nếu không phải nước đi thông thường, và chưa kiểm tra nhập thành, thì không hợp lệ
    }

    // Kiểm tra ô đích: trống hoặc có quân cờ của đối phương
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color; // Hợp lệ nếu ô trống hoặc có quân khác màu
}

// Phương thức để kiểm tra xem vua đã di chuyển hay chưa
bool King::hasMoved() const
{
    return _hasMoved; // Trả về giá trị của biến _hasMoved
}

// Các phương thức cho nhập thành
bool King::canCastleKingside(const ChessBoard &board) const
{
    // Không thể nhập thành nếu vua đã di chuyển
    if (_hasMoved)
        return false;

    // Xác định hàng của vua dựa trên màu
    int row = (_color == Color::WHITE) ? 7 : 0;
    // Vị trí của xe cánh vua
    Position rookPos(row, 7);
    // Lấy quân cờ tại vị trí xe
    ChessPiece *rook = board.getPiece(rookPos);

    // Kiểm tra xem có xe ở vị trí đó, là xe, cùng màu và chưa di chuyển
    if (rook == nullptr || rook->getType() != PieceType::ROOK ||
        rook->getColor() != _color || dynamic_cast<Rook *>(rook)->hasMoved())
    {
        return false;
    }

    // Kiểm tra xem các ô giữa vua và xe có trống không
    for (int col = 5; col < 7; ++col)
    {
        if (board.getPiece(Position(row, col)) != nullptr)
        {
            return false;
        }
    }

    // Kiểm tra xem vua có bị chiếu, hoặc có đi qua ô bị chiếu không
    for (int col = 4; col <= 6; ++col)
    {
        Position checkPos(row, col);
        // Giả lập vị trí vua tại mỗi ô để kiểm tra xem có bị chiếu không
        // (Cần cài đặt phương thức isSquareAttacked trong ChessBoard)

        // Đoạn code giả (cần thay thế bằng logic thực tế):
        // if (board.isSquareAttacked(checkPos, _color)) {
        //     return false;
        // }
    }

    return true; // Nếu tất cả các điều kiện trên đều đúng, có thể nhập thành cánh vua
}

bool King::canCastleQueenside(const ChessBoard &board) const
{
    // Không thể nhập thành nếu vua đã di chuyển
    if (_hasMoved)
        return false;

    // Xác định hàng của vua dựa trên màu
    int row = (_color == Color::WHITE) ? 7 : 0;
    // Vị trí của xe cánh hậu
    Position rookPos(row, 0);
    // Lấy quân cờ tại vị trí xe
    ChessPiece *rook = board.getPiece(rookPos);

    // Kiểm tra xem có xe ở vị trí đó, là xe, cùng màu và chưa di chuyển
    if (rook == nullptr || rook->getType() != PieceType::ROOK ||
        rook->getColor() != _color || dynamic_cast<Rook *>(rook)->hasMoved())
    {
        return false;
    }

    // Kiểm tra xem các ô giữa vua và xe có trống không
    for (int col = 1; col < 4; ++col)
    {
        if (board.getPiece(Position(row, col)) != nullptr)
        {
            return false;
        }
    }

    // Kiểm tra xem vua có bị chiếu, hoặc có đi qua ô bị chiếu không
    for (int col = 2; col <= 4; ++col)
    {
        Position checkPos(row, col);
        // Tương tự như canCastleKingside (cần cài đặt isSquareAttacked)
    }

    return true; // Nếu tất cả các điều kiện trên đều đúng, có thể nhập thành cánh hậu
}

// Phương thức để kiểm tra xem một nước đi đến vị trí đích có phải là nhập thành không
bool King::isCastlingMove(const Position &dest) const
{
    int rowDiff = dest._row - _position._row; // Độ lệch hàng
    int colDiff = dest._col - _position._col; // Độ lệch cột

    // Vua di chuyển 2 ô theo chiều ngang và không thay đổi hàng
    return rowDiff == 0 && std::abs(colDiff) == 2;
}

// Cập nhật getPossibleMoves để bao gồm nước nhập thành
std::vector<Position> King::getPossibleMoves(const ChessBoard &board) const
{
    std::vector<Position> moves;

    // Eight adjacent squares (code đã có)
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int colOffset = -1; colOffset <= 1; ++colOffset)
        {
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

    // Add castling moves (thêm các nước đi nhập thành)
    int row = (_color == Color::WHITE) ? 7 : 0; // Xác định hàng của vua (hàng 7 cho trắng, hàng 0 cho đen)
    if (canCastleKingside(board))
    {
        moves.push_back(Position(row, 6)); // Vị trí nhập thành cánh vua (g1 cho trắng, g8 cho đen)
    }
    if (canCastleQueenside(board))
    {
        moves.push_back(Position(row, 2)); // Vị trí nhập thành cánh hậu (c1 cho trắng, c8 cho đen)
    }

    return moves;
}

// Cập nhật isValidMove để kiểm tra nước nhập thành
bool King::isValidMove(const ChessBoard &board, const Position &dest) const
{
    int rowDiff = std::abs(dest._row - _position._row); // Độ lệch hàng
    int colDiff = std::abs(dest._col - _position._col); // Độ lệch cột

    // Normal king move: one square in any direction (nước đi thông thường của vua: một ô theo bất kỳ hướng nào)
    bool isNormalMove = rowDiff <= 1 && colDiff <= 1 && (rowDiff != 0 || colDiff != 0);

    // Castling move (nước đi nhập thành)
    bool isCastling = isCastlingMove(dest);
    if (isCastling)
    {
        bool isKingside = dest._col > _position._col;                             // Kiểm tra xem có phải nhập thành cánh vua không
        return isKingside ? canCastleKingside(board) : canCastleQueenside(board); // Trả về kết quả kiểm tra khả năng nhập thành tương ứng
    }

    if (!isNormalMove && !isCastling)
    {
        return false; // Nếu không phải nước đi thông thường và không phải nhập thành, thì không hợp lệ
    }

    // Check destination: empty or opponent's piece (kiểm tra ô đích: trống hoặc có quân cờ của đối phương)
    ChessPiece *pieceAtDest = board.getPiece(dest);
    return pieceAtDest == nullptr || pieceAtDest->getColor() != _color; // Hợp lệ nếu ô trống hoặc có quân khác màu
}