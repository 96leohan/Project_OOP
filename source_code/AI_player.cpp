// ai_player.cpp
#include "AI_player.h"
#include <algorithm>
#include <random>
#include <iostream>

AIPlayer::AIPlayer(Color aiColor, int difficulty) : _aiColor(aiColor), _difficulty(difficulty)
{
}

std::pair<Position, Position> AIPlayer::getBestMove(ChessBoard &board)
{
    // Lấy tất cả nước đi có thể cho AI
    auto moves = getAllValidMoves(board, _aiColor);

    if (moves.empty())
    {
        return std::make_pair(Position(0, 0), Position(0, 0)); // Không có nước đi hợp lệ
    }

    // Ở chế độ dễ, chọn ngẫu nhiên trong các nước đi hợp lệ
    if (_difficulty == 1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, moves.size() - 1);
        int randomIndex = dis(gen);
        return moves[randomIndex];
    }

    // Chế độ trung bình hoặc khó, sử dụng minimax với độ sâu khác nhau
    int depth = (_difficulty == 2) ? 2 : 4; // Độ sâu 2 cho trung bình, 4 cho khó

    std::vector<MoveEvaluation> evaluatedMoves;

    // Đánh giá từng nước đi bằng minimax
    for (const auto &move : moves)
    {
        // Tạo một bản sao của bàn cờ để thử nước đi
        ChessBoard tempBoard = board;
        tempBoard.movePiece(move.first, move.second);

        // Đánh giá nước đi bằng minimax
        int score = minimax(tempBoard, depth - 1, INT_MIN, INT_MAX, false);
        evaluatedMoves.push_back(MoveEvaluation(move.first, move.second, score));
    }

    // Sắp xếp các nước đi theo điểm đánh giá (giảm dần)
    std::sort(evaluatedMoves.begin(), evaluatedMoves.end(),
              [](const MoveEvaluation &a, const MoveEvaluation &b)
              {
                  return a.score > b.score;
              });

    // Thêm một chút ngẫu nhiên vào quyết định để tránh AI luôn chơi giống nhau
    int selectionRange = std::min(3, static_cast<int>(evaluatedMoves.size()));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, selectionRange - 1);
    int selectedIndex = dis(gen);

    // Trả về nước đi được chọn
    return std::make_pair(evaluatedMoves[selectedIndex].from, evaluatedMoves[selectedIndex].to);
}

