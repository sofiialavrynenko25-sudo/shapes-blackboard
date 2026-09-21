#include <cmath>
#include <iostream>
#include <sstream>
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
                    grid[y][x] = _color.empty() ? '*' : _color[0];
                }
            }
            else
            {
                if (distSqrd <= std::pow(_radius, 2) && distSqrd >= std::pow(abs(_radius - 1), 2))
                {
                    grid[y][x] = _color.empty() ? '*' : _color[0];
                }
            }
        }
    }
}

bool Circle::EditParameters(std::stringstream& ss, int boardWidth, int boardHeight)
{
    int newRadius;

    if (!(ss >> newRadius) || newRadius <= 0)
    {
        return false;
    }

    if (newRadius * 2 >= boardHeight || newRadius * 2 >= boardWidth)
    {
        std::cout << "Shape cannot be bigger than a board.\n";
        return false;
    }

    _radius = newRadius;
    return true;
}

std::string Circle::Serialize() const
{
    std::ostringstream toReturn;

    toReturn << GetType() << " "
            << _id << " "
            << _x << " "
            << _y << " "
            << _radius << " "
            << _color << " "
            << _isFilled;
        
    return toReturn.str();
}

bool Circle::Deserialize(std::istream& serialized)
{
    if (!(serialized >> _id >> _x >> _y >> _radius >> _color >> _isFilled))
    {
        return false;
    }

    return true;
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

    return "Type: " + GetType() + 
            " | ID " + std::to_string(_id) +
            " | Radius: " + std::to_string(_radius) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: " + fill;
}

bool Circle::IsEqual(const Shape* other) const
{
    if (other == nullptr || GetType() != other -> GetType())
    {
        return false;
    }

    const Circle* circle = dynamic_cast<const Circle*>(other);

    if (circle && _x == circle -> _x && _y == circle -> _y &&
        _radius == circle -> _radius && _color == circle -> _color &&
        _isFilled == circle -> _isFilled)
    {
        return true;
    }
    else
    {
        return false;
    }
}