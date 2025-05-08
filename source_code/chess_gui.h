#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "chess_board.h"
#include "position.h"

class ChessGUI
{
private:
    sf::RenderWindow *window;
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
    std::map<std::string, sf::Texture> pieceTextures;

    // Trạng thái giao diện
    Position selectedPiecePos;
    bool isPieceSelected;
    std::vector<Position> validMoves;

    // Màu sắc cho việc đánh dấu
    sf::Color selectedColor;
    sf::Color validMoveColor;
    sf::Color lastMoveColor;

    // Kích thước và vị trí
    int boardSize;
    int squareSize;
    int boardOffsetX;
    int boardOffsetY;

    // Quân cờ last move
    Position lastMoveFrom;
    Position lastMoveTo;

    // Font và text
    sf::Font font;
    sf::Text statusText;

public:
    ChessGUI(sf::RenderWindow *window);
    ~ChessGUI();

    sf::Font &getFont() { return font; } // lấy font

    // Khởi tạo tài nguyên
    bool loadResources();

    // Xử lý sự kiện
    void handleEvent(sf::Event event, ChessBoard &board);

    // Vẽ các thành phần
    void draw(const ChessBoard &board);
    void drawBoard();
    void drawPieces(const ChessBoard &board);
    void drawValidMoves();
    void drawLastMove();
    void drawStatus(const std::string &status);

    // Tiện ích
    void highlightSquare(Position pos, sf::Color color);
    Position getBoardPosition(int x, int y);
    sf::Vector2f getSquarePosition(Position pos);
    std::string getPieceKey(ChessPiece *piece);

    // Cập nhật trạng thái
    void setLastMove(Position from, Position to);
    void clearSelection();
    void updateValidMoves(const ChessBoard &board, Position pos);
};

#endif // CHESS_GUI_H
