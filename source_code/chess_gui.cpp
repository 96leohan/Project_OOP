// nhớ kiểm tra các đường link có đúng không
//  ches GUI
#include "ChessGUI.h"
#include "chess_piece.h"
#include <iostream>

ChessGUI::ChessGUI(sf::RenderWindow *window) : window(window)
{
    // Khởi tạo các giá trị mặc định
    isPieceSelected = false;
    boardSize = 800;
    squareSize = 100;
    boardOffsetX = 50;
    boardOffsetY = 50;

    // Màu sắc mặc định
    selectedColor = sf::Color(255, 255, 0, 128); // Vàng trong suốt
    validMoveColor = sf::Color(0, 255, 0, 128);  // Xanh lá trong suốt
    lastMoveColor = sf::Color(0, 0, 255, 128);   // Xanh dương trong suốt

    // Vị trí không hợp lệ
    lastMoveFrom = Position(-1, -1);
    lastMoveTo = Position(-1, -1);
    selectedPiecePos = Position(-1, -1);

    // Thiết lập kích thước cửa sổ
    window->setSize(sf::Vector2u(boardSize + 2 * boardOffsetX, boardSize + 2 * boardOffsetY + 100));
}

ChessGUI::~ChessGUI()
{
    // Giải phóng tài nguyên nếu cần
}

bool ChessGUI::loadResources()
{
    // Tải texture cho bàn cờ
    if (!boardTexture.loadFromFile("resources/chessboard.png")) // Assuming this is correct
    {
        std::cerr << "Failed to load chessboard texture!" << std::endl;
        return false;
    }
    // ...

    // Tải texture cho các quân cờ
    std::vector<std::string> pieceFilenames = {// More descriptive names
                                               "w_king", "w_queen", "w_bishop", "w_knight", "w_rook", "w_pawn",
                                               "b_king", "b_queen", "b_bishop", "b_knight", "b_rook", "b_pawn"};

    for (const auto &filename : pieceFilenames) // Use the filename directly
    {
        sf::Texture texture;
        // CORRECTED PATH:
        if (!texture.loadFromFile("resources/pieces/" + filename + ".png"))
        {
            std::cerr << "Failed to load texture for " << filename << "!" << std::endl;
            return false;
        }
        pieceTextures[filename] = texture; // Store by filename (which is your key)
    }

    // Tải font chữ
    // CORRECTED PATH:
    if (!font.loadFromFile("resources/fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return false;
    }

    // Thiết lập text
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(boardOffsetX, boardOffsetY + boardSize + 20);

    return true;
}

void ChessGUI::handleEvent(sf::Event event, ChessBoard &board)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        // Lấy vị trí con trỏ chuột
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        Position boardPos = getBoardPosition(mousePos.x, mousePos.y);

        // Kiểm tra xem có nằm trong bàn cờ không
        if (boardPos.getX() >= 0 && boardPos.getX() < 8 &&
            boardPos.getY() >= 0 && boardPos.getY() < 8)
        {

            // Nếu chưa chọn quân cờ nào và ô này có quân
            if (!isPieceSelected)
            {
                ChessPiece *piece = board.getPiece(boardPos);
                if (piece != nullptr && piece->getColor() == board.getCurrentPlayer())
                {
                    selectedPiecePos = boardPos;
                    isPieceSelected = true;
                    updateValidMoves(board, boardPos);
                }
            }
            // Nếu đã chọn quân cờ và chọn ô đích
            else
            {
                // Kiểm tra xem nước đi có hợp lệ không
                bool isValidMove = false;
                for (const auto &move : validMoves)
                {
                    if (move == boardPos)
                    {
                        isValidMove = true;
                        break;
                    }
                }

                if (isValidMove)
                {
                    // Thực hiện nước đi
                    ChessPiece *piece = board.getPiece(selectedPiecePos);
                    if (piece && board.movePiece(selectedPiecePos, boardPos))
                    {
                        setLastMove(selectedPiecePos, boardPos);
                        clearSelection();
                    }
                }
                else
                {
                    // Chọn lại quân cờ khác nếu ô đó có quân cờ của người chơi hiện tại
                    ChessPiece *piece = board.getPiece(boardPos);
                    if (piece != nullptr && piece->getColor() == board.getCurrentPlayer())
                    {
                        selectedPiecePos = boardPos;
                        updateValidMoves(board, boardPos);
                    }
                    else
                    {
                        clearSelection();
                    }
                }
            }
        }
        else
        {
            clearSelection();
        }
    }
}

void ChessGUI::draw(const ChessBoard &board)
{
    drawBoard();
    drawLastMove();

    if (isPieceSelected)
    {
        highlightSquare(selectedPiecePos, selectedColor);
        drawValidMoves();
    }

    drawPieces(board);

    // Hiển thị trạng thái trò chơi
    std::string status;
    if (board.isCheckmate())
    {
        status = "Chiếu bí! " + std::string(board.getCurrentTurn() == ChessPiece::WHITE ? "Đen" : "Trắng") + " thắng!";
    }
    else if (board.isStalemate())
    {
        status = "Hòa cờ!";
    }
    else if (board.isCheck())
    {
        status = "Chiếu tướng! " + std::string(board.getCurrentTurn() == ChessPiece::WHITE ? "Trắng" : "Đen") + " cần bảo vệ vua.";
    }
    else
    {
        status = "Lượt của " + std::string(board.getCurrentTurn() == ChessPiece::WHITE ? "Trắng" : "Đen");
    }

    drawStatus(status);
}

