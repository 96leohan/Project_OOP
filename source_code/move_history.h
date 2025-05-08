// move_histosy.h
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
