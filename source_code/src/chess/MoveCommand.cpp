#include "MoveCommand.h"

MoveCommand::MoveCommand(Board& board, const Position& from, const Position& to)
    : board_(board), from_(from), to_(to), has_last_move_(false) {}

void MoveCommand::execute() {
    moved_piece_ = board_.getPiece(from_);
    captured_piece_ = board_.getPiece(to_);
    board_.movePiece(from_, to_);
}

void MoveCommand::undo() {
    board_.placePiece(std::move(moved_piece_), from_);
    board_.placePiece(std::move(captured_piece_), to_);
}
