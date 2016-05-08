
#include "Board.h"

#include <iostream>

void Board::updatePosition(const size_t& index_row, const size_t& index_col, const std::string& c)
{
    if (((index_col + index_row) % 2) == 0)
    {
        this->m_board[index_row][index_col] = this->invertColors(c);
    }
    else
    {
        this->m_board[index_row][index_col] = c;
    }
}

void Board::reset()
{
    for (size_t index_row = 0; index_row < this->m_size; index_row++)
    {
        for (size_t index_column = 0; index_column < this->m_size; index_column++)
        {
            this->updatePosition(index_row, index_column, "  ");
        }
    }
}

void Board::update(const BoardPositions& positions)
{
    this->reset();

    for (auto queen_pos : positions)
    {
        size_t index_row = queen_pos.first;
        size_t index_col = queen_pos.second;

        this->updatePosition(index_row, index_col, "QQ");
    }
}

void Board::print() const
{
    for (auto row : this->m_board)
    {
        for (auto pos : row)
        {
            std::cout << pos;
        }
        std::cout << std::endl;
    }
}

void Board::updateAndPrint(const BoardPositions& positions)
{
    this->update(positions);
    this->print();
}

std::string Board::invertColors(const std::string& c) const
{
    return "\033[7m" + c + "\033[0m";
}

