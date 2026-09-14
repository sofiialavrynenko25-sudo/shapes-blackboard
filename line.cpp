#include <cmath>
#include <iostream>
#include "line.h"

std::string Line::GetType() const
{
    return "line";
}

int Line::GetLength() const
{
    return _length;
}

bool Line::GetIsVertical() const
{
    return _isVertical;
}

bool Line::CheckCoordinates(int x, int y) const
{
    if (_isVertical)
    {
        int lowerLim = _y - _length / 2;
        int upperLim = _y + _length / 2;

        if (x == _x && y >= lowerLim && y <= upperLim)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        int rightLim = _x + _length / 2;
        int leftLim = _x - _length / 2;

        if (y == _y && x >= leftLim && x <= rightLim)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Line::DrawOnBoard(std::vector<std::vector<char>>& grid, int width, int height) const
{
    if (_isVertical)
    {
        int startY = std::max(0, _y - _length / 2);
        int endY = std::min(height - 1, _y + _length / 2);

        if (_x >= 0 && _x < width)
        {
            for (int y = startY; y <= endY; y++)
            {
                grid[y][_x] = '*';
            }
        }
    }
    else
    {
        int startX = std::max(0, _x - _length / 2);
        int endX = std::min(width - 1, _x + _length / 2);

        if (_y >= 0 && _y < height)
        {
            for (int x = startX; x <= endX; x++)
            {
                grid[_y][x] = '*';
            }
        }
    }
}