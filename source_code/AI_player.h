// ai_player.h
#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "chess_board.h"
#include "position.h"
#include <vector>
#include <utility>

// Struct để lưu thông tin về một nước đi và điểm đánh giá của nó
struct MoveEvaluation {
    Position from;
    Position to;
    int score;
    
    MoveEvaluation(Position f, Position t, int s) : from(f), to(t), score(s) {}
};

class AIPlayer {
private:
    Color _aiColor;  // Màu quân của AI (WHITE hoặc BLACK)
    int _difficulty; // Mức độ khó (1: Dễ, 2: Trung bình, 3: Khó)
    
    // Phương thức đánh giá tình trạng bàn cờ
    int evaluateBoard(const ChessBoard& board) const;
    
    // Thuật toán Minimax với cắt tỉa Alpha-Beta
    int minimax(ChessBoard& board, int depth, int alpha, int beta, bool isMaximizing) const;
    
    // Lấy danh sách tất cả các nước đi hợp lệ cho một quân cờ
    std::vector<std::pair<Position, Position>> getAllValidMoves(const ChessBoard& board, Color color) const;
    
    // Đánh giá giá trị của một quân cờ
    int getPieceValue(const ChessPiece* piece) const;

public:
    AIPlayer(Color aiColor, int difficulty = 2);
    
    // Phương thức chính để AI đưa ra nước đi
    std::pair<Position, Position> getBestMove(ChessBoard& board);
    
    // Getter và setter cho các thuộc tính
    Color getColor() const { return _aiColor; }
    void setColor(Color color) { _aiColor = color; }
    
    int getDifficulty() const { return _difficulty; }
    void setDifficulty(int difficulty) { _difficulty = difficulty; }
};

#endif // AI_PLAYER_H