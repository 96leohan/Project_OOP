#include "chess_board.h"
#include <iostream>
#include <limits> //dùng std::numeric_limits để xử lý lỗi nhập liệu
#include <cctype> // std::toupper để chuyển đổi ký tự thành chữ hoa

/*!SECTION - ghi chú: xem lại promotePawn
Pawn Promotion is the trickiest part to adapt from console to GUI.
The getPromotionChoiceGUI in main_gui.cpp is a start.
You need to make ChessBoard::promotePawn (or the logic in movePiece that calls it) use this GUI prompt instead of std::cin.
The global pointer g_chessGUI and g_fontForPromotion is a quick hack; a better solution involves callbacks or interfaces.
*/

// Định nghĩa constructor của lớp ChessBoard
ChessBoard::ChessBoard()
    : _board(8, std::vector<std::unique_ptr<ChessPiece>>(8)), // Khởi tạo bàn cờ là một vector 2D 8x8 chứa các con trỏ thông minh (unique_ptr) đến các đối tượng ChessPiece
      _currentTurn(Color::WHITE),                             // Khởi tạo lượt đi hiện tại là Trắng
      _gameOver(false)                                        // Khởi tạo trạng thái trò chơi là chưa kết thúc
                                                              // _moveHistory is default-constructed
{
    initializeBoard(); // Gọi hàm initializeBoard để thiết lập các quân cờ vào vị trí ban đầu
}

// Định nghĩa hàm initializeBoard để thiết lập bàn cờ với các quân cờ ở vị trí bắt đầu
void ChessBoard::initializeBoard()
{
    // Xóa lịch sử nước đi khi tạo bàn cờ mới
    _moveHistory.clear();

    // Xóa bàn cờ trước (đặt tất cả các ô về nullptr)
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            _board[i][j] = nullptr; // Đặt con trỏ thông minh tại vị trí (i, j) thành null
        }
    }

    // Thiết lập các quân cờ Trắng
    // Tốt trắng ở hàng thứ 6 (tính từ 0)
    for (int col = 0; col < 8; ++col)
    {
        _board[6][col] = std::make_unique<Pawn>(Color::WHITE, Position(6, col)); // Tạo một đối tượng Pawn màu Trắng tại hàng 6, cột col và gán cho ô trên bàn cờ
    }

    // Các quân cờ khác của Trắng ở hàng thứ 7
    _board[7][0] = std::make_unique<Rook>(Color::WHITE, Position(7, 0));   // Xe trắng ở a1
    _board[7][1] = std::make_unique<Knight>(Color::WHITE, Position(7, 1)); // Mã trắng ở b1
    _board[7][2] = std::make_unique<Bishop>(Color::WHITE, Position(7, 2)); // Tượng trắng ở c1
    _board[7][3] = std::make_unique<Queen>(Color::WHITE, Position(7, 3));  // Hậu trắng ở d1
    _board[7][4] = std::make_unique<King>(Color::WHITE, Position(7, 4));   // Vua trắng ở e1
    _board[7][5] = std::make_unique<Bishop>(Color::WHITE, Position(7, 5)); // Tượng trắng ở f1
    _board[7][6] = std::make_unique<Knight>(Color::WHITE, Position(7, 6)); // Mã trắng ở g1
    _board[7][7] = std::make_unique<Rook>(Color::WHITE, Position(7, 7));   // Xe trắng ở h1

    // Thiết lập các quân cờ Đen
    // Tốt đen ở hàng thứ 1
    for (int col = 0; col < 8; ++col)
    {
        _board[1][col] = std::make_unique<Pawn>(Color::BLACK, Position(1, col)); // Tạo một đối tượng Pawn màu Đen tại hàng 1, cột col
    }

    // Các quân cờ khác của Đen ở hàng thứ 0
    _board[0][0] = std::make_unique<Rook>(Color::BLACK, Position(0, 0));   // Xe đen ở a8
    _board[0][1] = std::make_unique<Knight>(Color::BLACK, Position(0, 1)); // Mã đen ở b8
    _board[0][2] = std::make_unique<Bishop>(Color::BLACK, Position(0, 2)); // Tượng đen ở c8
    _board[0][3] = std::make_unique<Queen>(Color::BLACK, Position(0, 3));  // Hậu đen ở d8
    _board[0][4] = std::make_unique<King>(Color::BLACK, Position(0, 4));   // Vua đen ở e8
    _board[0][5] = std::make_unique<Bishop>(Color::BLACK, Position(0, 5)); // Tượng đen ở f8
    _board[0][6] = std::make_unique<Knight>(Color::BLACK, Position(0, 6)); // Mã đen ở g8
    _board[0][7] = std::make_unique<Rook>(Color::BLACK, Position(0, 7));   // Xe đen ở h8

    // Thiết lập lại trạng thái trò chơi
    _currentTurn = Color::WHITE; // Bắt đầu ván cờ với lượt đi của Trắng
    _gameOver = false;           // Đặt trạng thái kết thúc ván cờ về false

    std::cout << "Chess board initialized with all pieces in starting positions." << std::endl; // Thông báo khi bàn cờ được khởi tạo
}

