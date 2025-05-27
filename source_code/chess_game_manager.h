#pragma once
#include <SFML/Graphics.hpp>
#include "chess_board.h"
#include "chess_gui.h"
#include "UI/TimerView.h"
#include "UI/HistoryView.h"

class ChessGameManager
{
public:
    ChessGameManager(ChessBoard *board, ChessGUI *gui, TimerView *timer, HistoryView *history);

    // Handle player move events
    bool handlePlayerMove(const Position &from, const Position &to);

    // Check if move was successful and update UI accordingly
    void onMoveCompleted();

    // Reset game state
    void resetGame();

private:
    ChessBoard *chessBoard;
    ChessGUI *chessGUI;
    TimerView *timerView;
    HistoryView *historyView;

    // Track last move for history
    Position lastFrom, lastTo;
    bool moveInProgress;
};

// Implementation
ChessGameManager::ChessGameManager(ChessBoard *board, ChessGUI *gui, TimerView *timer, HistoryView *history)
    : chessBoard(board), chessGUI(gui), timerView(timer), historyView(history),
      moveInProgress(false), lastFrom(-1, -1), lastTo(-1, -1)
{
}

bool ChessGameManager::handlePlayerMove(const Position &from, const Position &to)
{
    if (chessBoard->movePiece(from, to))
    {
        lastFrom = from;
        lastTo = to;
        moveInProgress = true;
        onMoveCompleted();
        return true;
    }
    return false;
}

void ChessGameManager::onMoveCompleted()
{
    if (moveInProgress)
    {
        // Switch timer turn
        timerView->switchTurn();

        // Update GUI with last move
        chessGUI->setLastMove(lastFrom, lastTo);

        // Update history
        historyView->updateFromMoveHistory(chessBoard->getMoveHistory());

        moveInProgress = false;
    }
}

void ChessGameManager::resetGame()
{
    chessBoard->initializeBoard();
    chessGUI->clearSelection();
    chessGUI->setLastMove(Position(-1, -1), Position(-1, -1));
    timerView->setMode(TimerView::TimeControl::Blitz);
    historyView->reset();
    moveInProgress = false;
}