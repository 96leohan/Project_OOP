#include "chess_board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>

// Static function for piece type to string conversion
static const char *pieceTypeToString(PieceType type)
{
    switch (type)
    {
    case PieceType::PAWN:
        return "Pawn";
    case PieceType::ROOK:
        return "Rook";
    case PieceType::KNIGHT:
        return "Knight";
    case PieceType::BISHOP:
        return "Bishop";
    case PieceType::QUEEN:
        return "Queen";
    case PieceType::KING:
        return "King";
    default:
        return "Unknown";
    }
}

ChessBoard::ChessBoard() : _currentTurn(Color::WHITE), _gameOver(false)
{
    initializeBoard();
}

ChessBoard::ChessBoard(const ChessBoard &other)
    : _currentTurn(other._currentTurn), _gameOver(other._gameOver)
{
    // Deep copy the board
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (other._board[row][col])
            {
                // Clone each piece
                ChessPiece *piece = other._board[row][col].get();
                Color color = piece->getColor();
                Position pos(row, col);

                switch (piece->getType())
                {
                case PieceType::PAWN:
                    _board[row][col] = std::make_unique<Pawn>(color, pos);
                    break;
                case PieceType::ROOK:
                    _board[row][col] = std::make_unique<Rook>(color, pos);
                    // Copy rook's moved state through public interface
                    if (auto rook = dynamic_cast<Rook *>(piece))
                    {
                        // Assuming Rook has a public hasMoved() method
                        // and setMoved() method or constructor parameter
                        if (rook->hasMoved())
                        {
                            static_cast<Rook *>(_board[row][col].get())->setMoved(true);
                        }
                    }
                    break;
                case PieceType::KNIGHT:
                    _board[row][col] = std::make_unique<Knight>(color, pos);
                    break;
                case PieceType::BISHOP:
                    _board[row][col] = std::make_unique<Bishop>(color, pos);
                    break;
                case PieceType::QUEEN:
                    _board[row][col] = std::make_unique<Queen>(color, pos);
                    break;
                case PieceType::KING:
                    _board[row][col] = std::make_unique<King>(color, pos);
                    // Copy king's moved state
                    if (auto king = dynamic_cast<King *>(piece))
                    {
                        if (king->hasMoved())
                        {
                            static_cast<King *>(_board[row][col].get())->setMoved(true);
                        }
                    }
                    break;
                }
            }
        }
    }

    // Copy move history
    _moveHistory = other._moveHistory;
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other)
{
    if (this != &other)
    {
        _currentTurn = other._currentTurn;
        _gameOver = other._gameOver;

        // Clear current board
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                _board[row][col].reset();
            }
        }

        // Copy board (same logic as copy constructor)
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                if (other._board[row][col])
                {
                    ChessPiece *piece = other._board[row][col].get();
                    Color color = piece->getColor();
                    Position pos(row, col);

                    switch (piece->getType())
                    {
                    case PieceType::PAWN:
                        _board[row][col] = std::make_unique<Pawn>(color, pos);
                        break;
                    case PieceType::ROOK:
                        _board[row][col] = std::make_unique<Rook>(color, pos);
                        if (auto rook = dynamic_cast<Rook *>(piece))
                        {
                            if (rook->hasMoved())
                            {
                                static_cast<Rook *>(_board[row][col].get())->setMoved(true);
                            }
                        }
                        break;
                    case PieceType::KNIGHT:
                        _board[row][col] = std::make_unique<Knight>(color, pos);
                        break;
                    case PieceType::BISHOP:
                        _board[row][col] = std::make_unique<Bishop>(color, pos);
                        break;
                    case PieceType::QUEEN:
                        _board[row][col] = std::make_unique<Queen>(color, pos);
                        break;
                    case PieceType::KING:
                        _board[row][col] = std::make_unique<King>(color, pos);
                        if (auto king = dynamic_cast<King *>(piece))
                        {
                            if (king->hasMoved())
                            {
                                static_cast<King *>(_board[row][col].get())->setMoved(true);
                            }
                        }
                        break;
                    }
                }
            }
        }

        _moveHistory = other._moveHistory;
    }
    return *this;
}

