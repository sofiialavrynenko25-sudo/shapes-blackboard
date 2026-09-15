#include <iostream>
#include "cli.h"
#include "board.h"

int main()
{
    Board board(40, 20);
    CLI cli(board);

    cli.Run();
    
    return 0;
}