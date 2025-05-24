#include "BoardView.h"

BoardView::BoardView() {
    initBoard();
}

void BoardView::initBoard() {
    const float tileSize = 60.f;
    for (int y = 0; y < 8; ++y)
        for (int x = 0; x < 8; ++x) {
            squares[y][x].setSize({tileSize, tileSize});
            squares[y][x].setPosition(x * tileSize, y * tileSize);
            squares[y][x].setFillColor((x + y) % 2 == 0 ? sf::Color::White : sf::Color(125, 135, 150));
        }
}

void BoardView::draw(sf::RenderWindow& window) {
    for (int y = 0; y < 8; ++y)
        for (int x = 0; x < 8; ++x)
            window.draw(squares[y][x]);
}
