#include "GameWindow.h"
#include "../chess_board.h"
#include "../chess_gui.h"
#include "../game_mode.h"
#include "../ai_player.h"
#include <iostream>

// Forward declarations
PieceType getPromotionChoiceGUI(sf::RenderWindow &window, const sf::Font &font);
extern sf::RenderWindow *g_window;
extern sf::Font *g_fontForPromotion;

GameWindow::GameWindow()
    : window(sf::VideoMode(900, 1000), "Chess Game"),
      chessBoard(),
      chessGUI(&window),
      modeManager(),
      aiPlayer(Color::BLACK, modeManager.getAIDifficulty()),
      gameInitialized(false)
{

    window.setFramerateLimit(60);

    // Set global variables for pawn promotion
    g_window = &window;
}

GameWindow::~GameWindow()
{
    g_window = nullptr;
    g_fontForPromotion = nullptr;
}

void GameWindow::run()
{
    if (!initialize())
    {
        std::cerr << "Failed to initialize game!" << std::endl;
        return;
    }

    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

bool GameWindow::initialize()
{
    if (!chessGUI.loadResources())
    {
        std::cerr << "Failed to load GUI resources!" << std::endl;
        return false;
    }

    // Set font for pawn promotion
    g_fontForPromotion = &chessGUI.getFont();

    // Initialize chess board
    chessBoard.initializeBoard();

    gameInitialized = true;
    return true;
}

void GameWindow::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        if (!gameInitialized)
            continue;

        if (!chessBoard.isGameOver())
        {
            handleGameEvent(event);
        }
        else
        {
            handleGameOverEvent(event);
        }
    }
}

void GameWindow::handleGameEvent(const sf::Event &event)
{
    Color currentTurn = chessBoard.getCurrentTurn();
    bool isAITurn = isAICurrentTurn(currentTurn);

    if (isAITurn)
    {
        // AI makes a move
        handleAIMove(currentTurn);
    }
    else
    {
        // Human player's turn
        chessGUI.handleEvent(event, chessBoard);
    }
}

void GameWindow::handleGameOverEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
    {
        // Reset game
        chessBoard.initializeBoard();
        chessGUI.clearSelection();
        chessGUI.setLastMove(Position(-1, -1), Position(-1, -1));
        std::cout << "Game reset!" << std::endl;
    }
}

bool GameWindow::isAICurrentTurn(Color currentTurn)
{
    GameMode currentMode = modeManager.getCurrentMode();

    if (currentMode == GameMode::HUMAN_VS_AI && currentTurn == Color::BLACK)
    {
        return true;
    }
    else if (currentMode == GameMode::AI_VS_HUMAN && currentTurn == Color::WHITE)
    {
        return true;
    }

    return false;
}

void GameWindow::handleAIMove(Color aiColor)
{
    aiPlayer.setColor(aiColor);
    aiPlayer.setDifficulty(modeManager.getAIDifficulty());

    std::cout << "AI (" << (aiColor == Color::WHITE ? "White" : "Black")
              << ") is thinking..." << std::endl;

    auto aiMove = aiPlayer.getBestMove(chessBoard);

    if (chessBoard.movePiece(aiMove.first, aiMove.second))
    {
        chessGUI.setLastMove(aiMove.first, aiMove.second);
        chessGUI.clearSelection();

        std::cout << "AI moved: " << aiMove.first.toAlgebraic()
                  << " to " << aiMove.second.toAlgebraic() << std::endl;
    }
    else
    {
        std::cerr << "AI failed to make a valid move!" << std::endl;
    }
}

void GameWindow::update()
{
    if (!gameInitialized)
        return;

    // Update timer view
    timerView.update();

    // Check if time is up
    if (timerView.isTimeUp())
    {
        std::cout << "Time's up! Game over." << std::endl;
        // Handle time up logic here
    }

    // Check for game over conditions
    if (chessBoard.isGameOver())
    {
        handleGameOver();
    }
}

void GameWindow::handleGameOver()
{
    // Display game over message
    std::string gameOverMessage;

    if (chessBoard.isCheckmate())
    {
        Color winner = (chessBoard.getCurrentTurn() == Color::WHITE) ? Color::BLACK : Color::WHITE;
        gameOverMessage = (winner == Color::WHITE ? "White" : "Black") + std::string(" wins by checkmate!");
    }
    else if (chessBoard.isStalemate())
    {
        gameOverMessage = "Game ended in stalemate!";
    }
    else if (chessBoard.isDraw())
    {
        gameOverMessage = "Game ended in a draw!";
    }

    if (!gameOverMessage.empty())
    {
        std::cout << gameOverMessage << std::endl;
        std::cout << "Press 'R' to reset the game." << std::endl;
    }
}

void GameWindow::render()
{
    window.clear(sf::Color(128, 128, 128));

    if (gameInitialized)
    {
        // Draw board view
        boardView.draw(window);

        // Draw chess pieces using ChessGUI
        chessGUI.draw(chessBoard);

        // Draw UI components
        timerView.draw(window);
        historyView.draw(window);
    }

    window.display();
}