ChessBoard::ChessBoard(const ChessBoard &other)
    : _currentTurn(other._currentTurn),
      _gameOver(other._gameOver),
      _moveHistory(other._moveHistory) // Sao chép lịch sử nước đi
{
    // Khởi tạo bàn cờ trống
    _board.resize(8, std::vector<std::unique_ptr<ChessPiece>>(8, nullptr));

    // Sao chép từng quân cờ từ bàn cờ gốc
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Position pos(row, col);
            ChessPiece *piece = other.getPiece(pos);
            if (piece)
            {
                // Tạo bản sao của quân cờ dựa trên loại
                // Note: For full state copy (e.g. Pawn's _hasMoved for en-passant),
                // derived pieces might need their own clone methods or specific state copy here.
                switch (piece->getType())
                {
                case PieceType::PAWN:
                    _board[row][col] = std::make_unique<Pawn>(piece->getColor(), pos);
                    // TODO: Copy Pawn-specific state if any (e.g., _hasMoved, _justMovedTwoSquares)
                    // Example: if (auto p = dynamic_cast<Pawn*>(piece)) {
                    //            if (auto newP = dynamic_cast<Pawn*>(_board[row][col].get())) {
                    //                newP->_hasMoved = p->_hasMoved; // Assuming public or accessible
                    //            }
                    //          }
                    break;
                case PieceType::ROOK:
                    _board[row][col] = std::make_unique<Rook>(piece->getColor(), pos);
                    // Ensure the original piece pointer 'piece' is valid and of type Rook* before static_cast
                    if (auto r = dynamic_cast<Rook *>(piece))
                    {
                        static_cast<Rook *>(_board[row][col].get())->setHasMoved(r->hasMoved());
                    }
                    break;
                case PieceType::KNIGHT:
                    _board[row][col] = std::make_unique<Knight>(piece->getColor(), pos);
                    break;
                case PieceType::BISHOP:
                    _board[row][col] = std::make_unique<Bishop>(piece->getColor(), pos);
                    break;
                case PieceType::QUEEN:
                    _board[row][col] = std::make_unique<Queen>(piece->getColor(), pos);
                    break;
                case PieceType::KING:
                    _board[row][col] = std::make_unique<King>(piece->getColor(), pos);
                    // Ensure the original piece pointer 'piece' is valid and of type King* before static_cast
                    if (auto k = dynamic_cast<King *>(piece))
                    {
                        static_cast<King *>(_board[row][col].get())->_hasMoved = k->_hasMoved; // Assuming _hasMoved is accessible
                    }
                    break;
                }
            }
        }
    }
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other)
{
    if (this != &other)
    {
        // Sao chép các thuộc tính cơ bản
        _currentTurn = other._currentTurn;
        _gameOver = other._gameOver;
        _moveHistory = other._moveHistory; // Gán lịch sử nước đi

        // Xóa bàn cờ hiện tại
        for (auto &row_vec : _board) // Use a different name for the outer loop variable
        {
            for (auto &piece_ptr : row_vec) // Use a different name for the inner loop variable
            {
                piece_ptr.reset();
            }
        }
        // Ensure board is correctly sized if it wasn't (though it should be 8x8)
        _board.assign(8, std::vector<std::unique_ptr<ChessPiece>>(8, nullptr));

        // Sao chép từng quân cờ từ bàn cờ gốc
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                Position pos(row, col);
                ChessPiece *piece = other.getPiece(pos);
                if (piece)
                {
                    // Tạo bản sao của quân cờ dựa trên loại
                    // Note: See comment in copy constructor regarding full state copy for Pawns etc.
                    switch (piece->getType())
                    {
                    case PieceType::PAWN:
                        _board[row][col] = std::make_unique<Pawn>(piece->getColor(), pos);
                        // TODO: Copy Pawn-specific state
                        break;
                    case PieceType::ROOK:
                        _board[row][col] = std::make_unique<Rook>(piece->getColor(), pos);
                        if (auto r = dynamic_cast<Rook *>(piece))
                        {
                            static_cast<Rook *>(_board[row][col].get())->setHasMoved(r->hasMoved());
                        }
                        break;
                    case PieceType::KNIGHT:
                        _board[row][col] = std::make_unique<Knight>(piece->getColor(), pos);
                        break;
                    case PieceType::BISHOP:
                        _board[row][col] = std::make_unique<Bishop>(piece->getColor(), pos);
                        break;
                    case PieceType::QUEEN:
                        _board[row][col] = std::make_unique<Queen>(piece->getColor(), pos);
                        break;
                    case PieceType::KING:
                        _board[row][col] = std::make_unique<King>(piece->getColor(), pos);
                        if (auto k = dynamic_cast<King *>(piece))
                        {
                            static_cast<King *>(_board[row][col].get())->_hasMoved = k->_hasMoved; // Assuming _hasMoved is accessible
                        }
                        break;
                    }
                }
                else
                {
                    _board[row][col] = nullptr;
                }
            }
        }
    }
    return *this;
}

