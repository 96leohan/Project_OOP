#pragma once
#include "Position.h"

class UINotifier {
public:
    virtual ~UINotifier() = default;
    virtual void notifyMove(const Position& from, const Position& to) = 0;
};
