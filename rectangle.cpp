#include <cmath>
#include <iostream>
#include "rectangle.h"

std::string Rectangle::GetType() const
{
    return "rectangle";
}

int Rectangle::GetWidth() const
{
    return _width;
}

int Rectangle::GetHeight() const
{
    return _height;
}

bool Rectangle::CheckCoordinates(int x, int y) const
{
    int lowerLim = _y - _height / 2;
    int upperLim = _y + _height / 2;
    int rightLim = _x + _width / 2;
    int leftLim = _x - _width / 2;

    if (x >= leftLim && x <= rightLim && y <= upperLim && y >= lowerLim)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Rectangle::DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const
{
    int startY = std::max(0, _y - _height / 2);
    int endY = std::min(height - 1, _y + _height / 2);
    int startX = std::max(0, _x - _width / 2);
    int endX = std::min(width - 1, _x + _width / 2);

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            if (_isFilled)
            {
                grid[y][x] = _color.empty() ? '*' : _color[0];
            }
            else
            {
               if (x == startX || x == endX || y == startY || y == endY)
               {
                    grid[y][x] = _color.empty() ? '*' : _color[0];
               } 
            }
        }
    }
}

void Rectangle::EditParameters()
{
    std::cout << "What do you want to edit?\n";
    std::cout << "1. width\n";
    std::cout << "2. height\n";
    std::cout << "3. color\n";
    std::cout << "4. fill option\n";

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
            std::cout << "Enter new width:\n";
            if(!(std::cin >> _width) || _width <= 0)
            {
                std::cout << "Invalid width input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n'); 
            }
            break;
        }
        case 2:
        {
            std::cout << "Enter new height:\n";
            if(!(std::cin >> _height) || _height <= 0)
            {
                std::cout << "Invalid height input.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n'); 
            }
            break;
        }
        case 3:
        {
            std::cout << "Enter new color:\n";
            std::cin >> _color;
            break;
        }
        case 4:
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

std::string Rectangle::ToString() const
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
            " | Width: " + std::to_string(_width) +
            " | Height: " + std::to_string(_height) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: " + fill;
}