void ChessGUI::drawBoard()
{
    window->draw(boardSprite);
}

void ChessGUI::drawPieces(const ChessBoard &board)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position pos(x, y);
            ChessPiece *piece = board.getPiece(pos);

            if (piece != nullptr)
            {
                std::string key = getPieceKey(piece);

                if (pieceTextures.find(key) != pieceTextures.end())
                {
                    sf::Sprite pieceSprite;
                    pieceSprite.setTexture(pieceTextures[key]);

                    // Tính toán vị trí
                    sf::Vector2f spritePos = getSquarePosition(pos);

                    // Căn giữa quân cờ trong ô
                    float pieceSize = squareSize * 0.9f;
                    pieceSprite.setScale(
                        pieceSize / pieceTextures[key].getSize().x,
                        pieceSize / pieceTextures[key].getSize().y);

                    // Căn giữa
                    spritePos.x += (squareSize - pieceSize) / 2;
                    spritePos.y += (squareSize - pieceSize) / 2;

                    pieceSprite.setPosition(spritePos);
                    window->draw(pieceSprite);
                }
            }
        }
    }
}

void ChessGUI::drawValidMoves()
{
    for (const auto &pos : validMoves)
    {
        highlightSquare(pos, validMoveColor);
    }
}

void ChessGUI::drawLastMove()
{
    if (lastMoveFrom.getX() >= 0 && lastMoveFrom.getY() >= 0)
    {
        highlightSquare(lastMoveFrom, lastMoveColor);
    }

    if (lastMoveTo.getX() >= 0 && lastMoveTo.getY() >= 0)
    {
        highlightSquare(lastMoveTo, lastMoveColor);
    }
}

void ChessGUI::drawStatus(const std::string &status)
{
    statusText.setString(status);
    window->draw(statusText);
}

void ChessGUI::highlightSquare(Position pos, sf::Color color)
{
    sf::RectangleShape highlight;
    sf::Vector2f squarePos = getSquarePosition(pos);

    highlight.setPosition(squarePos);
    highlight.setSize(sf::Vector2f(squareSize, squareSize));
    highlight.setFillColor(color);

    window->draw(highlight);
}

Position ChessGUI::getBoardPosition(int x, int y)
{
    // Kiểm tra xem chuột có nằm trong bàn cờ không
    if (x < boardOffsetX || y < boardOffsetY ||
        x >= boardOffsetX + boardSize || y >= boardOffsetY + boardSize)
    {
        return Position(-1, -1);
    }

    // Tính toán ô
    int boardX = (x - boardOffsetX) / squareSize;
    int boardY = (y - boardOffsetY) / squareSize;

    return Position(boardX, boardY);
}

sf::Vector2f ChessGUI::getSquarePosition(Position pos)
{
    float x = boardOffsetX + pos.getX() * squareSize;
    float y = boardOffsetY + pos.getY() * squareSize;
    return sf::Vector2f(x, y);
}

std::string ChessGUI::getPieceKey(ChessPiece *piece)
{
    if (!piece)
        return "unknown";
    std::string prefix = (piece->getColor() == Color::WHITE) ? "w_" : "b_";
    std::string typeStr;
    PieceType pType = piece->getType(); // Assuming piece->getType() exists

    switch (pType)
    {
    case PieceType::KING:
        typeStr = "king";
        break;
    case PieceType::QUEEN:
        typeStr = "queen";
        break;
    case PieceType::BISHOP:
        typeStr = "bishop";
        break;
    case PieceType::KNIGHT:
        typeStr = "knight";
        break;
    case PieceType::ROOK:
        typeStr = "rook";
        break;
    case PieceType::PAWN:
        typeStr = "pawn";
        break;
    default:
        typeStr = "unknown";
        break;
    }
    return prefix + typeStr;
}

void ChessGUI::setLastMove(Position from, Position to)
{
    lastMoveFrom = from;
    lastMoveTo = to;
}

void ChessGUI::clearSelection()
{
    isPieceSelected = false;
    selectedPiecePos = Position(-1, -1);
    validMoves.clear();
}

void ChessGUI::updateValidMoves(const ChessBoard &board, Position piecePos) // Renamed pos to piecePos for clarity
{
    validMoves.clear();
    ChessPiece *piece = board.getPiece(piecePos);

    if (piece != nullptr && piece->getColor() == board.getCurrentTurn()) // Check if it's the current player's piece
    {
        // Lấy tất cả các nước đi hợp lệ của quân cờ
        // Assuming ChessPiece has a getPossibleMoves method
        validMoves = piece->getPossibleMoves(board);

        // If getPossibleMoves doesn't filter for self-check, you might need an extra step
        // to create a temporary board for each move and see if it results in a check.
        // However, your ChessBoard::movePiece already handles this.
        // So, the moves from getPossibleMoves should be fine if they are "pseudo-legal".
        // The final check in ChessBoard::movePiece will confirm legality.

        /*!SECTION
        Important: For this to work, your ChessPiece base class (and derived classes) must have a:
        virtual std::vector<Position> getPossibleMoves(const ChessBoard& board) const;
        This method should return all pseudo-legal moves (moves that are valid by the piece's movement rules, without considering if they leave the king in check).
        Your ChessBoard::movePiece will then do the final validation.
        */
    }
}