#pragma once
#include "InputHandler.h"

namespace ui {
    class ConsoleInputHandler : public InputHandler {
    public:
        std::pair<Position, Position> getMove() override;
    };
}
