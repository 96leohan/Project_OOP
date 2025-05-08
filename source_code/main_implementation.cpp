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
    std::cout << "- Type 'history' to display move history\n";
    std::cout << "- Type 'detail' to display detailed move history\n";
    std::cout << "- Type 'save [filename]' to save move history to file\n";
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

void displayGameInfo(const GameModeManager &modeManager)
{
    std::cout << "Current Mode: " << modeManager.getModeString();
    if (modeManager.getCurrentMode() != GameMode::HUMAN_VS_HUMAN)
    {
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

            if (isAITurn)
            {
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
                if (board.movePiece(bestMove.first, bestMove.second))
                {
                    board.display();
                }

                continue; // Tiếp tục vòng lặp để người chơi tiếp theo
            }
            else
            {
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
        else if (lowerInput == "history")
        {
            // Hiển thị lịch sử nước đi ngắn gọn
            board.displayMoveHistory(false);
        }
        else if (lowerInput == "detail")
        {
            // Hiển thị lịch sử nước đi chi tiết
            board.displayMoveHistory(true);
        }
        else if (lowerInput.substr(0, 4) == "save")
        {
            // Lưu lịch sử nước đi vào file
            std::string filename;
            if (lowerInput.length() > 5)
            {
                filename = input.substr(5); // Lấy tên file (giữ nguyên case)
            }
            else
            {
                // Sử dụng tên file mặc định
                filename = "chess_history.txt";
            }

            if (board.saveMoveHistory(filename))
            {
                std::cout << "Move history saved to file: " << filename << "\n";
            }
            else
            {
                std::cout << "Failed to save move history to file: " << filename << "\n";
            }
        }
        else if (lowerInput == "mode")
        {
            displayModeOptions();
            std::string modeChoice;
            std::getline(std::cin, modeChoice);

            if (modeChoice == "1")
            {
                modeManager.setCurrentMode(GameMode::HUMAN_VS_HUMAN);
            }
            else if (modeChoice == "2")
            {
                modeManager.setCurrentMode(GameMode::HUMAN_VS_AI);
                aiPlayer.setColor(Color::BLACK);
            }
            else if (modeChoice == "3")
            {
                modeManager.setCurrentMode(GameMode::AI_VS_HUMAN);
                aiPlayer.setColor(Color::WHITE);
            }
            else
            {
                std::cout << "Invalid choice. Game mode unchanged.\n";
            }

            displayGameInfo(modeManager);
        }
        else if (lowerInput == "difficulty")
        {
            if (modeManager.getCurrentMode() == GameMode::HUMAN_VS_HUMAN)
            {
                std::cout << "AI difficulty setting is only relevant in AI game modes.\n";
            }
            else
            {
                displayDifficultyOptions();
                std::string diffChoice;
                std::getline(std::cin, diffChoice);

                if (diffChoice == "1")
                {
                    modeManager.setAIDifficulty(1);
                }
                else if (diffChoice == "2")
                {
                    modeManager.setAIDifficulty(2);
                }
                else if (diffChoice == "3")
                {
                    modeManager.setAIDifficulty(3);
                }
                else
                {
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

                    // Kiểm tra nếu có nước đi cuối cùng, hiển thị nó
                    const MoveHistory &history = board.getMoveHistory();
                    const Move *lastMove = history.getLastMove();
                    if (lastMove)
                    {
                        std::cout << "Last move: " << lastMove->toString() << "\n";
                    }
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