#pragma once
#include "GameState.h"

class CheckmateState : public GameState {
public:
    void handle(Game& game) override;
    std::string getStateName() const override { return "Checkmate"; }
};