bool ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *piece = getPiece(from);
    if (!piece || piece->getColor() != _currentTurn)
    {
        return false;
    }

    // Store original information before the move
    Color pieceColor = piece->getColor();
    PieceType pieceType = piece->getType();

    // Check if destination has a piece (capture)
    ChessPiece *capturedPiece = getPiece(to);
    bool isCapture = (capturedPiece != nullptr);
    PieceType capturedType = isCapture ? capturedPiece->getType() : PieceType::PAWN;

    // Validate move
    if (!piece->isValidMove(to, *this))
    {
        return false;
    }

    // Check for special moves
    bool isCastling = false;
    bool isPromotion = false;
    PieceType promotionType = PieceType::PAWN;

    // Handle castling
    if (pieceType == PieceType::KING && std::abs(to._col - from._col) == 2)
    {
        isCastling = true;
        // Move the rook as well
        if (to._col == 6) // King-side castling
        {
            auto rook = std::move(_board[from._row][7]);
            _board[from._row][5] = std::move(rook);
            _board[from._row][5]->setPosition(Position(from._row, 5));
        }
        else if (to._col == 2) // Queen-side castling
        {
            auto rook = std::move(_board[from._row][0]);
            _board[from._row][3] = std::move(rook);
            _board[from._row][3]->setPosition(Position(from._row, 3));
        }
    }

    // Make the move
    _board[to._row][to._col] = std::move(_board[from._row][from._col]);
    _board[to._row][to._col]->setPosition(to);

    // Handle pawn promotion
    if (pieceType == PieceType::PAWN && (to._row == 0 || to._row == 7))
    {
        isPromotion = true;
        promotePawn(to);
        promotionType = _board[to._row][to._col]->getType();
    }

    // Switch turns
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    // Check for check and checkmate
    bool isCheck = isInCheck(_currentTurn);
    bool isCheckmate = isCheck && this->isCheckmate(_currentTurn);

    // Create and store move history - FIXED: use pieceColor instead of originalTurn
    Move move(from, to, pieceType, pieceColor, isCapture, capturedType,
              isCheck, isCheckmate, isCastling, isPromotion, promotionType);
    _moveHistory.push_back(move);

    // Check game end conditions
    if (checkGameEndConditions())
    {
        _gameOver = true;
    }

    return true;
}

void ChessBoard::promotePawn(const Position &pos)
{
    ChessPiece *pawn = getPiece(pos);
    if (!pawn || pawn->getType() != PieceType::PAWN)
    {
        std::cout << "Error: No pawn found at position for promotion!" << std::endl;
        return;
    }

    Color color = pawn->getColor();

    // For now, default to Queen promotion
    // TODO: Implement proper GUI selection
    PieceType promotionChoice = PieceType::QUEEN;

    // Console fallback for testing
    char choice = 'Q';
    std::cout << "Promote pawn to (Q)ueen, (R)ook, (B)ishop, or (K)night? ";
    std::cin >> choice;
    choice = std::toupper(choice);

    switch (choice)
    {
    case 'Q':
        promotionChoice = PieceType::QUEEN;
        break;
    case 'R':
        promotionChoice = PieceType::ROOK;
        break;
    case 'B':
        promotionChoice = PieceType::BISHOP;
        break;
    case 'K':
        promotionChoice = PieceType::KNIGHT;
        break;
    default:
        promotionChoice = PieceType::QUEEN;
        break;
    }

    // Remove pawn and create new piece
    _board[pos._row][pos._col].reset();

    switch (promotionChoice)
    {
    case PieceType::QUEEN:
        _board[pos._row][pos._col] = std::make_unique<Queen>(color, pos);
        break;
    case PieceType::ROOK:
        _board[pos._row][pos._col] = std::make_unique<Rook>(color, pos);
        break;
    case PieceType::BISHOP:
        _board[pos._row][pos._col] = std::make_unique<Bishop>(color, pos);
        break;
    case PieceType::KNIGHT:
        _board[pos._row][pos._col] = std::make_unique<Knight>(color, pos);
        break;
    default:
        _board[pos._row][pos._col] = std::make_unique<Queen>(color, pos);
        break;
    }

    std::cout << "Pawn promoted to " << pieceTypeToString(promotionChoice) << "!" << std::endl;
}

