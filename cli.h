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
        
        void Draw();

        void List();

        void Shapes();

        void Add();

        void Select();

        void Remove();

        void Edit();

        void Paint();

        void Move();

        void Clear();

        void Run();

        ~CLI() = default;
};