#pragma once
#include "Game.h"

class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handle(Game& game) = 0;
    virtual std::string getStateName() const = 0;
};
