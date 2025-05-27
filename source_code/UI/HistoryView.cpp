#include "HistoryView.h"
#include <iostream>
#include <sstream>

HistoryView::HistoryView()
{
    // Load font (you might need to adjust path)
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font for HistoryView" << std::endl;
        // Try default system font or handle error
    }

    // Setup history text
    historyText.setFont(font);
    historyText.setCharacterSize(16);
    historyText.setFillColor(sf::Color::Black);
    historyText.setPosition(850, 150); // Position to the right of the board

    updateDisplay();
}

void HistoryView::draw(sf::RenderWindow &window)
{
    // Draw background for history panel
    sf::RectangleShape background(sf::Vector2f(200, 500));
    background.setPosition(840, 140);
    background.setFillColor(sf::Color(240, 240, 240, 200));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);
    window.draw(background);

    // Title
    sf::Text title("Move History", font, 18);
    title.setPosition(850, 150);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    window.draw(title);

    // History text
    window.draw(historyText);
}

void HistoryView::addMove(const std::string &move)
{
    moves.push_back(move);
    updateDisplay();
}

void HistoryView::reset()
{
    moves.clear();
    updateDisplay();
}

void HistoryView::updateDisplay()
{
    std::stringstream ss;

    // Display moves in pairs (White, Black)
    for (size_t i = 0; i < moves.size(); ++i)
    {
        if (i % 2 == 0)
        {
            // White move - start new line with move number
            ss << (i / 2 + 1) << ". " << moves[i];
            if (i + 1 < moves.size())
            {
                ss << " " << moves[i + 1];
            }
            ss << "\n";
        }
        // Black moves are handled in the if block above
    }

    historyText.setString(ss.str());
    historyText.setPosition(850, 180); // Below the title
}

// Method to convert Move object to algebraic notation string
std::string HistoryView::moveToString(const Move &move)
{
    std::string result;

    // Add piece symbol (except for pawns)
    switch (move.pieceType)
    {
    case PieceType::KING:
        result += "K";
        break;
    case PieceType::QUEEN:
        result += "Q";
        break;
    case PieceType::ROOK:
        result += "R";
        break;
    case PieceType::BISHOP:
        result += "B";
        break;
    case PieceType::KNIGHT:
        result += "N";
        break;
    case PieceType::PAWN:
        break; // No symbol for pawns
    }

    // Handle castling
    if (move.isCastling)
    {
        if (move.to.col == 6)
        {
            return "O-O"; // Kingside castling
        }
        else
        {
            return "O-O-O"; // Queenside castling
        }
    }

    // Add capture notation
    if (move.isCapture)
    {
        if (move.pieceType == PieceType::PAWN)
        {
            // For pawn captures, show the file
            result += char('a' + move.from.col);
        }
        result += "x";
    }

    // Add destination square
    result += char('a' + move.to.col);
    result += char('1' + (7 - move.to.row));

    // Add promotion notation
    if (move.isPromotion)
    {
        result += "=";
        switch (move.promotionType)
        {
        case PieceType::QUEEN:
            result += "Q";
            break;
        case PieceType::ROOK:
            result += "R";
            break;
        case PieceType::BISHOP:
            result += "B";
            break;
        case PieceType::KNIGHT:
            result += "N";
            break;
        }
    }

    // Add check/checkmate notation
    if (move.isCheckmate)
    {
        result += "#";
    }
    else if (move.isCheck)
    {
        result += "+";
    }

    return result;
}

// Method to update display from MoveHistory object
void HistoryView::updateFromMoveHistory(const MoveHistory &moveHistory)
{
    moves.clear();

    // Convert Move objects to strings
    const auto &moveList = moveHistory.getMoves();
    for (const auto &move : moveList)
    {
        moves.push_back(moveToString(move));
    }

    updateDisplay();
}