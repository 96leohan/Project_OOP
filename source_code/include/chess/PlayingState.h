#pragma once
#include "GameState.h"

class PlayingState : public GameState {
public:
    void handle(Game& game) override;
    std::string getStateName() const override { return "Playing"; }
};
