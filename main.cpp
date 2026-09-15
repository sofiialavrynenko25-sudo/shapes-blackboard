#include <iostream>
#include "cli.h"
#include "board.h"

int main()
{
    Board board(20, 20);
    CLI cli(board);

    std::string input;

    while (true) 
    {
        std::cout << "> ";

        if (!std::getline(std::cin, input) || input == "exit")
        {
            break;
        }

        cli.Process(input);
    }

    return 0;
}