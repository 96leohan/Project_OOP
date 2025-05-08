// chess_board.h
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
#include "move_history.h" // Thêm include cho MoveHistory

class ChessBoard
{
private:
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> _board;
    Color _currentTurn;
    bool _gameOver;
    MoveHistory _moveHistory; // Thêm đối tượng MoveHistory để lưu trữ lịch sử nước đi

    // Các phương thức hỗ trợ
    bool isGameOver() const;
    bool isCheckmate(Color color) const;
    bool isStalemate(Color color) const;

public:
    ChessBoard();
    ~ChessBoard() = default;
    // Copy constructor
    ChessBoard(const ChessBoard &other);
    // Assignment operator
    ChessBoard &operator=(const ChessBoard &other);

    void initializeBoard();
    void display() const;

    ChessPiece *getPiece(const Position &pos) const;
    bool movePiece(const Position &from, const Position &to);
    Color getCurrentTurn() const;
    bool isGameOver() const;
    void promotePawn(const Position &pos);

    // Thêm các phương thức liên quan đến lịch sử nước đi
    void displayMoveHistory(bool detailed = false) const;    // Hiển thị lịch sử nước đi
    bool saveMoveHistory(const std::string &filename) const; // Lưu lịch sử nước đi vào file
    void clearMoveHistory();                                 // Xóa lịch sử nước đi
    const MoveHistory &getMoveHistory() const;               // Lấy đối tượng MoveHistory
};

#endif // CHESS_BOARD_H

// Cập nhật các phương thức trong chess_board_implementation.cpp
#include "chess_board.h"
#include <iostream>
#include <limits>
#include <cctype>

// Không thay đổi constructor và các phương thức khác...

// Cập nhật phương thức initializeBoard để xóa lịch sử nước đi khi khởi tạo bàn cờ mới
void ChessBoard::initializeBoard()
{
    // Xóa lịch sử nước đi khi tạo bàn cờ mới
    _moveHistory.clear();

    // Phần còn lại của phương thức không thay đổi...
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            _board[i][j] = nullptr;
        }
    }

    // Thiết lập các quân cờ Trắng
    for (int col = 0; col < 8; ++col)
    {
        _board[6][col] = std::make_unique<Pawn>(Color::WHITE, Position(6, col));
    }

    _board[7][0] = std::make_unique<Rook>(Color::WHITE, Position(7, 0));
    _board[7][1] = std::make_unique<Knight>(Color::WHITE, Position(7, 1));
    _board[7][2] = std::make_unique<Bishop>(Color::WHITE, Position(7, 2));
    _board[7][3] = std::make_unique<Queen>(Color::WHITE, Position(7, 3));
    _board[7][4] = std::make_unique<King>(Color::WHITE, Position(7, 4));
    _board[7][5] = std::make_unique<Bishop>(Color::WHITE, Position(7, 5));
    _board[7][6] = std::make_unique<Knight>(Color::WHITE, Position(7, 6));
    _board[7][7] = std::make_unique<Rook>(Color::WHITE, Position(7, 7));

    // Thiết lập các quân cờ Đen
    for (int col = 0; col < 8; ++col)
    {
        _board[1][col] = std::make_unique<Pawn>(Color::BLACK, Position(1, col));
    }

    _board[0][0] = std::make_unique<Rook>(Color::BLACK, Position(0, 0));
    _board[0][1] = std::make_unique<Knight>(Color::BLACK, Position(0, 1));
    _board[0][2] = std::make_unique<Bishop>(Color::BLACK, Position(0, 2));
    _board[0][3] = std::make_unique<Queen>(Color::BLACK, Position(0, 3));
    _board[0][4] = std::make_unique<King>(Color::BLACK, Position(0, 4));
    _board[0][5] = std::make_unique<Bishop>(Color::BLACK, Position(0, 5));
    _board[0][6] = std::make_unique<Knight>(Color::BLACK, Position(0, 6));
    _board[0][7] = std::make_unique<Rook>(Color::BLACK, Position(0, 7));

    _currentTurn = Color::WHITE;
    _gameOver = false;

    std::cout << "Chess board initialized with all pieces in starting positions." << std::endl;
}

