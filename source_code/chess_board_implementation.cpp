#include "chess_board.h"
#include <iostream>
#include <limits> //dùng std::numeric_limits để xử lý lỗi nhập liệu
#include <cctype> // std::toupper để chuyển đổi ký tự thành chữ hoa

// Định nghĩa constructor của lớp ChessBoard
ChessBoard::ChessBoard()
    : _board(8, std::vector<std::unique_ptr<ChessPiece>>(8)), // Khởi tạo bàn cờ là một vector 2D 8x8 chứa các con trỏ thông minh (unique_ptr) đến các đối tượng ChessPiece
      _currentTurn(Color::WHITE),                             // Khởi tạo lượt đi hiện tại là Trắng
      _gameOver(false)                                        // Khởi tạo trạng thái trò chơi là chưa kết thúc
{
    initializeBoard(); // Gọi hàm initializeBoard để thiết lập các quân cờ vào vị trí ban đầu
}

// Định nghĩa hàm initializeBoard để thiết lập bàn cờ với các quân cờ ở vị trí bắt đầu
void ChessBoard::initializeBoard()
{
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

// Định nghĩa hàm display để hiển thị bàn cờ ra màn hình console
void ChessBoard::display() const
{
    std::cout << "\n  a b c d e f g h\n"; // In ra tiêu đề cột
    for (int i = 0; i < 8; i++)           // Duyệt qua các hàng của bàn cờ
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
    std::cout << "  a b c d e f g h\n"; // In lại tiêu đề cột ở cuối
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

    // Trường hợp đặc biệt cho Tốt
    if (piece->getType() == PieceType::PAWN)
    {
        auto pawn = dynamic_cast<Pawn *>(piece); // Ép kiểu con trỏ ChessPiece thành con trỏ Pawn
        pawn->_hasMoved = true;                  // Đánh dấu là tốt đã di chuyển (quan trọng cho nước đi đầu tiên và en passant)

        // Logic en passant sẽ được thêm vào đây
    }
    // Trường hợp đặc biệt cho Xe
    else if (piece->getType() == PieceType::ROOK)
    {
        dynamic_cast<Rook *>(piece)->setHasMoved(true); // Đánh dấu là xe đã di chuyển (quan trọng cho nhập thành)
    }
    // Trường hợp đặc biệt cho Vua
    else if (piece->getType() == PieceType::KING)
    {
        auto king = dynamic_cast<King *>(piece); // Ép kiểu con trỏ ChessPiece thành con trỏ King

        // Xử lý nhập thành
        if (king->isCastlingMove(to))
        {
            int row = piece->getPosition()._row;     // Lấy hàng của vua
            int fromCol = piece->getPosition()._col; // Lấy cột xuất phát của vua
            int toCol = to._col;                     // Lấy cột đích của vua

            // Xác định xe nào sẽ di chuyển dựa trên nhập thành cánh vua hay cánh hậu
            Position rookFromPos(row, 7), rookToPos(row, 5); // Mặc định cho nhập thành cánh vua
            if (toCol > fromCol)                             // Nhập thành cánh vua
            {
                rookFromPos = Position(row, 7); // Vị trí ban đầu của xe cánh vua
                rookToPos = Position(row, 5);   // Vị trí đích của xe cánh vua
            }
            else // Nhập thành cánh hậu
            {
                rookFromPos = Position(row, 0); // Vị trí ban đầu của xe cánh hậu
                rookToPos = Position(row, 3);   // Vị trí đích của xe cánh hậu
            }

            // Di chuyển xe
            auto rook = std::move(_board[rookFromPos._row][rookFromPos._col]); // Lấy unique_ptr của xe
            _board[rookToPos._row][rookToPos._col] = std::move(rook);          // Di chuyển unique_ptr của xe đến vị trí mới
            _board[rookFromPos._row][rookFromPos._col] = nullptr;              // Đặt vị trí cũ của xe thành null

            // Cập nhật vị trí của xe
            ChessPiece *rookPiece = getPiece(rookToPos);
            rookPiece->setPosition(rookToPos);
        }

        king->_hasMoved = true; // Đánh dấu là vua đã di chuyển (ngăn không cho nhập thành sau này)
    }

    // Lưu trữ quân cờ bị bắt (nếu có) để có thể hoàn tác nước đi nếu cần
    std::unique_ptr<ChessPiece> capturedPiece = std::move(_board[to._row][to._col]);

    // Di chuyển quân cờ
    auto movingPiece = std::move(_board[from._row][from._col]); // Lấy unique_ptr của quân cờ di chuyển
    _board[to._row][to._col] = std::move(movingPiece);          // Di chuyển unique_ptr đến vị trí đích
    piece->setPosition(to);                                     // Cập nhật vị trí của quân cờ

    // Kiểm tra xem nước đi này có đặt hoặc để vua của người chơi vào thế chiếu hay không
    if (isInCheck(_currentTurn))
    {
        // Hoàn tác nước đi
        _board[from._row][from._col] = std::move(_board[to._row][to._col]); // Di chuyển quân cờ trở lại vị trí cũ
        _board[to._row][to._col] = std::move(capturedPiece);                // Đặt lại quân cờ bị bắt (nếu có)
        piece->setPosition(from);                                           // Cập nhật lại vị trí của quân cờ

        std::cout << "Invalid move: Would leave your king in check!" << std::endl; // Thông báo lỗi
        return false;                                                              // Trả về false (nước đi không hợp lệ)
    }

    // Xử lý phong cấp tốt
    if (piece->getType() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn->canPromote())
        {
            promotePawn(to); // Gọi hàm phong cấp tốt
        }
    }

    // Kiểm tra xem đối phương có bị chiếu hết không
    Color opponentColor = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    if (isInCheck(opponentColor))
    {
        if (isCheckmate(opponentColor))
        {
            std::cout << "Checkmate! " << (_currentTurn == Color::WHITE ? "White" : "Black") << " wins!" << std::endl;
            _gameOver = true; // Đánh dấu trò chơi kết thúc
        }
        else
        {
            std::cout << "Check!" << std::endl; // Thông báo chiếu
        }
    }

    // Chuyển lượt đi cho người chơi khác
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true; // Trả về true (di chuyển thành công)
}

