#include <cmath>
#include <iostream>
#include "circle.h"

std::string Circle::GetType() const
{
    return "circle";
}

int Circle::GetRadius() const
{
    return _radius;
}

bool Circle::CheckCoordinates(int x, int y) const
{
    if (std::pow((x - _x), 2) + std::pow((y - _y), 2) <= std::pow(_radius, 2))
    {
        return true;
    }

    return false;
}

void Circle::DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const
{
    if (_radius > width / 2 || _radius > height / 2)
    {
        std::cout << "The circle is bigger than the board, cannot draw.\n";
        return;
    }

    int startY = std::max(0, _y - _radius);
    int endY = std::min(height - 1, _y + _radius);
    int startX = std::max(0, _x - _radius);
    int endX = std::min(width - 1, _x + _radius);

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            int dX = x - _x;
            int dY = y - _y;
            int distSqrd = std::pow(dX, 2) + std::pow(dY, 2);

            if (_isFilled)
            {
                if (distSqrd <= std::pow(_radius, 2))
                {
                    grid[y][x] = '*';
                }
            }
            else
            {
                if (distSqrd <= std::pow(_radius, 2) && distSqrd >= std::pow(abs(_radius - 1), 2))
                {
                    grid[y][x] = '*';
                }
            }
        }
    }
}

void Circle::EditParameters()
{
    std::cout << "What do you want to edit?\n";
    std::cout << "1. radius\n";
    std::cout << "2. color\n";
    std::cout << "3. fill option";

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
            std::cout << "Enter new radius:\n";
            if(!(std::cin >> _radius) || _radius <= 0)
            {
                std::cout << "Invalid radius input.\n";
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

std::string Circle::ToString() const
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
            " | Radius: " + std::to_string(_radius) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: " + fill;
}