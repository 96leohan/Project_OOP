#include "chess_board.h"
#include <iostream>
#include <limits> // Required for numeric_limits
#include <cctype> // Required for toupper

ChessBoard::ChessBoard()
    : _board(8, std::vector<std::unique_ptr<ChessPiece>>(8)),
      _currentTurn(Color::WHITE),
      _gameOver(false)
{
    initializeBoard();
}

void ChessBoard::initializeBoard()
{
    // Clear the board first
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            _board[i][j] = nullptr;
        }
    }

    // Set up white pieces
    // Pawns
    for (int col = 0; col < 8; ++col)
    {
        _board[6][col] = std::make_unique<Pawn>(Color::WHITE, Position(6, col));
    }

    // Other pieces
    _board[7][0] = std::make_unique<Rook>(Color::WHITE, Position(7, 0));
    _board[7][1] = std::make_unique<Knight>(Color::WHITE, Position(7, 1));
    _board[7][2] = std::make_unique<Bishop>(Color::WHITE, Position(7, 2));
    _board[7][3] = std::make_unique<Queen>(Color::WHITE, Position(7, 3));
    _board[7][4] = std::make_unique<King>(Color::WHITE, Position(7, 4));
    _board[7][5] = std::make_unique<Bishop>(Color::WHITE, Position(7, 5));
    _board[7][6] = std::make_unique<Knight>(Color::WHITE, Position(7, 6));
    _board[7][7] = std::make_unique<Rook>(Color::WHITE, Position(7, 7));

    // Set up black pieces
    // Pawns
    for (int col = 0; col < 8; ++col)
    {
        _board[1][col] = std::make_unique<Pawn>(Color::BLACK, Position(1, col));
    }

    // Other pieces
    _board[0][0] = std::make_unique<Rook>(Color::BLACK, Position(0, 0));
    _board[0][1] = std::make_unique<Knight>(Color::BLACK, Position(0, 1));
    _board[0][2] = std::make_unique<Bishop>(Color::BLACK, Position(0, 2));
    _board[0][3] = std::make_unique<Queen>(Color::BLACK, Position(0, 3));
    _board[0][4] = std::make_unique<King>(Color::BLACK, Position(0, 4));
    _board[0][5] = std::make_unique<Bishop>(Color::BLACK, Position(0, 5));
    _board[0][6] = std::make_unique<Knight>(Color::BLACK, Position(0, 6));
    _board[0][7] = std::make_unique<Rook>(Color::BLACK, Position(0, 7));

    // Reset game state
    _currentTurn = Color::WHITE;
    _gameOver = false;

    std::cout << "Chess board initialized with all pieces in starting positions." << std::endl;
}

void ChessBoard::display() const
{
    std::cout << "\n  a b c d e f g h\n";
    for (int i = 0; i < 8; i++)
    {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; j++)
        {
            if (_board[i][j] == nullptr)
            {
                std::cout << (((i + j) % 2 == 0) ? "." : " ") << " ";
            }
            else
            {
                std::cout << _board[i][j]->getSymbol() << " ";
            }
        }
        std::cout << 8 - i << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}

ChessPiece *ChessBoard::getPiece(const Position &pos) const
{
    if (!pos.isValid())
        return nullptr;
    return _board[pos._row][pos._col].get();
}

bool ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *piece = getPiece(from);

    // Basic validations
    if (piece == nullptr || !to.isValid())
    {
        return false;
    }

    if (piece->getColor() != _currentTurn)
    {
        std::cout << "It's not your turn!" << std::endl;
        return false;
    }

    // Check if move is valid according to piece rules
    if (!piece->isValidMove(*this, to))
    {
        std::cout << "Invalid move for this piece!" << std::endl;
        return false;
    }

    // Special case for Pawn
    if (piece->getType() == PieceType::PAWN)
    {
        auto pawn = dynamic_cast<Pawn *>(piece);
        pawn->_hasMoved = true;

        // En passant logic would go here
    }
    // Special case for Rook
    else if (piece->getType() == PieceType::ROOK)
    {
        dynamic_cast<Rook *>(piece)->_hasMoved = true;
    }
    // Special case for King
    else if (piece->getType() == PieceType::KING)
    {
        auto king = dynamic_cast<King *>(piece);

        // Handle castling
        if (king->isCastlingMove(to))
        {
            int row = piece->getPosition()._row;
            int fromCol = piece->getPosition()._col;
            int toCol = to._col;

            // Determine which rook to move based on kingside/queenside castling
            Position rookFromPos, rookToPos;
            if (toCol > fromCol)
            { // Kingside castling
                rookFromPos = Position(row, 7);
                rookToPos = Position(row, 5);
            }
            else
            { // Queenside castling
                rookFromPos = Position(row, 0);
                rookToPos = Position(row, 3);
            }

            // Move the rook
            auto rook = std::move(_board[rookFromPos._row][rookFromPos._col]);
            _board[rookToPos._row][rookToPos._col] = std::move(rook);
            _board[rookFromPos._row][rookFromPos._col] = nullptr;

            // Update rook's position
            ChessPiece *rookPiece = getPiece(rookToPos);
            rookPiece->setPosition(rookToPos);
        }

        king->_hasMoved = true;
    }

    // Save the destination piece (if any) in case we need to revert the move
    std::unique_ptr<ChessPiece> capturedPiece = std::move(_board[to._row][to._col]);

    // Move the piece
    auto movingPiece = std::move(_board[from._row][from._col]);
    _board[to._row][to._col] = std::move(movingPiece);
    piece->setPosition(to);

    // Check if the move puts or leaves the player's king in check
    if (isInCheck(_currentTurn))
    {
        // Revert the move
        _board[from._row][from._col] = std::move(_board[to._row][to._col]);
        _board[to._row][to._col] = std::move(capturedPiece);
        piece->setPosition(from);

        std::cout << "Invalid move: Would leave your king in check!" << std::endl;
        return false;
    }

    // Handle pawn promotion
    if (piece->getType() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn->canPromote())
        {
            promotePawn(to);
        }
    }

    // Check if the opponent is in checkmate
    Color opponentColor = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    if (isInCheck(opponentColor))
    {
        if (isCheckmate(opponentColor))
        {
            std::cout << "Checkmate! " << (_currentTurn == Color::WHITE ? "White" : "Black") << " wins!" << std::endl;
            _gameOver = true;
        }
        else
        {
            std::cout << "Check!" << std::endl;
        }
    }

    // Switch turns
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true;
}

