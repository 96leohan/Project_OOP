#pragma once
#include "../chess/Position.h"

namespace ui {
    class InputHandler {
    public:
        virtual ~InputHandler() = default;
        virtual std::pair<Position, Position> getMove() = 0;
    };
}
