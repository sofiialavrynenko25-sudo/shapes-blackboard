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
                grid[y][x] = '*';
            }
            else
            {
               if (x == startX || x == endX || y == startY || y == endY)
               {
                    grid[y][x] = '*';
               } 
            }
        }
    }
}