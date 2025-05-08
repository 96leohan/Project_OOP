// move.h
#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "position.h"
#include "chess_piece.h"

// Lớp Move đại diện cho một nước đi trong ván cờ
class Move
{
private:
    Position _from;           // Vị trí bắt đầu
    Position _to;             // Vị trí đích
    PieceType _pieceType;     // Loại quân cờ được di chuyển
    Color _pieceColor;        // Màu của quân cờ được di chuyển
    bool _isCapture;          // Có bắt quân hay không
    PieceType _capturedType;  // Loại quân bị bắt (nếu có)
    bool _isCheck;            // Nước đi này gây chiếu không
    bool _isCheckmate;        // Nước đi này gây chiếu hết không
    bool _isCastling;         // Nước đi này là nhập thành không
    bool _isPromotion;        // Nước đi này là phong cấp tốt không
    PieceType _promotionType; // Loại quân được phong cấp thành (nếu có)

public:
    // Constructor
    Move(const Position &from, const Position &to, PieceType pieceType, Color pieceColor,
         bool isCapture = false, PieceType capturedType = PieceType::PAWN,
         bool isCheck = false, bool isCheckmate = false,
         bool isCastling = false, bool isPromotion = false,
         PieceType promotionType = PieceType::QUEEN);

    // Các phương thức getter
    Position getFrom() const { return _from; }
    Position getTo() const { return _to; }
    PieceType getPieceType() const { return _pieceType; }
    Color getPieceColor() const { return _pieceColor; }
    bool isCapture() const { return _isCapture; }
    PieceType getCapturedType() const { return _capturedType; }
    bool isCheck() const { return _isCheck; }
    bool isCheckmate() const { return _isCheckmate; }
    bool isCastling() const { return _isCastling; }
    bool isPromotion() const { return _isPromotion; }
    PieceType getPromotionType() const { return _promotionType; }

    // Phương thức để chuyển nước đi thành ký hiệu chuẩn (Algebraic Notation)
    std::string toAlgebraic() const;

    // Phương thức để chuyển nước đi thành xâu ký tự dễ đọc
    std::string toString() const;

    // Các phương thức setter để cập nhật thông tin về kiểm/chiếu hết sau khi di chuyển
    void setCheck(bool isCheck) { _isCheck = isCheck; }
    void setCheckmate(bool isCheckmate) { _isCheckmate = isCheckmate; }
};

#endif // MOVE_H

// move.cpp
#include "move.h"
#include <sstream>

Move::Move(const Position &from, const Position &to, PieceType pieceType, Color pieceColor,
           bool isCapture, PieceType capturedType, bool isCheck, bool isCheckmate,
           bool isCastling, bool isPromotion, PieceType promotionType)
    : _from(from), _to(to), _pieceType(pieceType), _pieceColor(pieceColor),
      _isCapture(isCapture), _capturedType(capturedType), _isCheck(isCheck),
      _isCheckmate(isCheckmate), _isCastling(isCastling), _isPromotion(isPromotion),
      _promotionType(promotionType)
{
}

std::string Move::toAlgebraic() const
{
    std::string notation;

    // Đặc biệt cho nhập thành
    if (_isCastling)
    {
        if (_to._col > _from._col)
        {
            return "O-O"; // Nhập thành cánh vua
        }
        else
        {
            return "O-O-O"; // Nhập thành cánh hậu
        }
    }

    // Thêm ký hiệu quân cờ (trừ tốt)
    if (_pieceType != PieceType::PAWN)
    {
        switch (_pieceType)
        {
        case PieceType::KNIGHT:
            notation += "N";
            break;
        case PieceType::BISHOP:
            notation += "B";
            break;
        case PieceType::ROOK:
            notation += "R";
            break;
        case PieceType::QUEEN:
            notation += "Q";
            break;
        case PieceType::KING:
            notation += "K";
            break;
        default:
            break;
        }
    }

    // Thêm vị trí xuất phát (đối với tốt chỉ khi có bắt quân)
    if (_pieceType == PieceType::PAWN && _isCapture)
    {
        notation += _from.toAlgebraic()[0]; // Chỉ cần cột xuất phát của tốt khi bắt quân
    }

    // Thêm ký hiệu bắt quân
    if (_isCapture)
    {
        notation += "x";
    }

    // Thêm vị trí đích
    notation += _to.toAlgebraic();

    // Thêm ký hiệu phong cấp
    if (_isPromotion)
    {
        notation += "=";
        switch (_promotionType)
        {
        case PieceType::KNIGHT:
            notation += "N";
            break;
        case PieceType::BISHOP:
            notation += "B";
            break;
        case PieceType::ROOK:
            notation += "R";
            break;
        case PieceType::QUEEN:
            notation += "Q";
            break;
        default:
            break;
        }
    }

    // Thêm ký hiệu chiếu và chiếu hết
    if (_isCheckmate)
    {
        notation += "#";
    }
    else if (_isCheck)
    {
        notation += "+";
    }

    return notation;
}

