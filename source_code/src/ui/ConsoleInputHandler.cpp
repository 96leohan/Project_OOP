#include "ConsoleInputHandler.h"
#include <iostream>

std::pair<Position, Position> ui::ConsoleInputHandler::getMove() {
    std::string input;
    std::cout << "Enter move (e.g., e2 e4): ";
    std::getline(std::cin, input);
    Position from(input[1] - '1', input[0] - 'a');
    Position to(input[4] - '1', input[3] - 'a');
    return {from, to};
}