// Định nghĩa hàm promotePawn để xử lý việc phong cấp tốt
void ChessBoard::promotePawn(const Position &pos)
{
    char choice;
    bool validChoice = false;

    while (!validChoice)
    {
        std::cout << "Promote pawn to (Q)ueen, (R)ook, (B)ishop, or k(N)ight? ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Xóa bộ đệm đầu vào

        choice = std::toupper(choice); // Chuyển đổi lựa chọn thành chữ hoa để dễ so sánh
        if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N')
        {
            validChoice = true;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    ChessPiece *pawn = getPiece(pos); // Lấy con trỏ đến tốt cần phong cấp
    Color color = pawn->getColor();   // Lấy màu của tốt

    // Loại bỏ tốt khỏi bàn cờ
    _board[pos._row][pos._col] = nullptr;

    // Tạo quân cờ mới dựa trên lựa chọn của người chơi
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

// Định nghĩa hàm getCurrentTurn để trả về màu của lượt đi hiện tại
Color ChessBoard::getCurrentTurn() const
{
    return _currentTurn;
}

// Định nghĩa hàm isGameOver để kiểm tra xem trò chơi đã kết thúc chưa
bool ChessBoard::isGameOver() const
{
    return _gameOver;
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
                break;                        // Thoát khỏi vòng lặp cột vì đã tìm thấy vua
            }
        }
        if (kingPos._row != -1) // Nếu đã tìm thấy vua (hàng của vua không còn là -1)
            break;              // Thoát khỏi vòng lặp hàng
    }

    // Kiểm tra xem có bất kỳ quân cờ nào của đối phương có thể tấn công vua không
    for (int row = 0; row < 8; ++row) // Duyệt qua tất cả các hàng của bàn cờ
    {
        for (int col = 0; col < 8; ++col) // Duyệt qua tất cả các cột của bàn cờ
        {
            ChessPiece *piece = _board[row][col].get(); // Lấy con trỏ đến quân cờ tại vị trí (row, col)
            // Kiểm tra xem quân cờ có tồn tại và có màu khác với màu của vua đang xét không
            if (piece != nullptr && piece->getColor() != color)
            {
                // Kiểm tra xem quân cờ này có nước đi hợp lệ đến vị trí của vua không
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
    for (int fromRow = 0; fromRow < 8; ++fromRow) // Duyệt qua tất cả các hàng
    {
        for (int fromCol = 0; fromCol < 8; ++fromCol) // Duyệt qua tất cả các cột
        {
            ChessPiece *piece = _board[fromRow][fromCol].get(); // Lấy quân cờ tại vị trí (fromRow, fromCol)
            // Nếu có quân cờ và nó thuộc màu đang bị chiếu
            if (piece != nullptr && piece->getColor() == color)
            {
                // Lấy tất cả các nước đi hợp lệ có thể của quân cờ này
                std::vector<Position> moves = piece->getPossibleMoves(*this);

                // Duyệt qua tất cả các nước đi có thể
                for (const auto &move : moves)
                {
                    // Lưu trạng thái hiện tại của bàn cờ để có thể khôi phục sau khi thử nước đi
                    Position from(fromRow, fromCol);
                    std::unique_ptr<ChessPiece> savedDestPiece = nullptr;
                    if (_board[move._row][move._col]) // Nếu có quân cờ ở vị trí đích
                    {
                        savedDestPiece = std::make_unique<ChessPiece>(*_board[move._row][move._col]); // Sao chép quân cờ bị bắt
                    }

                    // Thử thực hiện nước đi (tạm thời)
                    if (piece->isValidMove(*this, move))
                    {
                        auto movingPiece = std::move(const_cast<ChessBoard *>(this)->_board[from._row][from._col]);
                        const_cast<ChessBoard *>(this)->_board[move._row][move._col] = std::move(movingPiece);
                        piece->setPosition(move);

                        // Kiểm tra xem sau nước đi này, vua có còn bị chiếu không
                        bool stillInCheck = isInCheck(color);

                        // Khôi phục lại trạng thái bàn cờ
                        auto movedPiece = std::move(const_cast<ChessBoard *>(this)->_board[move._row][move._col]);
                        const_cast<ChessBoard *>(this)->_board[from._row][fromCol] = std::move(movedPiece);
                        if (savedDestPiece)
                        {
                            const_cast<ChessBoard *>(this)->_board[move._row][move._col] = std::move(savedDestPiece);
                        }
                        piece->setPosition(from);

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