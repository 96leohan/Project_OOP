#include "HistoryView.h"
#include <sstream>

HistoryView::HistoryView() {
    font.loadFromFile("resources/font.ttf");
    historyText.setFont(font);
    historyText.setCharacterSize(14);
    historyText.setPosition(500, 150);
    historyText.setFillColor(sf::Color::Black);
    historyText.setString("Move history:");
}

void HistoryView::draw(sf::RenderWindow& window) {
    window.draw(historyText);
}

void HistoryView::addMove(const std::string& move) {
    moves.push_back(move);
    updateDisplay();
}

void HistoryView::reset() {
    moves.clear();
    updateDisplay();
}

void HistoryView::updateDisplay() {
    std::ostringstream oss;
    for (size_t i = 0; i < moves.size(); i++) {
        if (i % 2 == 0)
            oss << (i / 2 + 1) << ". ";
        oss << moves[i] << " ";
        if (i % 2 == 1)
            oss << "\n";
    }
    historyText.setString(oss.str());
}
