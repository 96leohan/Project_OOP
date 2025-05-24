#include "GameWindow.h"

GameWindow::GameWindow()
    : window(sf::VideoMode(900, 600), "C++ Chess Game") {}

void GameWindow::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameWindow::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void GameWindow::update() {
    // Cập nhật logic nếu cần
}

void GameWindow::render() {
    window.clear(sf::Color::White);
    boardView.draw(window);
    timerView.draw(window);
    historyView.draw(window);
    window.display();
}