// Cập nhật phương thức movePiece để ghi lại các nước đi vào lịch sử
bool ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *piece = getPiece(from);

    // Các kiểm tra cơ bản
    if (piece == nullptr || !to.isValid())
    {
        return false;
    }

    if (piece->getColor() != _currentTurn)
    {
        std::cout << "It's not your turn!" << std::endl;
        return false;
    }

    if (!piece->isValidMove(*this, to))
    {
        std::cout << "Invalid move for this piece!" << std::endl;
        return false;
    }

    // Thông tin cho Move object
    PieceType pieceType = piece->getType();
    Color pieceColor = piece->getColor();
    bool isCapture = (getPiece(to) != nullptr);
    PieceType capturedType = isCapture ? getPiece(to)->getType() : PieceType::PAWN;
    bool isCastling = (pieceType == PieceType::KING && std::abs(to._col - from._col) > 1);
    bool isPromotion = false;
    PieceType promotionType = PieceType::QUEEN;

    // Trường hợp đặc biệt cho Tốt
    if (piece->getType() == PieceType::PAWN)
    {
        auto pawn = dynamic_cast<Pawn *>(piece);
        pawn->_hasMoved = true;

        // Kiểm tra phong cấp
        if (pawn->canPromote())
        {
            isPromotion = true;
        }
    }
    // Trường hợp đặc biệt cho Xe
    else if (piece->getType() == PieceType::ROOK)
    {
        dynamic_cast<Rook *>(piece)->setHasMoved(true);
    }
    // Trường hợp đặc biệt cho Vua
    else if (piece->getType() == PieceType::KING)
    {
        auto king = dynamic_cast<King *>(piece);

        // Xử lý nhập thành
        if (king->isCastlingMove(to))
        {
            int row = piece->getPosition()._row;
            int fromCol = piece->getPosition()._col;
            int toCol = to._col;

            Position rookFromPos(row, toCol > fromCol ? 7 : 0);
            Position rookToPos(row, toCol > fromCol ? 5 : 3);

            auto rook = std::move(_board[rookFromPos._row][rookFromPos._col]);
            _board[rookToPos._row][rookToPos._col] = std::move(rook);
            _board[rookFromPos._row][rookFromPos._col] = nullptr;

            ChessPiece *rookPiece = getPiece(rookToPos);
            rookPiece->setPosition(rookToPos);
        }

        king->_hasMoved = true;
    }

    // Lưu trữ quân cờ bị bắt (nếu có) để có thể hoàn tác nước đi nếu cần
    std::unique_ptr<ChessPiece> capturedPiece = std::move(_board[to._row][to._col]);

    // Di chuyển quân cờ
    auto movingPiece = std::move(_board[from._row][from._col]);
    _board[to._row][to._col] = std::move(movingPiece);
    piece->setPosition(to);

    // Kiểm tra xem nước đi này có đặt hoặc để vua của người chơi vào thế chiếu hay không
    if (isInCheck(_currentTurn))
    {
        // Hoàn tác nước đi
        _board[from._row][from._col] = std::move(_board[to._row][to._col]);
        _board[to._row][to._col] = std::move(capturedPiece);
        piece->setPosition(from);

        std::cout << "Invalid move: Would leave your king in check!" << std::endl;
        return false;
    }

    // Biến để theo dõi trạng thái chiếu và chiếu hết
    bool isCheck = false;
    bool isCheckmate = false;

    // Kiểm tra xem đối phương có bị chiếu hết không
    Color opponentColor = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    if (isInCheck(opponentColor))
    {
        isCheck = true;
        if (isCheckmate(opponentColor))
        {
            isCheckmate = true;
            std::cout << "Checkmate! " << (_currentTurn == Color::WHITE ? "White" : "Black") << " wins!" << std::endl;
            _gameOver = true;
        }
        else
        {
            std::cout << "Check!" << std::endl;
        }
    }

    // Xử lý phong cấp tốt
    if (piece->getType() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn->canPromote())
        {
            promotePawn(to);
            // Cập nhật loại quân được phong cấp
            ChessPiece *promotedPiece = getPiece(to);
            promotionType = promotedPiece->getType();
        }
    }

    // Tạo đối tượng Move và thêm vào lịch sử
    Move move(from, to, pieceType, pieceColor, isCapture, capturedType,
              isCheck, isCheckmate, isCastling, isPromotion, promotionType);
    _moveHistory.addMove(move);

    // Chuyển lượt đi cho người chơi khác
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true;
}

// Các phương thức mới cho lịch sử nước đi
void ChessBoard::displayMoveHistory(bool detailed) const
{
    if (detailed)
    {
        _moveHistory.displayDetailed();
    }
    else
    {
        _moveHistory.displayShort();
    }
}

bool ChessBoard::saveMoveHistory(const std::string &filename) const
{
    return _moveHistory.saveToFile(filename);
}

void ChessBoard::clearMoveHistory()
{
    _moveHistory.clear();
}

const MoveHistory &ChessBoard::getMoveHistory() const
{
    return _moveHistory;
}