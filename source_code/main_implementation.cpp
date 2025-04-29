/*!SECTION
1. position.h và position.cpp
Các file này định nghĩa lớp Position, dùng để xử lý tọa độ trên bàn cờ:
Đại diện cho một vị trí trên bàn cờ bằng chỉ số hàng và cột (0–7)
Cung cấp chức năng chuyển đổi giữa ký hiệu đại số (ví dụ: "e4") và tọa độ nội bộ
Bao gồm kiểm tra hợp lệ để đảm bảo vị trí nằm trong phạm vi bàn cờ
Các phương thức chính gồm: fromAlgebraic(), toAlgebraic(), và isValid()

2. chess_piece.h và chess_piece.cpp
Các file này định nghĩa lớp cơ sở trừu tượng cho các quân cờ:
Định nghĩa enum class PieceType (PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING)
Định nghĩa enum class Color (WHITE, BLACK)
Chứa lớp trừu tượng ChessPiece với:
Thuộc tính cơ bản của quân cờ (loại, màu, vị trí)
Các phương thức trừu tượng để kiểm tra nước đi (sẽ được cài trong các lớp con)
Các hàm tiện ích để lấy thông tin và ký hiệu của quân cờ để hiển thị

3. chess_board.h và chess_board.cpp
Các file này triển khai bàn cờ và cơ chế chơi game:
Quản lý lưới 8x8 quân cờ bằng smart pointers
Theo dõi lượt chơi của người chơi hiện tại
Cung cấp các phương thức:
Khởi tạo bàn cờ (hiện tại là khung placeholder)
Hiển thị trạng thái bàn cờ dưới dạng văn bản
Lấy quân cờ tại một vị trí cụ thể
Di chuyển quân cờ với kiểm tra hợp lệ
Kiểm tra lượt chơi hiện tại

4. main.cpp
File này chứa điểm khởi đầu chương trình và giao diện người dùng:
Hiển thị lời chào và hướng dẫn chơi
Triển khai vòng lặp chính của trò chơi
Phân tích cú pháp đầu vào từ người chơi (nhập nước đi)
Xử lý lệnh và hiển thị bàn cờ sau mỗi lượt
Bao gồm hàm parseMove() để chuyển đổi đầu vào thành đối tượng Position

*** Trạng thái hiện tại của chương trình
Cấu trúc và kiến trúc code đã sẵn sàng
Vòng lặp trò chơi chính đã hoạt động, cho phép nhập lệnh và hiển thị bàn cờ
Cơ chế di chuyển quân cờ đã được định nghĩa nhưng chưa hoàn thiện

*** Những phần còn thiếu:
Các lớp quân cờ cụ thể (Tốt, Mã, Tượng, Xe, Hậu, Vua) kế thừa từ ChessPiece
Cài đặt thực tế cho hàm initializeBoard() để sắp xếp quân ở vị trí ban đầu
Logic kiểm tra hợp lệ cho từng loại quân
Quy tắc đặc biệt như nhập thành, bắt tốt qua đường, phong cấp
Kiểm tra chiếu và chiếu hết

Các file này tạo nên một nền tảng vững chắc cho trò chơi cờ vua của bạn, tuân theo chuẩn lập trình C++ với phân tách rõ ràng giữa các chức năng.
Bước tiếp theo là triển khai các lớp quân cờ cụ thể để biến trò chơi thành một sản phẩm hoàn chỉnh.

---------------------------------------------
Bổ sung ngày 20/4/2025
-Hoàn thành việc triển khai các lớp quân cờ cụ thể và các chức năng bổ sung

+Các lớp quân cờ cụ thể:
Pawn (Tốt): Triển khai nước đi tiêu chuẩn, di chuyển 2 ô lần đầu, bắt quân theo đường chéo
Knight (Mã): Triển khai nước đi hình chữ L
Bishop (Tượng): Triển khai nước đi theo đường chéo
Rook (Xe): Triển khai nước đi theo hàng và cột
Queen (Hậu): Triển khai nước đi theo hàng, cột và đường chéo
King (Vua): Triển khai nước đi 1 ô theo mọi hướng

+Các chức năng đặc biệt:
Phong cấp quân tốt khi đến hàng cuối cùng
Nhập thành (cả bên Vua và bên Hậu)
Kiểm tra chiếu và chiếu hết
Kiểm tra nước đi hợp lệ cho từng loại quân

+Cập nhật ChessBoard:
Khởi tạo bàn cờ với vị trí ban đầu của tất cả quân cờ
Xử lý logic di chuyển quân cờ với kiểm tra hợp lệ
Triển khai kiểm tra chiếu và chiếu hết

+Thêm các cải tiến về giao diện người dùng như hiển thị trợ giúp, xử lý đầu vào, và các lệnh bổ sung.
.Cải thiện việc triển khai ChessBoard với thiết lập quân cờ hoàn chỉnh và logic trò chơi
. Khởi tạo bàn cờ với tất cả các quân cờ ở vị trí bắt đầu của chúng.
. Triển khai quản lý trạng thái trò chơi, bao gồm chuyển lượt và điều kiện kết thúc trò chơi.
.Thêm logic cho các nước đi đặc biệt như nhập thành và phong cấp quân tốt.
. Giới thiệu các phương pháp để kiểm tra điều kiện chiếu và chiếu hết.
. Cập nhật vòng lặp trò chơi chính để xử lý lệnh của người dùng và hiển thị trạng thái trò chơi hiệu quả.


*/

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "chess_board.h"
#include "position.h"
#include "ai_player.h"
#include "game_mode.h"

