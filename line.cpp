#include <cmath>
#include <iostream>
#include <sstream>
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
                grid[y][_x] = _color.empty() ? '*' : _color[0];
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
                grid[_y][x] = _color.empty() ? '*' : _color[0];
            }
        }
    }
}

bool Line::EditParameters(std::stringstream& ss, int boardWidth, int boardHeight)
{
    int newLength;

    if (!(ss >> newLength) || newLength <= 0)
    {
        return false;
    }

    if ((_isVertical && newLength >= boardHeight) || (!_isVertical && newLength >= boardWidth))
    {
        std::cout << "Shape cannot be bigger than a board.\n";
        return false;
    }

    _length = newLength;
    return true;
}

std::string Line::Serialize() const
{
    std::ostringstream toReturn;

    toReturn << GetType() << " "
            << _id << " "
            << _x << " "
            << _y << " "
            << _length << " "
            << _isVertical << " "
            << _color;
        
    return toReturn.str();
}

bool Line::Deserialize(std::istream& serialized)
{
    if (!(serialized >> _id >> _x >> _y >> _length >> _isVertical >> _color))
    {
        return false;
    }

    return true;
}

std::string Line::ToString() const
{
    return "Type: " + GetType() +
            " | ID " + std::to_string(_id) +
            " | Length: " + std::to_string(_length) +
            " | Position: (" + std::to_string(_x) + ", " + std::to_string(_y) + ")" +
            " | Color: " + _color +
            " | Filled: cannot be filled";
}

bool Line::IsEqual(const Shape* other) const
{
    if (other == nullptr || GetType() != other -> GetType())
    {
        return false;
    }

    const Line* line = dynamic_cast<const Line*>(other);

    if (line && _x == line -> _x && _y == line -> _y &&
        _length == line -> _length && _color == line -> _color &&
        _isVertical == line -> _isVertical)
    {
        return true;
    }
    else
    {
        return false;
    }
}