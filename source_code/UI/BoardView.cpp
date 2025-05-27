#include "BoardView.h"

BoardView::BoardView()
{
    initBoard();
}

void BoardView::initBoard()
{
    const float SQUARE_SIZE = 100.0f;
    const float BOARD_OFFSET_X = 50.0f;
    const float BOARD_OFFSET_Y = 50.0f;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            squares[row][col].setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            squares[row][col].setPosition(
                BOARD_OFFSET_X + col * SQUARE_SIZE,
                BOARD_OFFSET_Y + row * SQUARE_SIZE);

            // Alternating colors for chess board
            if ((row + col) % 2 == 0)
            {
                squares[row][col].setFillColor(sf::Color(240, 217, 181)); // Light squares
            }
            else
            {
                squares[row][col].setFillColor(sf::Color(181, 136, 99)); // Dark squares
            }
        }
    }
}

void BoardView::draw(sf::RenderWindow &window)
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            window.draw(squares[row][col]);
        }
    }
}