// Parse user move command (e.g., "e2 e4")
bool parseMove(const std::string &input, Position &from, Position &to)
{
    // Remove leading/trailing whitespace and convert to lowercase
    std::string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);
    std::transform(trimmed.begin(), trimmed.end(), trimmed.begin(), ::tolower);

    // Simple parsing - expects format like "e2 e4"
    size_t spacePos = trimmed.find(' ');
    if (spacePos == std::string::npos || spacePos == 0 || spacePos == trimmed.length() - 1)
    {
        return false;
    }

    std::string fromStr = trimmed.substr(0, spacePos);
    std::string toStr = trimmed.substr(spacePos + 1);

    try
    {
        from = Position::fromAlgebraic(fromStr);
        to = Position::fromAlgebraic(toStr);
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
}

void displayHelp()
{
    std::cout << "\n=== Chess Commands ===\n";
    std::cout << "- Enter moves in format 'e2 e4' (from to)\n";
    std::cout << "- Type 'help' to display this help\n";
    std::cout << "- Type 'reset' to restart the game\n";
    std::cout << "- Type 'quit' or 'exit' to exit the game\n";
    std::cout << "- Type 'board' to display the current board\n";
    std::cout << "- Type 'mode' to change game mode (human vs human, human vs AI, AI vs human)\n";
    std::cout << "- Type 'difficulty' to change AI difficulty (easy, medium, hard)\n";
    std::cout << "=====================\n\n";
}

void displayModeOptions()
{
    std::cout << "\n=== Game Mode Options ===\n";
    std::cout << "1. Human vs Human\n";
    std::cout << "2. Human vs AI (You play White)\n";
    std::cout << "3. AI vs Human (You play Black)\n";
    std::cout << "Enter your choice (1-3): ";
}

void displayDifficultyOptions()
{
    std::cout << "\n=== AI Difficulty Options ===\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
    std::cout << "Enter your choice (1-3): ";
}