std::string Move::toString() const
{
    std::stringstream ss;

    // Lấy màu quân cờ
    ss << (_pieceColor == Color::WHITE ? "White" : "Black") << " ";

    // Mô tả nước đi
    if (_isCastling)
    {
        if (_to._col > _from._col)
        {
            ss << "castled kingside (O-O)";
        }
        else
        {
            ss << "castled queenside (O-O-O)";
        }
    }
    else
    {
        // Mô tả quân cờ
        switch (_pieceType)
        {
        case PieceType::PAWN:
            ss << "Pawn";
            break;
        case PieceType::KNIGHT:
            ss << "Knight";
            break;
        case PieceType::BISHOP:
            ss << "Bishop";
            break;
        case PieceType::ROOK:
            ss << "Rook";
            break;
        case PieceType::QUEEN:
            ss << "Queen";
            break;
        case PieceType::KING:
            ss << "King";
            break;
        }

        // Mô tả chuyển động
        ss << " moved from " << _from.toAlgebraic() << " to " << _to.toAlgebraic();

        // Thêm thông tin về bắt quân
        if (_isCapture)
        {
            ss << ", capturing ";
            switch (_capturedType)
            {
            case PieceType::PAWN:
                ss << "Pawn";
                break;
            case PieceType::KNIGHT:
                ss << "Knight";
                break;
            case PieceType::BISHOP:
                ss << "Bishop";
                break;
            case PieceType::ROOK:
                ss << "Rook";
                break;
            case PieceType::QUEEN:
                ss << "Queen";
                break;
            case PieceType::KING:
                ss << "King";
                break;
            }
        }

        // Thêm thông tin về phong cấp
        if (_isPromotion)
        {
            ss << ", promoted to ";
            switch (_promotionType)
            {
            case PieceType::KNIGHT:
                ss << "Knight";
                break;
            case PieceType::BISHOP:
                ss << "Bishop";
                break;
            case PieceType::ROOK:
                ss << "Rook";
                break;
            case PieceType::QUEEN:
                ss << "Queen";
                break;
            default:
                break;
            }
        }
    }

    // Thêm thông tin về chiếu/chiếu hết
    if (_isCheckmate)
    {
        ss << ", checkmate!";
    }
    else if (_isCheck)
    {
        ss << ", check!";
    }

    return ss.str();
}

// move_history.h
#ifndef MOVE_HISTORY_H
#define MOVE_HISTORY_H

#include <vector>
#include <string>
#include "move.h"

// Lớp MoveHistory để lưu trữ và quản lý lịch sử nước đi trong ván cờ
class MoveHistory
{
private:
    std::vector<Move> _moves; // Danh sách các nước đi

public:
    // Constructor
    MoveHistory() = default;

    // Thêm một nước đi vào lịch sử
    void addMove(const Move &move);

    // Xóa tất cả nước đi (dùng khi bắt đầu ván mới)
    void clear();

    // Lấy số lượng nước đi đã thực hiện
    size_t getSize() const;

    // Lấy nước đi cuối cùng
    const Move *getLastMove() const;

    // Hiển thị lịch sử nước đi theo định dạng ngắn gọn
    void displayShort() const;

    // Hiển thị lịch sử nước đi với mô tả chi tiết
    void displayDetailed() const;

    // Xuất lịch sử nước đi ra file (tùy chọn)
    bool saveToFile(const std::string &filename) const;

    // Lấy toàn bộ lịch sử dưới dạng chuỗi ký tự
    std::string toString() const;
};

#endif // MOVE_HISTORY_H