// FIXED: Implement the correct function name from header
bool ChessBoard::checkGameEndConditions() const
{
    Color currentPlayer = getCurrentTurn();

    if (isInCheck(currentPlayer) && isCheckmate(currentPlayer))
    {
        return true;
    }

    if (!isInCheck(currentPlayer) && isStalemate(currentPlayer))
    {
        return true;
    }

    return false;
}

// Simple wrapper - FIXED: Keep this simple as per header
bool ChessBoard::isGameOver() const
{
    return _gameOver;
}

std::vector<Position> ChessBoard::getAllPossibleMoves(const Position &pos) const
{
    std::vector<Position> moves;
    ChessPiece *piece = getPiece(pos);

    // FIXED: Add error handling
    if (!piece)
    {
        return moves; // Return empty vector if no piece found
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Position target(row, col);
            if (piece->isValidMove(target, *this))
            {
                moves.push_back(target);
            }
        }
    }
    return moves;
}

bool ChessBoard::isInCheck(Color color) const
{
    // Find the king
    Position kingPos(-1, -1);
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = getPiece(Position(row, col));
            if (piece && piece->getType() == PieceType::KING && piece->getColor() == color)
            {
                kingPos = Position(row, col);
                break;
            }
        }
        if (kingPos._row != -1)
            break;
    }

    // FIXED: Better error handling if king not found
    if (kingPos._row == -1)
    {
        std::cerr << "Error: King not found for color " << static_cast<int>(color) << std::endl;
        return false;
    }

    // Check if any opponent piece can attack the king
    Color opponentColor = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = getPiece(Position(row, col));
            if (piece && piece->getColor() == opponentColor)
            {
                if (piece->isValidMove(kingPos, *this))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isCheckmate(Color color) const
{
    if (!isInCheck(color))
    {
        return false;
    }

    // Try all possible moves for the color
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = getPiece(Position(row, col));
            if (piece && piece->getColor() == color)
            {
                Position from(row, col);
                std::vector<Position> moves = getAllPossibleMoves(from);

                for (const Position &to : moves)
                {
                    // Create a copy of the board to test the move
                    ChessBoard testBoard = *this;

                    // Make the move on test board (without updating move history to avoid recursion)
                    ChessPiece *testPiece = testBoard.getPiece(from);
                    testBoard._board[to._row][to._col] = std::move(testBoard._board[from._row][from._col]);
                    testBoard._board[to._row][to._col]->setPosition(to);

                    // Check if king is still in check
                    if (!testBoard.isInCheck(color))
                    {
                        return false; // Found a move that gets out of check
                    }
                }
            }
        }
    }
    return true; // No moves found that get out of check
}

bool ChessBoard::isStalemate(Color color) const
{
    if (isInCheck(color))
    {
        return false; // Can't be stalemate if in check
    }

    // Try all possible moves for the color
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = getPiece(Position(row, col));
            if (piece && piece->getColor() == color)
            {
                Position from(row, col);
                std::vector<Position> moves = getAllPossibleMoves(from);

                for (const Position &to : moves)
                {
                    // Create a copy of the board to test the move
                    ChessBoard testBoard = *this;

                    // Make the move on test board
                    testBoard._board[to._row][to._col] = std::move(testBoard._board[from._row][from._col]);
                    testBoard._board[to._row][to._col]->setPosition(to);

                    // Check if this move puts king in check
                    if (!testBoard.isInCheck(color))
                    {
                        return false; // Found a legal move
                    }
                }
            }
        }
    }
    return true; // No legal moves found
}

// Implementation for user promotion choice - basic console version
PieceType askUserForPromotionChoice(sf::RenderWindow &window)
{
    // For now, implement as console input
    // TODO: Implement proper GUI dialog
    char choice;
    std::cout << "Promote pawn to (Q)ueen, (R)ook, (B)ishop, or (K)night? ";
    std::cin >> choice;
    choice = std::toupper(choice);

    switch (choice)
    {
    case 'Q':
        return PieceType::QUEEN;
    case 'R':
        return PieceType::ROOK;
    case 'B':
        return PieceType::BISHOP;
    case 'K':
        return PieceType::KNIGHT;
    default:
        return PieceType::QUEEN;
    }
}

// ===== OTHER EXISTING METHODS (keep unchanged) =====

