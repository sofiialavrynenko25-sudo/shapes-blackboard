#pragma once

#include <iostream>
#include <vector> 
#include <cmath>
#include <string>

#include "board.h"

class CLI 
{
    private:
        Board& _board;

    public:
        CLI(Board& board)
            : _board(board) {}
        
        void Process(const std::string& inpu);

        ~CLI() = default;
};