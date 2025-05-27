#include "TimerView.h"
#include <iostream>
#include <iomanip>
#include <sstream>

TimerView::TimerView()
    : whiteTimeSeconds(300), // Default 5 minutes
      blackTimeSeconds(300),
      whiteTurn(true),
      lastUpdate(std::chrono::steady_clock::now())
{

    // Load font (you might need to adjust path)
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font for TimerView" << std::endl;
        // Try default system font or handle error
    }

    // Setup text objects
    whiteText.setFont(font);
    whiteText.setCharacterSize(24);
    whiteText.setFillColor(sf::Color::White);
    whiteText.setPosition(850, 750); // Adjust position as needed

    blackText.setFont(font);
    blackText.setCharacterSize(24);
    blackText.setFillColor(sf::Color::Black);
    blackText.setPosition(850, 50); // Adjust position as needed

    setMode(TimeControl::Blitz); // Default mode
    updateClock();
}

void TimerView::setMode(TimeControl mode)
{
    switch (mode)
    {
    case TimeControl::Blitz:
        whiteTimeSeconds = blackTimeSeconds = 5 * 60; // 5 minutes
        break;
    case TimeControl::Rapid:
        whiteTimeSeconds = blackTimeSeconds = 15 * 60; // 15 minutes
        break;
    case TimeControl::Classical:
        whiteTimeSeconds = blackTimeSeconds = 30 * 60; // 30 minutes
        break;
    }
    updateClock();
}

void TimerView::update()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate);

    if (elapsed.count() >= 1)
    { // Update every second
        if (whiteTurn)
        {
            whiteTimeSeconds -= elapsed.count();
            if (whiteTimeSeconds < 0)
                whiteTimeSeconds = 0;
        }
        else
        {
            blackTimeSeconds -= elapsed.count();
            if (blackTimeSeconds < 0)
                blackTimeSeconds = 0;
        }

        updateClock();
        lastUpdate = now;
    }
}

void TimerView::switchTurn()
{
    whiteTurn = !whiteTurn;
    lastUpdate = std::chrono::steady_clock::now();
}

void TimerView::draw(sf::RenderWindow &window)
{
    // Add background rectangles for better visibility
    sf::RectangleShape whiteBackground(sf::Vector2f(120, 40));
    whiteBackground.setPosition(845, 745);
    whiteBackground.setFillColor(sf::Color(50, 50, 50, 200));
    window.draw(whiteBackground);

    sf::RectangleShape blackBackground(sf::Vector2f(120, 40));
    blackBackground.setPosition(845, 45);
    blackBackground.setFillColor(sf::Color(200, 200, 200, 200));
    window.draw(blackBackground);

    // Draw timer texts
    window.draw(whiteText);
    window.draw(blackText);

    // Highlight current player's timer
    if (whiteTurn)
    {
        sf::RectangleShape highlight(sf::Vector2f(125, 45));
        highlight.setPosition(842, 742);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setOutlineThickness(3);
        window.draw(highlight);
    }
    else
    {
        sf::RectangleShape highlight(sf::Vector2f(125, 45));
        highlight.setPosition(842, 42);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setOutlineThickness(3);
        window.draw(highlight);
    }
}

bool TimerView::isTimeUp() const
{
    return (whiteTimeSeconds <= 0 && whiteTurn) || (blackTimeSeconds <= 0 && !whiteTurn);
}

void TimerView::updateClock()
{
    whiteText.setString("White: " + formatTime(whiteTimeSeconds));
    blackText.setString("Black: " + formatTime(blackTimeSeconds));
}

std::string TimerView::formatTime(int seconds) const
{
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << remainingSeconds;

    return ss.str();
}