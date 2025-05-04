cmake_minimum_required(VERSION 3.10)
project(ChessGame VERSION 1.0)

# Cài đặt chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML path
set(SFML_DIR "D:/SFML library/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/lib/cmake/SFML")

# Tìm thư viện SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Danh sách tất cả các file nguồn
set(SOURCE_FILES
    source_code/position_implementation.cpp
    source_code/chess_piece_implementation.cpp
    source_code/chess_board_implementation.cpp
    source_code/main_implementation.cpp
    source_code/king.cpp
    source_code/queen.cpp
    source_code/pawn.cpp
    source_code/bishop.cpp
    source_code/rook.cpp
    source_code/knight.cpp
    source_code/AI_player.cpp
    source_code/texture_manager.cpp
)

# Tạo thư viện cho các file nguồn (tất cả trừ main)
list(REMOVE_ITEM SOURCE_FILES source_code/main_implementation.cpp)
add_library(chess_lib ${SOURCE_FILES})

# Liên kết thư viện SFML với thư viện chess_lib
target_link_libraries(chess_lib PUBLIC sfml-graphics sfml-window sfml-system)

# Tạo tệp thực thi chính
add_executable(ChessGame source_code/main_implementation.cpp)
target_link_libraries(ChessGame PRIVATE chess_lib)

# Đặt thư mục include cho header
target_include_directories(chess_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source_code)
target_include_directories(ChessGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source_code)

# Copy các tài nguyên (nếu có) vào thư mục build
file(COPY ${CMAKE_SOURCE_DIR}/resource DESTINATION ${CMAKE_BINARY_DIR})