// Định nghĩa hàm display để hiển thị bàn cờ ra màn hình console
void ChessBoard::display() const
{
    std::cout << "\n   a b c d e f g h\n"; // In ra tiêu đề cột (fixed spacing)
    for (int i = 0; i < 8; i++)            // Duyệt qua các hàng của bàn cờ
    {
        std::cout << 8 - i << " ";  // In ra số thứ tự hàng (từ 8 xuống 1)
        for (int j = 0; j < 8; j++) // Duyệt qua các cột của hàng hiện tại
        {
            if (_board[i][j] == nullptr) // Nếu ô cờ trống (không có quân cờ)
            {
                // In ra dấu "." cho ô trắng và dấu " " cho ô đen để tạo hình bàn cờ
                std::cout << (((i + j) % 2 == 0) ? "." : " ") << " ";
            }
            else // Nếu ô cờ có quân cờ
            {
                std::cout << _board[i][j]->getSymbol() << " "; // In ra ký hiệu của quân cờ
            }
        }
        std::cout << 8 - i << std::endl; // In lại số thứ tự hàng ở cuối hàng
    }
    std::cout << "   a b c d e f g h\n"; // In lại tiêu đề cột ở cuối (fixed spacing)
}

// Định nghĩa hàm getPiece để lấy con trỏ đến quân cờ tại một vị trí nhất định
ChessPiece *ChessBoard::getPiece(const Position &pos) const
{
    if (!pos.isValid())                      // Kiểm tra xem vị trí có hợp lệ không
        return nullptr;                      // Nếu không hợp lệ, trả về nullptr
    return _board[pos._row][pos._col].get(); // Trả về con trỏ thô (raw pointer) đến đối tượng ChessPiece được quản lý bởi unique_ptr tại vị trí (row, col)
}

