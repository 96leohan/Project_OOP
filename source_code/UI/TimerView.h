#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>

class TimerView {
public:
    enum class TimeControl {
        Blitz,      // 5 phút
        Rapid,      // 15 phút
        Classical   // 30 phút
    };

    TimerView();
    void setMode(TimeControl mode);

    void update();                     // gọi mỗi frame
    void switchTurn();                // chuyển lượt người chơi
    void draw(sf::RenderWindow& window);
    bool isTimeUp() const;            // kiểm tra người chơi hiện tại hết giờ chưa

private:
    sf::Font font;
    sf::Text whiteText, blackText;

    int whiteTimeSeconds;
    int blackTimeSeconds;
    bool whiteTurn;

    std::chrono::steady_clock::time_point lastUpdate;

    void updateClock();
    std::string formatTime(int seconds) const;
};
