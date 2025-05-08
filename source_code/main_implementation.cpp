// source/main_gui.cpp
#include <SFML/Graphics.hpp>
#include "chess_board.h"
#include "chess_gui.h"
#include "game_mode.h" // If you're using it
#include "ai_player.h" // If you're using it

// (Pawn promotion choice - very basic for now)
PieceType getPromotionChoiceGUI(sf::RenderWindow &window, const sf::Font &font)
{
    sf::Text promptText("Promote Pawn to: (Q)ueen (R)ook (B)ishop (N)ight", font, 20);
    promptText.setFillColor(sf::Color::Black);
    promptText.setPosition(50, 50); // Adjust position as needed

    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(200, 200, 200, 150)); // Semi-transparent background

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return PieceType::QUEEN; // Default or handle exit
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Q:
                    return PieceType::QUEEN;
                case sf::Keyboard::R:
                    return PieceType::ROOK;
                case sf::Keyboard::B:
                    return PieceType::BISHOP;
                case sf::Keyboard::N:
                    return PieceType::KNIGHT; // Or K for Knight if N is used elsewhere
                default:
                    break;
                }
            }
        }
        window.clear(sf::Color::White); // Or your GUI's current drawing
        // gui.draw(board); // Redraw board behind prompt
        window.draw(background);
        window.draw(promptText);
        window.display();
    }
    return PieceType::QUEEN; // Should not be reached if window closes
}

// Update ChessBoard's promotePawn to accept a chosen type, or have GUI manage this
// For now, let's assume the GUI will handle the choice and tell the board
// Or, we modify ChessBoard::promotePawn to be more flexible.
// Let's try to call promotePawn from ChessBoard, and it will call a GUI function.

// A bit of a hack: global pointer to GUI for pawn promotion callback
ChessGUI *g_chessGUI = nullptr; // Initialize to nullptr
sf::Font *g_fontForPromotion = nullptr;

// This function will be called by ChessBoard::promotePawn
PieceType askUserForPromotionChoice(sf::RenderWindow &window)
{
    if (g_chessGUI && g_fontForPromotion)
    {
        return getPromotionChoiceGUI(window, *g_fontForPromotion);
    }
    return PieceType::QUEEN; // Default if GUI not set
}

// You'll need to modify ChessBoard::promotePawn to call a function like askUserForPromotionChoice
// OR, handle promotion entirely within the GUI's move logic before calling board.movePiece
// (or after, if movePiece can signal that promotion is needed).

// For simplicity, the ChessBoard::promotePawn from your previous example
// already handles console input. We need to adapt that for GUI.
// One way: Modify ChessBoard::promotePawn
/*
void ChessBoard::promotePawn(const Position &pos, PieceType promotionPiece) // Added PieceType
{
    ChessPiece *pawn = getPiece(pos);
    Color color = pawn->getColor();
    _board[pos._row][pos._col].reset(); // Remove pawn

    switch (promotionPiece)
    {
    case PieceType::QUEEN:
        _board[pos._row][pos._col] = std::make_unique<Queen>(color, pos);
        break;
    // ... other cases ...
    default: // Queen by default
        _board[pos._row][pos._col] = std::make_unique<Queen>(color, pos);
        break;
    }
    std::cout << "Pawn promoted!" << std::endl; // Keep for console, GUI will show
}
*/
// And then in ChessGUI::handleEvent, if promotion is detected:
// PieceType choice = getPromotionChoiceGUI(*window, font);
// board.promotePawn(targetPosition, choice);
// This is complex because movePiece internally calls promotePawn.
// It's better if movePiece can return a status indicating promotion is needed,
// or if ChessBoard::promotePawn can somehow query the GUI.

// The path of least resistance for now:
// Let ChessBoard::movePiece try to promote and if it finds a pawn needs promotion,
// it can call a globally accessible function (passed via a setter or global)
// that triggers the GUI prompt. This is not ideal design but works for a start.

int main()
{
    unsigned int windowWidth = 900;   // boardSize (800) + 2*boardOffsetX (50)
    unsigned int windowHeight = 1000; // boardSize (800) + 2*boardOffsetY (50) + statusTextHeight (100)

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Chess");
    window.setFramerateLimit(60);

    ChessBoard board;      // Your game logic
    ChessGUI gui(&window); // Your GUI class
    g_chessGUI = &gui;     // For pawn promotion callback (simplistic)
    // You'll also need to pass the font to the promotion function, e.g., make gui.font public or pass it.

    if (!gui.loadResources())
    {
        return -1; // Error loading resources
    }
    g_fontForPromotion = &gui.getFont(); // Add a getter for font in ChessGUI

    GameModeManager modeManager;                                    // Optional, for Human vs AI
    AIPlayer aiPlayer(Color::BLACK, modeManager.getAIDifficulty()); // Default AI

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Pass event to GUI to handle piece selection/movement
            if (!board.isGameOver())
            {
                // Check if it's AI's turn (before human input handling)
                bool isAITurn = false;
                Color currentTurn = board.getCurrentTurn();
                if (modeManager.getCurrentMode() == GameMode::HUMAN_VS_AI && currentTurn == Color::BLACK)
                { // Assuming AI is Black
                    isAITurn = true;
                }
                else if (modeManager.getCurrentMode() == GameMode::AI_VS_HUMAN && currentTurn == Color::WHITE)
                { // Assuming AI is White
                    isAITurn = true;
                }

                if (isAITurn)
                {
                    // AI makes a move
                    aiPlayer.setColor(currentTurn); // Make sure AI knows its color
                    aiPlayer.setDifficulty(modeManager.getAIDifficulty());
                    std::cout << "AI (" << (currentTurn == Color::WHITE ? "White" : "Black") << ") is thinking..." << std::endl;
                    auto aiMove = aiPlayer.getBestMove(board);
                    if (board.movePiece(aiMove.first, aiMove.second))
                    {
                        gui.setLastMove(aiMove.first, aiMove.second);
                        gui.clearSelection(); // Important after AI move
                        std::cout << "AI moved: " << aiMove.first.toAlgebraic() << " to " << aiMove.second.toAlgebraic() << std::endl;
                    }
                    else
                    {
                        std::cerr << "AI failed to make a valid move!" << std::endl;
                        // This indicates a problem with AI or game state
                    }
                }
                else
                {
                    // Human player's turn
                    gui.handleEvent(event, board);
                }
            }
            else
            { // Game is over
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                { // 'R' to reset
                    board.initializeBoard();
                    gui.clearSelection();
                    gui.setLastMove(Position(-1, -1), Position(-1, -1)); // Clear last move highlight
                }
            }
        }

        window.clear(sf::Color(128, 128, 128)); // A background color
        gui.draw(board);                        // Draw all GUI elements
        window.display();
    }

    g_chessGUI = nullptr;
    g_fontForPromotion = nullptr;
    return 0;
}