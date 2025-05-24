#include "TimerView.h"

TimerView::TimerView() {
    font.loadFromFile("resources/font.ttf");

    whiteText.setFont(font);
    whiteText.setCharacterSize(20);
    whiteText.setFillColor(sf::Color::Black);
    whiteText.setPosition(500, 50);

    blackText.setFont(font);
    blackText.setCharacterSize(20);
    blackText.setFillColor(sf::Color::Black);
    blackText.setPosition(500, 500);

    setMode(TimeControl::Blitz); // mặc định
    lastUpdate = std::chrono::steady_clock::now();
    whiteTurn = true;
}

void TimerView::setMode(TimeControl mode) {
    switch (mode) {
        case TimeControl::Blitz:
            whiteTimeSeconds = blackTimeSeconds = 5 * 60;
            break;
        case TimeControl::Rapid:
            whiteTimeSeconds = blackTimeSeconds = 15 * 60;
            break;
        case TimeControl::Classical:
            whiteTimeSeconds = blackTimeSeconds = 30 * 60;
            break;
    }
    updateClock();
    lastUpdate = std::chrono::steady_clock::now();
}

void TimerView::update() {
    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();
    if (elapsed > 0) {
        if (whiteTurn)
            whiteTimeSeconds -= elapsed;
        else
            blackTimeSeconds -= elapsed;
        lastUpdate = now;
        updateClock();
    }
}

void TimerView::updateClock() {
    whiteText.setString("White: " + formatTime(std::max(0, whiteTimeSeconds)));
    blackText.setString("Black: " + formatTime(std::max(0, blackTimeSeconds)));
}

std::string TimerView::formatTime(int seconds) const {
    int min = seconds / 60;
    int sec = seconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", min, sec);
    return std::string(buffer);
}

void TimerView::draw(sf::RenderWindow& window) {
    window.draw(whiteText);
    window.draw(blackText);
}

void TimerView::switchTurn() {
    whiteTurn = !whiteTurn;
    lastUpdate = std::chrono::steady_clock::now();
}

bool TimerView::isTimeUp() const {
    return whiteTurn ? (whiteTimeSeconds <= 0) : (blackTimeSeconds <= 0);
}