void ChessBoard::initializeBoard()
{
    // Clear the board
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            _board[row][col] = nullptr;
        }
    }

    // Initialize white pieces
    _board[7][0] = std::make_unique<Rook>(Color::WHITE, Position(7, 0));
    _board[7][1] = std::make_unique<Knight>(Color::WHITE, Position(7, 1));
    _board[7][2] = std::make_unique<Bishop>(Color::WHITE, Position(7, 2));
    _board[7][3] = std::make_unique<Queen>(Color::WHITE, Position(7, 3));
    _board[7][4] = std::make_unique<King>(Color::WHITE, Position(7, 4));
    _board[7][5] = std::make_unique<Bishop>(Color::WHITE, Position(7, 5));
    _board[7][6] = std::make_unique<Knight>(Color::WHITE, Position(7, 6));
    _board[7][7] = std::make_unique<Rook>(Color::WHITE, Position(7, 7));

    for (int col = 0; col < 8; ++col)
    {
        _board[6][col] = std::make_unique<Pawn>(Color::WHITE, Position(6, col));
    }

    // Initialize black pieces
    _board[0][0] = std::make_unique<Rook>(Color::BLACK, Position(0, 0));
    _board[0][1] = std::make_unique<Knight>(Color::BLACK, Position(0, 1));
    _board[0][2] = std::make_unique<Bishop>(Color::BLACK, Position(0, 2));
    _board[0][3] = std::make_unique<Queen>(Color::BLACK, Position(0, 3));
    _board[0][4] = std::make_unique<King>(Color::BLACK, Position(0, 4));
    _board[0][5] = std::make_unique<Bishop>(Color::BLACK, Position(0, 5));
    _board[0][6] = std::make_unique<Knight>(Color::BLACK, Position(0, 6));
    _board[0][7] = std::make_unique<Rook>(Color::BLACK, Position(0, 7));

    for (int col = 0; col < 8; ++col)
    {
        _board[1][col] = std::make_unique<Pawn>(Color::BLACK, Position(1, col));
    }
}

ChessPiece *ChessBoard::getPiece(const Position &pos) const
{
    if (pos._row < 0 || pos._row >= 8 || pos._col < 0 || pos._col >= 8)
    {
        return nullptr;
    }
    return _board[pos._row][pos._col].get();
}

Color ChessBoard::getCurrentTurn() const
{
    return _currentTurn;
}

const std::vector<Move> &ChessBoard::getMoveHistory() const
{
    return _moveHistory;
}

void ChessBoard::printBoard() const
{
    std::cout << "  a b c d e f g h\n";
    for (int row = 0; row < 8; ++row)
    {
        std::cout << 8 - row << " ";
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece *piece = getPiece(Position(row, col));
            if (piece)
            {
                char symbol = '?';
                switch (piece->getType())
                {
                case PieceType::PAWN:
                    symbol = 'P';
                    break;
                case PieceType::ROOK:
                    symbol = 'R';
                    break;
                case PieceType::KNIGHT:
                    symbol = 'N';
                    break;
                case PieceType::BISHOP:
                    symbol = 'B';
                    break;
                case PieceType::QUEEN:
                    symbol = 'Q';
                    break;
                case PieceType::KING:
                    symbol = 'K';
                    break;
                }

                if (piece->getColor() == Color::BLACK)
                {
                    symbol = std::tolower(symbol);
                }

                std::cout << symbol << " ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << 8 - row << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

bool ChessBoard::isValidPosition(const Position &pos) const
{
    return pos._row >= 0 && pos._row < 8 && pos._col >= 0 && pos._col < 8;
}

void ChessBoard::undoMove()
{
    if (_moveHistory.empty())
    {
        return;
    }

    // This is a complex operation that would require storing more state
    // For now, just remove the last move from history
    // TODO: Implement full undo functionality
    _moveHistory.pop_back();
}

std::string ChessBoard::getGameStatus() const
{
    if (_gameOver)
    {
        if (isInCheck(_currentTurn))
        {
            Color winner = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
            return (winner == Color::WHITE) ? "White wins by checkmate!" : "Black wins by checkmate!";
        }
        else
        {
            return "Game ended in stalemate!";
        }
    }
    else if (isInCheck(_currentTurn))
    {
        return (_currentTurn == Color::WHITE) ? "White is in check!" : "Black is in check!";
    }
    else
    {
        return (_currentTurn == Color::WHITE) ? "White to move" : "Black to move";
    }
}