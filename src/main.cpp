
#include "Board.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Board board(50u);
    Board::BoardPositions positions = {
        {1, 2},
        {3, 4},
        {4, 4}
    };
    
    board.updateAndPrint(positions);
}
