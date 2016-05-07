
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility>
#include <string>

class Board
{
public:
    Board(const unsigned int& size)
        : m_size(size),
          m_board(size, std::vector<std::string>(size))
    {}

    typedef std::pair<unsigned int, unsigned int> BoardPosition;
    typedef std::vector<BoardPosition> BoardPositions;
  
    void updateAndPrint(const BoardPositions& positions);
    void update(const BoardPositions& positions);
    void print() const;
    void reset();

private:
    std::string invertColors(const std::string& c) const;
    void updatePosition(const unsigned int& index_row, const unsigned int& index_col, const std::string& c); 

    const unsigned int m_size;
    std::vector<std::vector<std::string>> m_board;

};

#endif /* BOARD_H */

