#pragma once
#include "GameState.h"

class CheckState : public GameState {
public:
    void handle(Game& game) override;
    std::string getStateName() const override { return "Check"; }
};
