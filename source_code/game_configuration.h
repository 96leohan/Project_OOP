#pragma once

namespace GameConfig
{
    // Window settings
    constexpr unsigned int WINDOW_WIDTH = 900;
    constexpr unsigned int WINDOW_HEIGHT = 1000;
    constexpr unsigned int FRAMERATE_LIMIT = 60;

    // Board settings
    constexpr unsigned int BOARD_SIZE = 800;
    constexpr unsigned int BOARD_OFFSET_X = 50;
    constexpr unsigned int BOARD_OFFSET_Y = 50;
    constexpr unsigned int STATUS_TEXT_HEIGHT = 100;

    // Colors
    constexpr int BACKGROUND_GRAY = 128;

    // Game settings
    constexpr Color DEFAULT_AI_COLOR = Color::BLACK;

    // Resource paths
    const std::string RESOURCE_PATH = "Resource/";
    const std::string PIECE_IMAGE_PATH = RESOURCE_PATH + "pieces/";
}