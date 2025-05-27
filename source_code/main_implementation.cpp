#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI/GameWindow.h"
#include "chess_board.h"
#include "chess_gui.h"
#include "game_mode.h"
#include "ai_player.h"

// Forward declarations
PieceType getPromotionChoiceGUI(sf::RenderWindow &window, const sf::Font &font);

// Global variables for pawn promotion (temporary solution)
static sf::RenderWindow *g_window = nullptr;
static sf::Font *g_fontForPromotion = nullptr;

PieceType getPromotionChoiceGUI(sf::RenderWindow &window, const sf::Font &font)
{
    sf::Text promptText("Promote Pawn to: (Q)ueen (R)ook (B)ishop (N)ight", font, 20);
    promptText.setFillColor(sf::Color::Black);
    promptText.setPosition(50, 50);

    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(200, 200, 200, 150));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return PieceType::QUEEN;
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
                    return PieceType::KNIGHT;
                default:
                    break;
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(promptText);
        window.display();
    }
    return PieceType::QUEEN;
}

// Callback function for pawn promotion
PieceType askUserForPromotionChoice()
{
    if (g_window && g_fontForPromotion)
    {
        return getPromotionChoiceGUI(*g_window, *g_fontForPromotion);
    }
    return PieceType::QUEEN;
}

int main()
{
    try
    {
        // Create and run the game window using the UI architecture
        GameWindow gameWindow;

        // Initialize chess components
        ChessBoard board;

        // Set up AI if needed
        GameModeManager modeManager;
        AIPlayer aiPlayer(Color::BLACK, modeManager.getAIDifficulty());

        // Run the main game loop
        gameWindow.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}