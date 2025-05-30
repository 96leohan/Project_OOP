#include "ConsoleRenderer.h"
#include <iostream>

void ui::ConsoleRenderer::render(const Board& board) {
    clearScreen();
    std::cout << "  a b c d e f g h\n";
    for (int row = 7; row >= 0; --row) {
        std::cout << row + 1 << " ";
        for (int col = 0; col < 8; ++col) {
            auto piece = board.getPiece(Position(row, col));
            std::cout << (piece ? piece->getSymbol() : ".") << " ";
        }
        std::cout << row + 1 << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

void ui::ConsoleRenderer::highlightMove(const Position& from, const Position& to) {
    std::cout << "Moved: " << from.toString() << " -> " << to.toString() << "\n";
}

void ui::ConsoleRenderer::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
