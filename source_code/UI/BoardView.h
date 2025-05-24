#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BoardView {
public:
    BoardView();
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape squares[8][8];
    void initBoard();
};
