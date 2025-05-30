#include "CheckState.h"
#include "PlayingState.h"
#include "CheckmateState.h"

void CheckState::handle(Game& game) {
    if (game.getBoard().isCheckmate(game.getCurrentTurn())) {
        game.setState(std::make_unique<CheckmateState>());
    } else if (!game.getBoard().isCheck(game.getCurrentTurn())) {
        game.setState(std::make_unique<PlayingState>());
    }
}
