#include <cmath>
#include <iostream>
#include "triangle.h"

std::string Triangle::GetType() const
{
    return "triangle";
}

int Triangle::GetSide() const
{
    return _side;
}

bool Triangle::CheckCoordinates(int x, int y) const
{
    float h = (std::sqrt(3.0) / 2.0) * _side;
    float R = (std::sqrt(3.0) / 3.0) * _side;
    float r = (std::sqrt(3.0) / 6.0) * _side;

    float x1 = _x;
    float y1 = _y - R;
    float x2 = _x - _side / 2.0;
    float y2 = _y + r;
    float x3 = _x + _side / 2.0;
    float y3 = _y + r;

    int intersections = 0;

    float xs[3] = {x1, x2, x3};
    float ys[3] = {y1, y2, y3};

    for (int i = 0; i < 3 ; i++)
    {
        int j = i + 1;
        if (j >= 3)
        {
            j = 0;
        }

        if ((ys[i] > y) != (ys[j] > y))
        {
            float intersect = xs[i] + (y - ys[i]) * (xs[j] - xs[i]) / (ys[j] - ys[i]);

            if (x < intersect)
            {
                intersections++;
            }
        }
    }

    if (intersections % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Triangle::DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const
{
    float h = (std::sqrt(3.0) / 2.0) * _side;
    float R = (std::sqrt(3.0) / 3.0) * _side;
    float r = (std::sqrt(3.0) / 6.0) * _side;

    if (_side > width || h > height)
    {
        std::cout << "The triangle is bigger than the board, cannot draw.\n";
        return;
    }

    int startY = std::max(0, static_cast<int>(_y - R));
    int endY = std::min(height - 1, static_cast<int>(_y + r));
    int startX = std::max(0, static_cast<int>(_x - _side / 2.0));
    int endX = std::min(width - 1, static_cast<int>(_x + _side / 2.0));

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            if (_isFilled)
            {
                if (CheckCoordinates(x, y))
                {
                    grid[y][x] = _color.empty() ? '*' : _color[0];
                }
            }
            else
            {
                if (CheckCoordinates(x, y))
                {
                    bool isBorder = !CheckCoordinates(x + 1, y) ||
                                    !CheckCoordinates(x - 1, y) ||
                                    !CheckCoordinates(x, y + 1) ||
                                    !CheckCoordinates(x, y - 1);
                    
                    if (isBorder)
                    {
                        grid[y][x] = _color.empty() ? '*' : _color[0];
                    } 
                }
            }
        }
    }
}

void Triangle::EditParameters()
{
    std::cout << "What do you want to edit?\n";
    std::cout << "1. side\n";
    std::cout << "2. color\n";
    std::cout << "3. fill option\n";

    int inputEdit;

    std::cout << "Please, choose your option:\n";
    if (!(std::cin >> inputEdit))
    {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    switch (inputEdit)
    {
        case 1:
        {
            std::cout << "Enter new side:\n";
            if(!(std::cin >> _side) || _side <= 0)
            {
                std::cout << "Invalid side input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n'); 
            }
            break;
        }
        case 2:
        {
            std::cout << "Enter new color:\n";
            std::cin >> _color;
            break;
        }
        case 3:
        {
            int fill;
            std::cout << "Enter fill option (1 - filled, 0 - outlined):\n";
            if (!(std::cin >> fill))
            {
                std::cout << "Invalid fill option input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }
            _isFilled = (fill != 0);
            break;
        }
        default:
        {
            std::cout << "Invalid option.\n";
            break;
        }
    }
}

std::string Triangle::ToString() const
{
    std::string fill;

    if (_isFilled)
    {
        fill = "yes";
    }
    else
    {
        fill = "no";
    }

    return "ID " + std::to_string(_id) +
            " | Type: " + GetType() +
            " | Side: " + std::to_string(_side) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: " + fill;
}