void ChessBoard::promotePawn(const Position &pos)
{
    char choice;
    bool validChoice = false;

    while (!validChoice)
    {
        std::cout << "Promote pawn to (Q)ueen, (R)ook, (B)ishop, or k(N)ight? ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        choice = std::toupper(choice);
        if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N')
        {
            validChoice = true;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    ChessPiece *pawn = getPiece(pos);
    Color color = pawn->getColor();

    // Remove the pawn
    _board[pos._row][pos._col] = nullptr;

    // Create the new piece
    switch (choice)
    {
    case 'Q':
        _board[pos._row][pos._col] = std::make_unique<Queen>(color, pos);
        break;
    case 'R':
        _board[pos._row][pos._col] = std::make_unique<Rook>(color, pos);
        break;
    case 'B':
        _board[pos._row][pos._col] = std::make_unique<Bishop>(color, pos);
        break;
    case 'N':
        _board[pos._row][pos._col] = std::make_unique<Knight>(color, pos);
        break;
    }

    std::cout << "Pawn promoted!" << std::endl;
}

Color ChessBoard::getCurrentTurn() const
{
    return _currentTurn;
}

bool ChessBoard::isGameOver() const
{
    return _gameOver;
}

bool ChessBoard::isInCheck(Color color) const
{
    // First, find the king's position
    Position kingPos(-1, -1);
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = _board[row][col].get();
            if (piece != nullptr && piece->getType() == PieceType::KING && piece->getColor() == color)
            {
                kingPos = Position(row, col);
                break;
            }
        }
        if (kingPos._row != -1)
            break; // King found
    }

    // Check if any opponent piece can attack the king
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = _board[row][col].get();
            if (piece != nullptr && piece->getColor() != color)
            {
                if (piece->isValidMove(*this, kingPos))
                {
                    return true; // King is in check
                }
            }
        }
    }

    return false; // King is not in check
}

bool ChessBoard::isCheckmate(Color color) const
{
    // If not in check, can't be checkmate
    if (!isInCheck(color))
    {
        return false;
    }

    // Try all possible moves for all pieces of this color
    for (int fromRow = 0; fromRow < 8; ++fromRow)
    {
        for (int fromCol = 0; fromCol < 8; ++fromCol)
        {
            ChessPiece *piece = _board[fromRow][fromCol].get();
            if (piece != nullptr && piece->getColor() == color)
            {
                // Get all possible moves for this piece
                std::vector<Position> moves = piece->getPossibleMoves(*this);

                for (const auto &move : moves)
                {
                    // Save current state
                    Position from(fromRow, fromCol);
                    std::unique_ptr<ChessPiece> savedDestPiece = nullptr;
                    if (_board[move._row][move._col])
                    {
                        savedDestPiece = std::make_unique<ChessPiece>(*_board[move._row][move._col]);
                    }

                    // Try to make the move (temporarily)
                    if (piece->isValidMove(*this, move))
                    {
                        auto movingPiece = std::move(const_cast<ChessBoard *>(this)->_board[from._row][from._col]);
                        const_cast<ChessBoard *>(this)->_board[move._row][move._col] = std::move(movingPiece);
                        piece->setPosition(move);

                        // Check if we're still in check
                        bool stillInCheck = isInCheck(color);

                        // Restore the board
                        auto movedPiece = std::move(const_cast<ChessBoard *>(this)->_board[move._row][move._col]);
                        const_cast<ChessBoard *>(this)->_board[from._row][from._col] = std::move(movedPiece);
                        if (savedDestPiece)
                        {
                            const_cast<ChessBoard *>(this)->_board[move._row][move._col] = std::move(savedDestPiece);
                        }
                        piece->setPosition(from);

                        // If any move gets us out of check, it's not checkmate
                        if (!stillInCheck)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // If we couldn't find any move to get out of check, it's checkmate
    return true;
}