void displayGameInfo(const GameModeManager& modeManager)
{
    std::cout << "Current Mode: " << modeManager.getModeString();
    if (modeManager.getCurrentMode() != GameMode::HUMAN_VS_HUMAN) {
        std::cout << " (AI Difficulty: " << modeManager.getDifficultyString() << ")";
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "=== C++ Chess Game ===\n";
    displayHelp();

    ChessBoard board;
    GameModeManager modeManager;
    AIPlayer aiPlayer(Color::BLACK, modeManager.getAIDifficulty());
    
    board.display();
    displayGameInfo(modeManager);

    std::string input;
    while (true)
    {
        if (board.isGameOver())
        {
            std::cout << "\nGame over! Type 'reset' to start a new game or 'quit' to exit.\n";
        }
        else
        {
            Color currentPlayer = board.getCurrentTurn();
            
            // Kiểm tra xem có phải lượt của AI không
            bool isAITurn = (currentPlayer == Color::WHITE && modeManager.getCurrentMode() == GameMode::AI_VS_HUMAN) ||
                           (currentPlayer == Color::BLACK && modeManager.getCurrentMode() == GameMode::HUMAN_VS_AI);
            
            if (isAITurn) {
                std::cout << "\nAI is thinking...\n";
                
                // Đảm bảo AI chơi đúng màu
                aiPlayer.setColor(currentPlayer);
                aiPlayer.setDifficulty(modeManager.getAIDifficulty());
                
                // Lấy nước đi tốt nhất từ AI
                auto bestMove = aiPlayer.getBestMove(board);
                
                // Hiển thị nước đi của AI
                std::string fromStr = bestMove.first.toAlgebraic();
                std::string toStr = bestMove.second.toAlgebraic();
                std::cout << "AI moves: " << fromStr << " " << toStr << "\n";
                
                // Thực hiện nước đi
                if (board.movePiece(bestMove.first, bestMove.second)) {
                    board.display();
                }
                
                continue; // Tiếp tục vòng lặp để người chơi tiếp theo
            }
            else {
                std::cout << "\n"
                          << (currentPlayer == Color::WHITE ? "White" : "Black") << " to move: ";
            }
        }

        std::getline(std::cin, input);

        // Convert input to lowercase for command comparison
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

        if (lowerInput == "quit" || lowerInput == "exit")
        {
            break;
        }
        else if (lowerInput == "help")
        {
            displayHelp();
        }
        else if (lowerInput == "reset")
        {
            std::cout << "Resetting the game...\n";
            board.initializeBoard();
            board.display();
            displayGameInfo(modeManager);
        }
        else if (lowerInput == "board")
        {
            board.display();
        }
        else if (lowerInput == "mode")
        {
            displayModeOptions();
            std::string modeChoice;
            std::getline(std::cin, modeChoice);
            
            if (modeChoice == "1") {
                modeManager.setCurrentMode(GameMode::HUMAN_VS_HUMAN);
            } else if (modeChoice == "2") {
                modeManager.setCurrentMode(GameMode::HUMAN_VS_AI);
                aiPlayer.setColor(Color::BLACK);
            } else if (modeChoice == "3") {
                modeManager.setCurrentMode(GameMode::AI_VS_HUMAN);
                aiPlayer.setColor(Color::WHITE);
            } else {
                std::cout << "Invalid choice. Game mode unchanged.\n";
            }
            
            displayGameInfo(modeManager);
        }
        else if (lowerInput == "difficulty")
        {
            if (modeManager.getCurrentMode() == GameMode::HUMAN_VS_HUMAN) {
                std::cout << "AI difficulty setting is only relevant in AI game modes.\n";
            } else {
                displayDifficultyOptions();
                std::string diffChoice;
                std::getline(std::cin, diffChoice);
                
                if (diffChoice == "1") {
                    modeManager.setAIDifficulty(1);
                } else if (diffChoice == "2") {
                    modeManager.setAIDifficulty(2);
                } else if (diffChoice == "3") {
                    modeManager.setAIDifficulty(3);
                } else {
                    std::cout << "Invalid choice. AI difficulty unchanged.\n";
                }
                
                aiPlayer.setDifficulty(modeManager.getAIDifficulty());
                displayGameInfo(modeManager);
            }
        }
        else if (!board.isGameOver())
        {
            Position from(0, 0), to(0, 0);
            if (parseMove(input, from, to))
            {
                if (board.movePiece(from, to))
                {
                    board.display();
                }
                else
                {
                    std::cout << "Invalid move! Try again.\n";
                }
            }
            else
            {
                std::cout << "Invalid input format! Use format 'e2 e4'.\n";
            }
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}