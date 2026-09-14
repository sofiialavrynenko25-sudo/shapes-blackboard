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
                    grid[y][x] = '*';
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
                        grid[y][x] = '*';
                    } 
                }
            }
        }
    }
}