#pragma once
#include <SFML/Graphics.hpp>
#include "BoardView.h"
#include "TimerView.h"
#include "HistoryView.h"
#include "../chess_board.h"
#include "../chess_gui.h"
#include "../game_mode.h"
#include "../ai_player.h"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();
    void run();

private:
    // SFML window
    sf::RenderWindow window;

    // UI components
    BoardView boardView;
    TimerView timerView;
    HistoryView historyView;

    // Chess game components
    ChessBoard chessBoard;
    ChessGUI chessGUI;
    GameModeManager modeManager;
    AIPlayer aiPlayer;

    // Game state
    bool gameInitialized;

    // Private methods
    bool initialize();
    void processEvents();
    void update();
    void render();

    // Event handling
    void handleGameEvent(const sf::Event &event);
    void handleGameOverEvent(const sf::Event &event);

    // AI handling
    bool isAICurrentTurn(Color currentTurn);
    void handleAIMove(Color aiColor);

    // Game state management
    void handleGameOver();
};