int AIPlayer::minimax(ChessBoard &board, int depth, int alpha, int beta, bool isMaximizing) const
{
    // Điều kiện dừng: đạt độ sâu mong muốn hoặc game kết thúc
    if (depth == 0 || board.isGameOver())
    {
        return evaluateBoard(board);
    }

    Color currentColor = isMaximizing ? _aiColor : ((_aiColor == Color::WHITE) ? Color::BLACK : Color::WHITE);

    // Lấy tất cả nước đi có thể cho người chơi hiện tại
    auto moves = getAllValidMoves(board, currentColor);

    if (isMaximizing)
    {
        int maxEval = INT_MIN;
        for (const auto &move : moves)
        {
            // Tạo bản sao của bàn cờ để thử nước đi
            ChessBoard tempBoard = board;
            tempBoard.movePiece(move.first, move.second);

            // Đánh giá nước đi bằng cách gọi đệ quy minimax
            int eval = minimax(tempBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);

            // Cắt tỉa Alpha-Beta
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        for (const auto &move : moves)
        {
            // Tạo bản sao của bàn cờ để thử nước đi
            ChessBoard tempBoard = board;
            tempBoard.movePiece(move.first, move.second);

            // Đánh giá nước đi bằng cách gọi đệ quy minimax
            int eval = minimax(tempBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);

            // Cắt tỉa Alpha-Beta
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

std::vector<std::pair<Position, Position>> AIPlayer::getAllValidMoves(const ChessBoard &board, Color color) const
{
    std::vector<std::pair<Position, Position>> allMoves;

    // Duyệt qua tất cả các vị trí trên bàn cờ
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Position from(row, col);
            ChessPiece *piece = board.getPiece(from);

            // Kiểm tra xem vị trí có quân cờ của màu hiện tại không
            if (piece && piece->getColor() == color)
            {
                // Lấy tất cả nước đi "pseudo-legal" của quân cờ này
                // (những nước đi hợp lệ theo luật di chuyển của quân, không quan tâm đến chiếu)
                auto possibleMoves = piece->getPossibleMoves(board);

                // Kiểm tra từng nước đi xem có hợp lệ hoàn toàn không (bao gồm cả việc không tự chiếu)
                for (const auto &to : possibleMoves)
                {
                    // Tạo một bản sao của bàn cờ để thử nước đi
                    ChessBoard tempBoard = board;
                    // Thử di chuyển quân cờ trên bản sao.
                    // Hàm movePiece() của ChessBoard giờ đây sẽ có trách nhiệm kiểm tra xem
                    // nước đi có hợp lệ hoàn toàn hay không, bao gồm cả việc có bị tự chiếu hay không.
                    if (tempBoard.movePiece(from, to))
                    {
                        allMoves.push_back(std::make_pair(from, to));
                    }
                }
            }
        }
    }

    return allMoves;
}

int AIPlayer::evaluateBoard(const ChessBoard &board) const
{
    int score = 0;

    // Duyệt qua tất cả các vị trí trên bàn cờ
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Position pos(row, col);
            ChessPiece *piece = board.getPiece(pos);

            if (piece)
            {
                // Tính điểm dựa trên giá trị của quân cờ
                int pieceValue = getPieceValue(piece);

                // Cộng điểm nếu là quân của AI, trừ điểm nếu là quân của đối thủ
                if (piece->getColor() == _aiColor)
                {
                    score += pieceValue;

                    // Bonus cho vị trí trung tâm (chỉ áp dụng cho chế độ khó)
                    if (_difficulty == 3)
                    {
                        // Ưu tiên các quân ở trung tâm bàn cờ
                        int centerDistance = std::abs(row - 3.5) + std::abs(col - 3.5);
                        score += (4 - centerDistance) * 5;

                        // Khuyến khích phát triển quân sớm
                        if (piece->getType() == PieceType::KNIGHT || piece->getType() == PieceType::BISHOP)
                        {
                            if ((piece->getColor() == Color::WHITE && row < 6) ||
                                (piece->getColor() == Color::BLACK && row > 1))
                            {
                                score += 15; // Bonus cho phát triển mã, tượng
                            }
                        }
                    }
                }
                else
                {
                    score -= pieceValue;

                    // Làm tương tự với quân của đối thủ trong chế độ khó
                    if (_difficulty == 3)
                    {
                        int centerDistance = std::abs(row - 3.5) + std::abs(col - 3.5);
                        score -= (4 - centerDistance) * 5;

                        if (piece->getType() == PieceType::KNIGHT || piece->getType() == PieceType::BISHOP)
                        {
                            if ((piece->getColor() == Color::WHITE && row < 6) ||
                                (piece->getColor() == Color::BLACK && row > 1))
                            {
                                score -= 15;
                            }
                        }
                    }
                }
            }
        }
    }

    return score;
}

int AIPlayer::getPieceValue(const ChessPiece *piece) const
{
    if (!piece)
        return 0;

    switch (piece->getType())
    {
    case PieceType::PAWN:   // Thay 'P' bằng PieceType::PAWN
        return 100;         // Tốt
    case PieceType::KNIGHT: // Thay 'N' bằng PieceType::KNIGHT
        return 320;         // Mã
    case PieceType::BISHOP: // Thay 'B' bằng PieceType::BISHOP
        return 330;         // Tượng
    case PieceType::ROOK:   // Thay 'R' bằng PieceType::ROOK
        return 500;         // Xe
    case PieceType::QUEEN:  // Thay 'Q' bằng PieceType::QUEEN
        return 900;         // Hậu
    case PieceType::KING:   // Thay 'K' bằng PieceType::KING
        return 20000;       // Vua (giá trị rất cao vì không thể mất vua)
    default:
        return 0;
    }
}