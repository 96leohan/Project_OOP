#pragma once
#include "Command.h"
#include "Position.h"

class MoveCommand : public Command {
public:
    MoveCommand(Board& board, const Position& from, const Position& to);
    void execute() override;
    void undo() override;

private:
    Board& board_;
    Position from_;
    Position to_;
    std::unique_ptr<Piece> captured_piece_;
    std::unique_ptr<Piece> moved_piece_;
};