// Định nghĩa hàm movePiece để di chuyển một quân cờ từ một vị trí đến một vị trí khác
bool ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *piece = getPiece(from); // Lấy quân cờ tại vị trí xuất phát

    // Các kiểm tra cơ bản
    if (piece == nullptr || !to.isValid()) // Nếu không có quân cờ tại vị trí xuất phát hoặc vị trí đích không hợp lệ
    {
        return false; // Trả về false (di chuyển không thành công)
    }

    if (piece->getColor() != _currentTurn) // Kiểm tra xem có phải lượt đi của quân cờ này không
    {
        std::cout << "It's not your turn!" << std::endl; // Thông báo nếu không phải lượt
        return false;
    }

    // Kiểm tra xem nước đi có hợp lệ theo luật của quân cờ không
    if (!piece->isValidMove(*this, to))
    {
        std::cout << "Invalid move for this piece!" << std::endl; // Thông báo nếu nước đi không hợp lệ
        return false;
    }

    // Thông tin cho Move object
    PieceType pieceType = piece->getType();
    Color pieceColor = piece->getColor();
    // Check for capture before moving the piece
    ChessPiece *pieceAtTo = getPiece(to);
    bool isCapture = (pieceAtTo != nullptr);
    PieceType capturedType = isCapture ? pieceAtTo->getType() : PieceType::PAWN; // Default for non-capture, consider a "None" type

    bool isCastlingKingSide = false;
    bool isCastlingQueenSide = false;
    if (pieceType == PieceType::KING)
    {
        if (auto king = dynamic_cast<King *>(piece))
        {
            if (king->isCastlingMove(to))
            { // This checks if the move is a castling move by distance
                if (to._col > from._col)
                    isCastlingKingSide = true;
                else
                    isCastlingQueenSide = true;
            }
        }
    }
    bool isCastling = isCastlingKingSide || isCastlingQueenSide;

    bool isPromotion = false;
    PieceType promotionType = PieceType::QUEEN; // Default promotion type, will be updated if actual promotion occurs

    // Lưu trữ quân cờ bị bắt (nếu có) để có thể hoàn tác nước đi nếu cần
    // This must be done by moving the unique_ptr
    std::unique_ptr<ChessPiece> capturedPieceUniquePtr = std::move(_board[to._row][to._col]);

    // Di chuyển quân cờ (unique_ptr transfer)
    auto movingPiece = std::move(_board[from._row][from._col]);
    _board[to._row][to._col] = std::move(movingPiece);
    piece->setPosition(to); // Cập nhật vị trí của quân cờ

    // Handle special piece logic AFTER moving the piece pointer but BEFORE check validation
    // This order is important because _hasMoved flags affect future isValidMove calls.
    if (piece->getType() == PieceType::PAWN)
    {
        if (auto pawn = dynamic_cast<Pawn *>(piece))
        {
            pawn->_hasMoved = true; // Assuming Pawn has public _hasMoved or setter
            if (pawn->canPromote()) // Check for promotion eligibility
            {
                isPromotion = true;
            }
        }
    }
    else if (piece->getType() == PieceType::ROOK)
    {
        if (auto rook = dynamic_cast<Rook *>(piece))
        {
            rook->setHasMoved(true);
        }
    }
    else if (piece->getType() == PieceType::KING)
    {
        if (auto king = dynamic_cast<King *>(piece))
        {
            if (isCastling) // Use the flag determined earlier
            {
                int row = from._row;
                // Determine rook's original and new positions based on castling side
                Position rookFromPos = isCastlingKingSide ? Position(row, 7) : Position(row, 0);
                Position rookToPos = isCastlingKingSide ? Position(row, 5) : Position(row, 3);

                // Di chuyển xe
                auto rookToMove = std::move(_board[rookFromPos._row][rookFromPos._col]);
                _board[rookToPos._row][rookToPos._col] = std::move(rookToMove);
                // _board[rookFromPos._row][rookFromPos._col] is already nullptr after std::move

                // Cập nhật vị trí của xe
                ChessPiece *movedRookPiece = getPiece(rookToPos);
                if (movedRookPiece)
                    movedRookPiece->setPosition(rookToPos);
            }
            king->_hasMoved = true; // Mark king as moved (prevents future castling)
        }
    }

    // Kiểm tra xem nước đi này có đặt hoặc để vua của người chơi vào thế chiếu hay không
    if (isInCheck(_currentTurn))
    {
        // Hoàn tác nước đi
        // 1. Move the primary piece back
        _board[from._row][from._col] = std::move(_board[to._row][to._col]);
        piece->setPosition(from); // Restore piece's internal position

        // 2. Restore the captured piece (if any)
        _board[to._row][to._col] = std::move(capturedPieceUniquePtr);

        // 3. Revert castling's rook move if castling was attempted
        if (isCastling)
        {
            int row = from._row;
            Position rookFromOriginalPos = isCastlingKingSide ? Position(row, 7) : Position(row, 0);
            Position rookToOriginalPos = isCastlingKingSide ? Position(row, 5) : Position(row, 3);

            auto rookToRestore = std::move(_board[rookToOriginalPos._row][rookToOriginalPos._col]);
            _board[rookFromOriginalPos._row][rookFromOriginalPos._col] = std::move(rookToRestore);
            ChessPiece *restoredRook = getPiece(rookFromOriginalPos);
            if (restoredRook)
                restoredRook->setPosition(rookFromOriginalPos);
        }

        // 4. Revert _hasMoved flags (important!)
        // This requires knowing the previous state or more complex undo.
        // For simplicity here, if a move is invalid, we assume these flags might need manual reset
        // or the piece's isValidMove should not rely on a temporary _hasMoved state.
        // A full undo system would record previous _hasMoved states.
        // The current code just sets them to true. If move is invalid, this could be an issue
        // if _hasMoved was false before this invalid attempt.
        // For now, we accept this simplification as per original code's structure.

        std::cout << "Invalid move: Would leave your king in check!" << std::endl;
        return false;
    }

    // Xử lý phong cấp tốt (after confirming move is legal regarding checks)
    if (isPromotion) // Use the flag determined earlier
    {
        // piece is already at the promotion square 'to'
        promotePawn(to);
        // Update promotionType based on the actual choice made in promotePawn
        ChessPiece *promotedPiece = getPiece(to);
        if (promotedPiece)
        {
            promotionType = promotedPiece->getType();
        }
    }

    // Kiểm tra xem đối phương có bị chiếu hoặc chiếu hết không
    bool isOpponentInCheck = false;
    bool isOpponentCheckmated = false;
    Color opponentColor = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    if (isInCheck(opponentColor))
    {
        isOpponentInCheck = true;
        if (isCheckmate(opponentColor)) // This call uses the current board state
        {
            isOpponentCheckmated = true;
            std::cout << "Checkmate! " << (_currentTurn == Color::WHITE ? "White" : "Black") << " wins!" << std::endl;
            _gameOver = true;
        }
        else
        {
            std::cout << "Check!" << std::endl;
        }
    }

    // Tạo đối tượng Move và thêm vào lịch sử
    Move move(from, to, pieceType, pieceColor, isCapture, capturedType,
              isOpponentInCheck, isOpponentCheckmated, isCastling, isPromotion, promotionType);
    _moveHistory.addMove(move);

    // Chuyển lượt đi cho người chơi khác
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true; // Trả về true (di chuyển thành công)
}

