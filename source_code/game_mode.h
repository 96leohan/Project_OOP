// game_mode.h
#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <string>

enum class GameMode
{
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_HUMAN
};

class GameModeManager
{
private:
    GameMode _currentMode;
    int _aiDifficulty; // 1: Easy, 2: Medium, 3: Hard

public:
    GameModeManager() : _currentMode(GameMode::HUMAN_VS_HUMAN), _aiDifficulty(2) {}

    GameMode getCurrentMode() const { return _currentMode; }
    void setCurrentMode(GameMode mode) { _currentMode = mode; }

    int getAIDifficulty() const { return _aiDifficulty; }
    void setAIDifficulty(int difficulty)
    {
        if (difficulty >= 1 && difficulty <= 3)
            _aiDifficulty = difficulty;
    }

    std::string getModeString() const
    {
        switch (_currentMode)
        {
        case GameMode::HUMAN_VS_HUMAN:
            return "Human vs Human";
        case GameMode::HUMAN_VS_AI:
            return "Human vs AI";
        case GameMode::AI_VS_HUMAN:
            return "AI vs Human";
        default:
            return "Unknown";
        }
    }

    std::string getDifficultyString() const
    {
        switch (_aiDifficulty)
        {
        case 1:
            return "Easy";
        case 2:
            return "Medium";
        case 3:
            return "Hard";
        default:
            return "Unknown";
        }
    }
};

#endif // GAME_MODE_H