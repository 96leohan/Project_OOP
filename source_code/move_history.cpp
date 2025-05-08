// move_history.cpp
#include "move_history.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void MoveHistory::addMove(const Move &move)
{
    _moves.push_back(move);
}

void MoveHistory::clear()
{
    _moves.clear();
}

size_t MoveHistory::getSize() const
{
    return _moves.size();
}

const Move *MoveHistory::getLastMove() const
{
    if (_moves.empty())
    {
        return nullptr;
    }
    return &_moves.back();
}

void MoveHistory::displayShort() const
{
    if (_moves.empty())
    {
        std::cout << "No moves recorded yet.\n";
        return;
    }

    std::cout << "\n=== Move History ===\n";

    for (size_t i = 0; i < _moves.size(); ++i)
    {
        // Hiển thị số thứ tự nước đi
        if (i % 2 == 0)
        {
            std::cout << (i / 2 + 1) << ". ";
        }

        // Hiển thị nước đi theo kí hiệu đại số chuẩn
        std::cout << _moves[i].toAlgebraic();

        // Xuống dòng sau mỗi nước đi của đen
        if (i % 2 == 1 || i == _moves.size() - 1)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << "==================\n";
}

void MoveHistory::displayDetailed() const
{
    if (_moves.empty())
    {
        std::cout << "No moves recorded yet.\n";
        return;
    }

    std::cout << "\n=== Detailed Move History ===\n";

    for (size_t i = 0; i < _moves.size(); ++i)
    {
        // Hiển thị số thứ tự và mô tả chi tiết nước đi
        std::cout << std::setw(3) << (i + 1) << ". " << _moves[i].toString() << std::endl;
    }

    std::cout << "============================\n";
}

bool MoveHistory::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    file << "Chess Game Move History\n";
    file << "======================\n\n";

    // Lưu lịch sử theo định dạng PGN đơn giản
    for (size_t i = 0; i < _moves.size(); ++i)
    {
        if (i % 2 == 0)
        {
            file << (i / 2 + 1) << ". ";
        }

        file << _moves[i].toAlgebraic();

        if (i % 2 == 1)
        {
            file << std::endl;
        }
        else
        {
            file << " ";
        }
    }

    file << "\n\n";

    // Lưu lịch sử chi tiết
    file << "Detailed History:\n";
    file << "----------------\n";
    for (size_t i = 0; i < _moves.size(); ++i)
    {
        file << (i + 1) << ". " << _moves[i].toString() << "\n";
    }

    file.close();
    return true;
}

std::string MoveHistory::toString() const
{
    std::stringstream ss;

    for (size_t i = 0; i < _moves.size(); ++i)
    {
        if (i % 2 == 0)
        {
            ss << (i / 2 + 1) << ". ";
        }

        ss << _moves[i].toAlgebraic();

        if (i % 2 == 1)
        {
            ss << "\n";
        }
        else
        {
            ss << " ";
        }
    }

    return ss.str();
}