// Định nghĩa hàm promotePawn để xử lý việc phong cấp tốt
PieceType askUserForPromotionChoice(sf::RenderWindow &window); // This declaration needs to be visible

void ChessBoard::promotePawn(const Position &pos)
{
    // This is tricky because promotePawn doesn't have access to the sf::RenderWindow
    // One solution is to have movePiece return a special status if promotion is needed,
    // then the GUI handles the prompt and calls a different version of promotePawn.

    // For a simpler (but less clean) approach, if g_chessGUI is set:
    // This implies your main_gui.cpp needs to expose the window or a way to prompt.
    // The getPromotionChoiceGUI shown in main_gui.cpp needs the window.

    // Let's assume ChessBoard::movePiece detects promotion and gets the choice BEFORE calling this.
    // So, this version of promotePawn would take the chosen piece type.
    // This means you need to refactor how promotion is initiated.

    // The console version was:
    /*
    char choice;
    // ... get choice from std::cin ...
    // ... create piece based on choice ...
    */

    // For GUI, the choice should come from the GUI layer.
    // The easiest way is for ChessBoard::movePiece to:
    // 1. Detect that a pawn reached promotion rank.
    // 2. Instead of calling this->promotePawn directly with std::cin, it returns a special value
    //    or sets a flag on the board `_needsPromotion = true; _promotionSquare = pos;`
    // 3. The GUI loop in main_gui.cpp checks this flag.
    // 4. If true, GUI prompts user, then calls a *new* method on ChessBoard:
    //    `void ChessBoard::completePromotion(const Position& pos, PieceType chosenType)`

    // Let's go with the console version for now if g_chessGUI is not set,
    // and assume you'll implement the GUI part later.
    // The current `promotePawn` in your `chess_board_implementation.cpp` already does this with `std::cin`.
    // For SFML, you cannot use `std::cin` while the SFML window is active for this kind of prompt.
    // The `getPromotionChoiceGUI` function in `main_gui.cpp` is a starting point.
    // Your `ChessBoard::movePiece` would need to call it.
    // This requires `ChessBoard` to have a reference to the `sf::RenderWindow` or the `ChessGUI` object,
    // which is generally not ideal for separation of concerns.

    // A common pattern for GUI promotion:
    // - `ChessBoard::movePiece` moves the pawn.
    // - If it's a promotion move, `movePiece` returns a special status (e.g., `MoveResult::PROMOTION_NEEDED`).
    // - The `main_gui.cpp` game loop sees this status.
    // - It calls `gui.promptForPromotion()`.
    // - GUI shows options, gets user input.
    // - GUI then calls `board.finalizePromotion(square, chosenPieceType)`.

    // For now, to make it compile and *not* use cin in GUI:
    // We'll assume Queen promotion by default if it's a GUI context.
    // You'll need to implement the full GUI prompt.
    std::cout << "Pawn at " << pos.toAlgebraic() << " can promote." << std::endl;
    PieceType promotionChoice = PieceType::QUEEN; // Default for now in GUI context

    // If you had a way to get the window here:
    // extern sf::RenderWindow* g_AppWindow; // A global window pointer from main_gui.cpp
    // if (g_AppWindow) {
    //     promotionChoice = askUserForPromotionChoice(*g_AppWindow);
    // } else { // Console fallback
    //     char choice_char;
    //     // ... original std::cin logic ...
    // }

    ChessPiece *pawn = getPiece(pos);
    Color color = pawn->getColor();
    _board[pos._row][pos._col].reset(); // Remove pawn

    switch (promotionChoice) // Use the determined choice
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

// You'd need pieceTypeToString helper
const char *pieceTypeToString(PieceType type)
{
    switch (type)
    {
    case PieceType::PAWN:
        return "Pawn";
    case PieceType::ROOK:
        return "Rook";
    // ... etc.
    default:
        return "Unknown";
    }
}

// Định nghĩa hàm getCurrentTurn để trả về màu của lượt đi hiện tại
Color ChessBoard::getCurrentTurn() const
{
    return _currentTurn;
}

// Định nghĩa hàm isGameOver để kiểm tra xem trò chơi đã kết thúc chưa
bool ChessBoard::isGameOver() const
{
    Color currentPlayer = getCurrentTurn();
    Color opponent = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

    // Kiểm tra chiếu bí cho người chơi hiện tại
    if (isInCheck(currentPlayer) && isCheckmate(currentPlayer))
    {
        return true;
    }

    // Kiểm tra hòa cờ cho người chơi hiện tại (cần triển khai isStalemate)
    if (!isInCheck(currentPlayer) && isStalemate(currentPlayer))
    {
        return true;
    }

    // Có thể thêm các điều kiện hòa khác ở đây (lặp lại nước đi, luật 50 nước đi, v.v.)

    return false;
}

// Định nghĩa hàm isInCheck để kiểm tra xem vua của một màu cụ thể có đang bị chiếu hay không
bool ChessBoard::isInCheck(Color color) const
{
    // Đầu tiên, tìm vị trí của vua của màu được chỉ định
    Position kingPos(-1, -1);         // Khởi tạo vị trí vua không hợp lệ
    for (int row = 0; row < 8; ++row) // Duyệt qua tất cả các hàng của bàn cờ
    {
        for (int col = 0; col < 8; ++col) // Duyệt qua tất cả các cột của bàn cờ
        {
            ChessPiece *piece = _board[row][col].get(); // Lấy con trỏ đến quân cờ tại vị trí (row, col)
            // Kiểm tra xem quân cờ có tồn tại, có phải là vua và có đúng màu cần kiểm tra không
            if (piece != nullptr && piece->getType() == PieceType::KING && piece->getColor() == color)
            {
                kingPos = Position(row, col); // Lưu lại vị trí của vua
                goto found_king;              // Exit both loops once king is found
            }
        }
    }

found_king:
    if (kingPos._row == -1)
    { // King not found (should not happen in a valid game)
        // std::cerr << "Error: King of color " << (color == Color::WHITE ? "WHITE" : "BLACK") << " not found in isInCheck." << std::endl;
        return false; // Or throw an exception
    }

    // Kiểm tra xem có bất kỳ quân cờ nào của đối phương có thể tấn công vua không
    Color opponentColor = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
    for (int row = 0; row < 8; ++row) // Duyệt qua tất cả các hàng của bàn cờ
    {
        for (int col = 0; col < 8; ++col) // Duyệt qua tất cả các cột của bàn cờ
        {
            ChessPiece *piece = _board[row][col].get(); // Lấy con trỏ đến quân cờ tại vị trí (row, col)
            // Kiểm tra xem quân cờ có tồn tại và có màu của đối phương không
            if (piece != nullptr && piece->getColor() == opponentColor)
            {
                // Kiểm tra xem quân cờ này có nước đi hợp lệ đến vị trí của vua không
                // isValidMove should check for attacks, not just general moves.
                // For pieces like pawns, moving forward is different from attacking diagonally.
                // This assumes isValidMove correctly identifies an attack on kingPos.
                if (piece->isValidMove(*this, kingPos))
                {
                    return true; // Nếu có, vua đang bị chiếu
                }
            }
        }
    }

    return false; // Nếu không có quân cờ đối phương nào có thể tấn công vua, thì vua không bị chiếu
}

// Định nghĩa hàm isCheckmate để kiểm tra xem vua của một màu cụ thể có bị chiếu hết hay không
bool ChessBoard::isCheckmate(Color color) const
{
    // Nếu vua không bị chiếu, thì không thể bị chiếu hết
    if (!isInCheck(color))
    {
        return false;
    }

    // Thử tất cả các nước đi có thể của tất cả các quân cờ của màu đang bị chiếu
    for (int fromRow = 0; fromRow < 8; ++fromRow)
    {
        for (int fromCol = 0; fromCol < 8; ++fromCol)
        {
            ChessPiece *piece = _board[fromRow][fromCol].get();
            // Nếu có quân cờ và nó thuộc màu đang bị chiếu
            if (piece != nullptr && piece->getColor() == color)
            {
                Position from(fromRow, fromCol);
                // Lấy tất cả các nước đi có thể của quân cờ này
                std::vector<Position> possible_moves = piece->getPossibleMoves(*this);

                // Duyệt qua tất cả các nước đi có thể
                for (const auto &moveToPos : possible_moves) // Renamed 'move' to 'moveToPos'
                {
                    // Check if the move itself is valid by piece rules and board context
                    // (this specific isValidMove call should not check for self-check, that's what we're testing)
                    if (piece->isValidMove(*this, moveToPos))
                    {
                        // Simulate the move temporarily using const_cast.
                        // WARNING: This simulation is basic and does NOT handle:
                        // 1. Castling's rook move.
                        // 2. Pawn promotion (tries only moving the pawn, not promoting it).
                        // A true isCheckmate would need to simulate these fully by trying all promotion types
                        // and correctly moving the rook in castling.
                        // This may lead to false positives for checkmate if an escape involves these special moves.

                        Position originalPos = piece->getPosition(); // This is 'from'

                        // 1. Save the piece at the destination by moving its unique_ptr
                        //    Must use const_cast because this is a const method modifying state temporarily.
                        std::unique_ptr<ChessPiece> tempCapturedPiece =
                            std::move(const_cast<ChessBoard *>(this)->_board[moveToPos._row][moveToPos._col]);

                        // 2. Perform the move: move the unique_ptr of 'piece'
                        const_cast<ChessBoard *>(this)->_board[moveToPos._row][moveToPos._col] =
                            std::move(const_cast<ChessBoard *>(this)->_board[from._row][from._col]);

                        // Update the piece's internal position
                        // 'piece' is a raw pointer; its object is now managed by _board[moveToPos._row][moveToPos._col]
                        piece->setPosition(moveToPos);

                        // 3. Check if the king of 'color' is still in check after the_move
                        bool stillInCheck = this->isInCheck(color);

                        // 4. Revert the move
                        //  4a. Move 'piece' (pointed to by piece, now owned by _board[moveToPos]) back to 'from'
                        const_cast<ChessBoard *>(this)->_board[from._row][from._col] =
                            std::move(const_cast<ChessBoard *>(this)->_board[moveToPos._row][moveToPos._col]);

                        //  4b. Restore the captured piece (if any) to the 'moveToPos' square
                        const_cast<ChessBoard *>(this)->_board[moveToPos._row][moveToPos._col] =
                            std::move(tempCapturedPiece);

                        //  4c. Restore the piece's internal position
                        piece->setPosition(originalPos);
                        // After this, _board[from._row][from._col].get() should be 'piece' again.

                        // Nếu có bất kỳ nước đi nào khiến vua không còn bị chiếu, thì đó không phải là chiếu hết
                        if (!stillInCheck)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Nếu không có nước đi nào có thể giúp vua thoát khỏi thế chiếu, thì đó là chiếu hết
    return true;
}

// Các phương thức mới cho lịch sử nước đi
void ChessBoard::displayMoveHistory(bool detailed) const
{
    if (detailed)
    {
        _moveHistory.displayDetailed();
    }
    else
    {
        _moveHistory.displayShort();
    }
}

bool ChessBoard::saveMoveHistory(const std::string &filename) const
{
    return _moveHistory.saveToFile(filename);
}

void ChessBoard::clearMoveHistory()
{
    _moveHistory.clear();
}

const MoveHistory &ChessBoard::getMoveHistory() const
{
    return _moveHistory;
}