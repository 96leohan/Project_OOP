#include "PlayingState.h"
#include "CheckState.h"
#include "CheckmateState.h"

void PlayingState::handle(Game& game) {
    if (game.getBoard().isCheckmate(game.getCurrentTurn())) {
        game.setState(std::make_unique<CheckmateState>());
    } else if (game.getBoard().isCheck(game.getCurrentTurn())) {
        game.setState(std::make_unique<CheckState>());
    }
}
