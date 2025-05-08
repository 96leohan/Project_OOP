
#ifndef PAWN_H
#define PAWN_H

#include "chess_piece.h"
#include <vector> // Thêm include này

class Pawn : public ChessPiece
{
private: // Chuyển các thuộc tính thành private
    bool _hasMoved;
    bool _enPassantVulnerable;

public:
    Pawn(Color color, const Position &pos);

    std::vector<Position> getPossibleMoves(const ChessBoard &board) const override;
    bool isValidMove(const ChessBoard &board, const Position &dest) const override;

    // Kiểm tra nếu quân tốt đã đến hàng cuối cùng để phong cấp
    bool canPromote() const;

    // Thêm các getter/setter cho các thuộc tính private
    bool hasMoved() const { return _hasMoved; }
    void setHasMoved(bool value) { _hasMoved = value; }

    bool isEnPassantVulnerable() const { return _enPassantVulnerable; }
    void setEnPassantVulnerable(bool value) { _enPassantVulnerable = value; }
};

#endif
#endif