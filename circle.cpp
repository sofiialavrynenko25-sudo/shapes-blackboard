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