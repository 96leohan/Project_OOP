cmake_minimum_required(VERSION 3.10)
project(SFMLChessGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
# You might need to set SFML_DIR if SFML is not in a standard path
# e.g., set(SFML_DIR "path/to/your/SFML_install/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add your executable
add_executable(SFMLChessGame
    source/main_gui.cpp # You'll create this new main for the GUI
    source/chess_board_implementation.cpp
    source/chess_piece_im.cpp # Consider renaming to chess_piece.cpp
    source/position.cpp
    source/King.cpp
    source/Queen.cpp
    source/Rook.cpp
    source/Bishop.cpp
    source/Knight.cpp
    source/Pawn.cpp
    source/ai_player.cpp # If you integrate AI into GUI
    source/chess_gui.cpp
    # Add other .cpp files if any (e.g., move.cpp, move_history.cpp)
)

# Include directories
target_include_directories(SFMLChessGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source # To find your .h files
    ${SFML_INCLUDE_DIR}
)

# Link SFML libraries
target_link_libraries(SFMLChessGame PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Optional: Copy resources to build directory for easier execution
# This is a simple way, better for deployment might be install rules
# Ensure your executable can find the 'resources' folder relative to its runtime location.
# If you run from the build directory and 'resources' is in the source root:
# One way is to copy them:
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
# Or, ensure your code loads resources from a path relative to the executable,
# or configure an install step. For development, copying or running from source dir (if paths are relative) is common.

# For Windows, if you want a windowed app without a console
# add_executable(SFMLChessGame WIN32 ... )
# But for debugging, keep the console for now.