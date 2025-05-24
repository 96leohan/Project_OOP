#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class HistoryView {
public:
    HistoryView();

    // Vẽ lịch sử nước đi lên cửa sổ
    void draw(sf::RenderWindow& window);

    // Thêm một nước đi mới
    void addMove(const std::string& move);

    // Xóa toàn bộ lịch sử (khi chơi lại)
    void reset();

private:
    sf::Font font;
    sf::Text historyText;

    std::vector<std::string> moves; // danh sách nước đi dạng string
    void updateDisplay();           // cập nhật nội dung hiển thị
};
