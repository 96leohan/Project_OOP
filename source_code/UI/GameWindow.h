#pragma once
#include <SFML/Graphics.hpp>
#include "BoardView.h"
#include "TimerView.h"
#include "HistoryView.h"

class GameWindow {
public:
    GameWindow();
    void run();

private:
    sf::RenderWindow window;
    BoardView boardView;
    TimerView timerView;
    HistoryView historyView;

    void processEvents();
    void update();
    void render();
};
